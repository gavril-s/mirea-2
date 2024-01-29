from tkinter import *
from tkinter.ttk import Notebook, Frame, Combobox
import math
import requests
import xml.etree.ElementTree as ET
from collections import defaultdict
from datetime import datetime, date, timedelta
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg,
    NavigationToolbar2Tk,
)


class time_period:
    def __init__(self, begin, end):
        self.begin = begin
        self.end = end

    def __str__(self):
        return (
            self.begin.strftime("%d/%m/%Y")
            + " - "
            + self.end.strftime("%d/%m/%Y")
        )

    def daterange(self, begin_date, end_date, step=1):
        for n in range(0, int((end_date - begin_date).days), step):
            yield begin_date + timedelta(n)

    def split(self, points_number):
        points = []
        points_number -= 1
        step = math.ceil(self.duration() / points_number)
        for point in self.daterange(self.begin, self.end, step):
            points.append(point)
        points.append(self.end)
        return points

    def duration(self):
        return int((self.end - self.begin).days)


class converter_app:
    def __init__(self):
        self.base_data_url = (
            "http://www.cbr.ru/scripts/XML_daily.asp?date_req="
        )
        self.window_geometry = "700x400"
        self.expanded_window_geometry = "700x700"
        self.converter_tab_objects = dict()
        self.graph_tab_objects = dict()
        self.plot = None
        self.graph_canvas = None

        self.currency_data = self.fetch_currency_data()
        self.currency_data['Российский рубль'] = {
            'NumCode': 0,
            'CharCode': 'RU',
            'Nominal': 1,
            'Value': 1
        }

        self.build_interface()

    def run(self):
        self.window.mainloop()

    def fetch_currency_data(self, date=None):
        if date is None:
            date = datetime.today()
        data_url = self.base_data_url + date.strftime("%d/%m/%Y")
        res_xml = requests.get(data_url)
        res_dict_temp = self.parse_xml(res_xml.content)
        res_dict = dict()
        for key in res_dict_temp:
            elem = res_dict_temp[key]
            new_key = elem["Name"]
            res_dict[new_key] = dict()
            res_dict[new_key]["NumCode"] = int(elem["NumCode"])
            res_dict[new_key]["CharCode"] = elem["CharCode"]
            res_dict[new_key]["Nominal"] = int(elem["Nominal"])
            res_dict[new_key]["Value"] = float(elem["Value"].replace(",", "."))
        return res_dict

    def parse_xml(self, data):
        root = ET.fromstring(data)
        result = dict()
        tags = defaultdict(int)
        for child in root:
            tags[child.tag] += 1
            if tags[child.tag] > 1:
                tag = child.tag + str(tags[child.tag])
            else:
                tag = child.tag

            if len(child) == 0:
                result[tag] = child.text
            else:
                result[tag] = self.parse_xml(ET.tostring(child))
        return result

    def get_currency_list(self):
        return list(self.currency_data.keys())

    def get_currency_worth(self, name, data=None):
        if data is None:
            data = self.currency_data
        currency = data[name]
        return float(currency["Value"]) / float(currency["Nominal"])

    def build_converter_tab(self, tab_control):
        self.converter_tab = Frame(tab_control)
        tab_control.add(self.converter_tab, text="Конвертер")

        relwidth = 0.3
        relheight = 0.15
        relpadx = (1 - 3 * relwidth) / 4
        relpady = (1 - 2 * relheight) / 3

        currency_from_combobox = Combobox(self.converter_tab)
        currency_from_combobox["values"] = self.get_currency_list()
        currency_from_combobox.current(0)
        currency_from_combobox.place(
            relheight=relheight, relwidth=relwidth, relx=relpadx, rely=relpady
        )
        self.converter_tab_objects[
            "currency_from_combobox"
        ] = currency_from_combobox

        currency_to_combobox = Combobox(self.converter_tab)
        currency_to_combobox["values"] = self.get_currency_list()
        currency_to_combobox.current(0)
        currency_to_combobox.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=relpadx,
            rely=2 * relpady + relheight,
        )
        self.converter_tab_objects[
            "currency_to_combobox"
        ] = currency_to_combobox

        currency_amount_entry = Entry(self.converter_tab, text="")
        currency_amount_entry.focus()
        currency_amount_entry.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=2 * relpadx + relwidth,
            rely=relpady,
        )
        self.converter_tab_objects[
            "currency_amount_entry"
        ] = currency_amount_entry

        result_label = Label(
            self.converter_tab,
            bg="White",
            justify=LEFT,
            borderwidth=1,
            relief="sunken",
            text="",
        )
        result_label.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=2 * relpadx + relwidth,
            rely=2 * relpady + relheight,
        )
        self.converter_tab_objects["result_label"] = result_label

        convert_button = Button(
            self.converter_tab,
            text="Конвертировать",
            command=self.convert_button_on_click,
        )
        convert_button.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=3 * relpadx + 2 * relwidth,
            rely=0.5 - relheight / 2,
        )
        self.converter_tab_objects["convert_button"] = convert_button

    def convert_button_on_click(self):
        value_str = self.converter_tab_objects["currency_amount_entry"].get()
        if value_str != "":
            value = float(value_str)
            currency_from = self.converter_tab_objects[
                "currency_from_combobox"
            ].get()
            currency_to = self.converter_tab_objects[
                "currency_to_combobox"
            ].get()

            from_worth = self.get_currency_worth(currency_from)
            to_worth = self.get_currency_worth(currency_to)
            res = value * from_worth / to_worth

            self.converter_tab_objects["result_label"].config(text=str(res))
        else:
            self.converter_tab_objects["result_label"].config(text="NO INPUT")

    def build_graph_tab(self, tab_control):
        self.graph_tab = Frame(tab_control)
        tab_control.add(self.graph_tab, text="Динамика")

        relwidth = 0.3
        relheight = 0.15
        relpadx = (1 - 2 * relwidth) / 3
        relpady = (1 - 3 * relheight) / 4
        relradiopady = (1 - 2 * relpady - 4 * relheight) / 4

        period_radio_state = StringVar()
        period_radio_state.set("week")
        period_radio_state.trace_add("write", self.period_radio_state_on_write)
        self.graph_tab_objects["period_radio_state"] = period_radio_state
        self.graph_tab_objects["last_periods"] = []

        period_radiobutton_week = Radiobutton(
            self.graph_tab, text="Неделя", value="week", variable=period_radio_state
        )
        period_radiobutton_week.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=relpadx,
            rely=relpady,
        )
        self.graph_tab_objects[
            "period_radiobutton_week"
        ] = period_radiobutton_week

        period_radiobutton_month = Radiobutton(
            self.graph_tab, text="Месяц", value="month", variable=period_radio_state
        )
        period_radiobutton_month.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=relpadx,
            rely=relpady + relradiopady + relheight,
        )
        self.graph_tab_objects[
            "period_radiobutton_month"
        ] = period_radiobutton_month

        period_radiobutton_quarter = Radiobutton(
            self.graph_tab,
            text="Квартал",
            value="quarter",
            variable=period_radio_state,
        )
        period_radiobutton_quarter.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=relpadx,
            rely=relpady + 2 * relradiopady + 2 * relheight,
        )
        self.graph_tab_objects[
            "period_radiobutton_quarter"
        ] = period_radiobutton_quarter

        period_radiobutton_year = Radiobutton(
            self.graph_tab, text="Год", value="year", variable=period_radio_state
        )
        period_radiobutton_year.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=relpadx,
            rely=relpady + 3 * relradiopady + 3 * relheight,
        )
        self.graph_tab_objects[
            "period_radiobutton_year"
        ] = period_radiobutton_year

        period_combobox_state = StringVar()
        self.graph_tab_objects["period_combobox_state"] = period_combobox_state
        period_combobox_state.trace_add(
            "write", self.period_combobox_state_on_write
        )
        period_combobox = Combobox(
            self.graph_tab, textvariable=period_combobox_state
        )
        period_combobox["values"] = tuple()
        period_combobox.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=2 * relpadx + relwidth,
            rely=relpady,
        )
        self.graph_tab_objects["period_combobox"] = period_combobox

        currency_combobox = Combobox(self.graph_tab)
        currency_combobox["values"] = self.get_currency_list()
        currency_combobox.current(0)
        currency_combobox.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=2 * relpadx + relwidth,
            rely=2 * relpady + relheight,
        )
        self.graph_tab_objects["currency_combobox"] = currency_combobox

        draw_graph_button = Button(
            self.graph_tab,
            text="Отобразить график",
            command=self.draw_graph_button_on_click,
        )
        draw_graph_button.place(
            relheight=relheight,
            relwidth=relwidth,
            relx=2 * relpadx + relwidth,
            rely=3 * relpady + 2 * relheight,
        )
        self.graph_tab_objects["draw_graph_button"] = draw_graph_button

    def add_period_to_combobox(self, period):
        combobox = self.graph_tab_objects["period_combobox"]
        combobox.config(values=[str(period)] + list(combobox["values"])[:2])
        combobox.current(0)
        last_periods = self.graph_tab_objects["last_periods"]
        self.graph_tab_objects["last_periods"] = [
            (str(period), period)
        ] + last_periods[:2]

    def period_radio_state_on_write(self, *args):
        state = self.graph_tab_objects["period_radio_state"].get()
        today = datetime.today()

        if state == "week":
            week_ago = today - timedelta(7)
            period = time_period(week_ago, today)
        elif state == "month":
            month_ago = today.replace(month=today.month - 1)
            period = time_period(month_ago, today)
        elif state == "quarter":
            quarter_ago = today.replace(month=today.month - 3)
            period = time_period(quarter_ago, today)
        elif state == "year":
            year_ago = today.replace(year=today.year - 1)
            period = time_period(year_ago, today)
        self.graph_tab_objects["period"] = period
        self.add_period_to_combobox(period)

    def period_combobox_state_on_write(self, *args):
        index = self.graph_tab_objects["period_combobox_state"].get()
        selected_period = None
        last_periods = self.graph_tab_objects["last_periods"]
        for i in range(len(last_periods)):
            if last_periods[i][0] == index:
                selected_period = last_periods[i][1]
                break
        if selected_period is None:
            return

        self.graph_tab_objects["last_periods"] = [
            (str(selected_period), selected_period)
        ] + last_periods[:2]

        radio_state = self.graph_tab_objects["period_radio_state"].get()
        if selected_period.duration() == 7:
            self.graph_tab_objects["period_radio_state"].set("week")
        elif selected_period.duration() in [28, 29, 30, 31]:
            self.graph_tab_objects["period_radio_state"].set("month")
        elif selected_period.duration() in [365, 366]:
            self.graph_tab_objects["period_radio_state"].set("year")
        else:
            self.graph_tab_objects["period_radio_state"].set("quarter")

    def draw_graph_button_on_click(self):
        period = self.graph_tab_objects["last_periods"][0][1]
        points = period.split(30)
        currency = self.graph_tab_objects["currency_combobox"].get()
        worth_data = []
        for point in points:
            currency_data = self.fetch_currency_data(point)
            worth_data.append(self.get_currency_worth(currency, currency_data))

        if self.plot is None:
            self.window.geometry(self.expanded_window_geometry)

            fig = Figure(figsize=(6, 3), dpi=100)
            self.plot = fig.add_subplot()
            self.plot.plot(points, worth_data)
            
            self.graph_canvas = FigureCanvasTkAgg(fig, master=self.window)
            self.graph_canvas.draw()
            self.graph_canvas.get_tk_widget().pack(side=BOTTOM)
        else:
            self.plot.clear()
            self.plot.plot(points, worth_data)
            self.graph_canvas.draw()

    def build_interface(self):
        self.window = Tk()
        self.window.title("Конвертор валют")
        self.window.geometry(self.window_geometry)

        self.tab_control = Notebook(self.window)
        self.build_converter_tab(self.tab_control)
        self.build_graph_tab(self.tab_control)
        self.tab_control.pack(expand=True, fill=BOTH)


if __name__ == "__main__":
    app = converter_app()
    app.run()
