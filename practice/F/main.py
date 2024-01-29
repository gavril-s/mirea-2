import datetime
import re
import vk_api
from vk_api.longpoll import VkLongPoll, VkEventType
from vk_api.utils import get_random_id
from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.upload import VkUpload
import settings
import weather
from schedule import MireaSchedule, Weekdays, Parity


def make_group_keyboard():
    keyboard = VkKeyboard(one_time=True)
    keyboard.add_button("На сегодня", color=VkKeyboardColor.POSITIVE)
    keyboard.add_button("На завтра", color=VkKeyboardColor.NEGATIVE)
    keyboard.add_line()
    keyboard.add_button("На эту неделю", color=VkKeyboardColor.PRIMARY)
    keyboard.add_button("На следующую неделю", color=VkKeyboardColor.PRIMARY)
    keyboard.add_line()
    keyboard.add_button("Какая неделя?", color=VkKeyboardColor.SECONDARY)
    keyboard.add_button("Какая группа?", color=VkKeyboardColor.SECONDARY)
    return keyboard


def make_teacher_keyboard():
    keyboard = VkKeyboard(one_time=True)
    keyboard.add_button("На сегодня", color=VkKeyboardColor.POSITIVE)
    keyboard.add_button("На завтра", color=VkKeyboardColor.NEGATIVE)
    keyboard.add_line()
    keyboard.add_button("На эту неделю", color=VkKeyboardColor.PRIMARY)
    keyboard.add_button("На следующую неделю", color=VkKeyboardColor.PRIMARY)
    return keyboard


def make_teachers_choice_keyboard(teachers):
    keyboard = VkKeyboard(one_time=True)
    for i in range(len(teachers)):
        keyboard.add_button(teachers[i], color=VkKeyboardColor.PRIMARY)
        if i != len(teachers) - 1:
            keyboard.add_line()
    return keyboard


def make_weather_keyboard():
    keyboard = VkKeyboard(one_time=True)
    keyboard.add_button("сейчас", color=VkKeyboardColor.PRIMARY)
    keyboard.add_button("сегодня", color=VkKeyboardColor.POSITIVE)
    keyboard.add_button("завтра", color=VkKeyboardColor.POSITIVE)
    keyboard.add_line()
    keyboard.add_button("на 5 дней", color=VkKeyboardColor.POSITIVE)
    return keyboard


def main():
    try:
        schedule = MireaSchedule(datetime.timedelta(hours=12))
        schedule.start()

        vk_session = vk_api.VkApi(token=settings.vk_token)
        vk = vk_session.get_api()
        vk_upload = VkUpload(vk)
        longpoll = VkLongPoll(vk_session)

        group_keyboard = make_group_keyboard()
        teacher_keyboard = make_teacher_keyboard()
        weather_keyboard = make_weather_keyboard()

        users_groups = dict()

        group_name_pattern = r"[А-Я]{4}-\d{2}-\d{2}"
        teacher_name_pattern = r"[А-ЯЁ][а-яё]+\s[А-Я]\.[А-Я]\."
        weekday_pattern = (
            r"(ПОНЕДЕЛЬНИК|ВТОРНИК|СРЕДА|ЧЕТВЕРГ|ПЯТНИЦА|СУББОТА|ВОСКРЕСЕНЬЕ)"
        )

        HELP_TEXT = (
            "Краткая инструкция к боту:\n"
            + "· Начать - инструкция к боту\n"
            + "· [ИКБО-01-21] - сохранения номера группы\n"
            + "· Бот - показать клавиатуру с различными вариантами получения расписания\n"
            + "· Какая неделя? - получение номера текущей учебной недели\n"
            + "· Какая группа? - полное расписание сохранённой группы\n"
            + "· Бот [понедельник] - расписание сохранённой группы на определённый день недели\n"
            + "· Бот [ИКБО-01-21] - полное расписание указанной группы\n"
            + "· Бот [вторник] [ИНБО-01-21] - расписание указанной группы на определённый день недели\n"
            + "· Погода - вывод текущей погоды в Москве"
        )

        current_group = ""
        current_teacher = ""

        print("Bot: started")

        for event in longpoll.listen():
            if (
                event.type == VkEventType.MESSAGE_NEW
                and event.to_me
                and event.text
            ):
                print(f"New from {event.user_id}, text = {event.text}")
                msg = event.text.upper()

                if re.match("^НАЧАТЬ$", msg):
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=HELP_TEXT,
                    )
                elif re.match("^" + group_name_pattern + "$", msg):
                    users_groups[event.user_id] = msg
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=f"Я запомнил, что ты из группы {msg}",
                    )
                elif re.match("^БОТ$", msg):
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        keyboard=group_keyboard.get_keyboard(),
                        message=f"Показать расписание...",
                    )
                elif re.match("^НА СЕГОДНЯ$", msg):
                    name = ""
                    if current_group != "":
                        name = current_group
                        current_group = ""
                    elif current_teacher != "":
                        name = current_teacher
                        current_teacher = ""
                    else:
                        if event.user_id not in users_groups:
                            vk.messages.send(
                                user_id=event.user_id,
                                random_id=get_random_id(),
                                message="У меня не сохранена твоя группа",
                            )
                            continue
                        else:
                            name = users_groups[event.user_id]

                    schedules = schedule.get_formatted_day_schedules(
                        name, datetime.date.today()
                    )
                    if len(schedules) == 0:
                        res = "Расписание не найдено..."
                    else:
                        res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match("^НА ЗАВТРА$", msg):
                    name = ""
                    if current_group != "":
                        name = current_group
                        current_group = ""
                    elif current_teacher != "":
                        name = current_teacher
                        current_teacher = ""
                    else:
                        if event.user_id not in users_groups:
                            vk.messages.send(
                                user_id=event.user_id,
                                random_id=get_random_id(),
                                message="У меня не сохранена твоя группа",
                            )
                            continue
                        else:
                            name = users_groups[event.user_id]

                    schedules = schedule.get_formatted_day_schedules(
                        name,
                        datetime.date.today() + datetime.timedelta(days=1),
                    )
                    if len(schedules) == 0:
                        res = "Расписание не найдено..."
                    else:
                        res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match("^НА ЭТУ НЕДЕЛЮ$", msg):
                    name = ""
                    if current_group != "":
                        name = current_group
                        current_group = ""
                    elif current_teacher != "":
                        name = current_teacher
                        current_teacher = ""
                    else:
                        if event.user_id not in users_groups:
                            vk.messages.send(
                                user_id=event.user_id,
                                random_id=get_random_id(),
                                message="У меня не сохранена твоя группа",
                            )
                            continue
                        else:
                            name = users_groups[event.user_id]

                    schedules = schedule.get_formatted_week_schedules(
                        name, datetime.date.today()
                    )
                    if len(schedules) == 0:
                        res = "Расписание не найдено..."
                    else:
                        res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match("^НА СЛЕДУЮЩУЮ НЕДЕЛЮ$", msg):
                    name = ""
                    if current_group != "":
                        name = current_group
                        current_group = ""
                    elif current_teacher != "":
                        name = current_teacher
                        current_teacher = ""
                    else:
                        if event.user_id not in users_groups:
                            vk.messages.send(
                                user_id=event.user_id,
                                random_id=get_random_id(),
                                message="У меня не сохранена твоя группа",
                            )
                            continue
                        else:
                            name = users_groups[event.user_id]

                    schedules = schedule.get_formatted_week_schedules(
                        name,
                        datetime.date.today() + datetime.timedelta(days=7),
                    )
                    if len(schedules) == 0:
                        res = "Расписание не найдено..."
                    else:
                        res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match("^КАКАЯ НЕДЕЛЯ\?$", msg):
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=f"Идёт {schedule.get_week_number()} неделя",
                    )
                elif re.match("^КАКАЯ ГРУППА\?$", msg):
                    if event.user_id not in users_groups:
                        res = "У меня не сохранена твоя группа"
                    else:
                        schedules = schedule.get_formatted_general_schedules(
                            users_groups[event.user_id]
                        )
                        if len(schedules) == 0:
                            res = "Твоя группа не найдена..."
                        else:
                            res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match("^БОТ " + weekday_pattern + "$", msg):
                    if event.user_id not in users_groups:
                        res = "У меня не сохранена твоя группа"
                    else:
                        schedules = (
                            schedule.get_formatted_general_day_schedules(
                                users_groups[event.user_id],
                                Weekdays.from_string(msg[4:]),
                            )
                        )
                        if len(schedules) == 0:
                            res = "Твоя группа не найдена..."
                        else:
                            res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match(
                    "^БОТ " + weekday_pattern + " " + group_name_pattern + "$",
                    msg,
                ):
                    weekday, group = msg[4:].split(" ")
                    schedules = schedule.get_formatted_general_day_schedules(
                        group, Weekdays.from_string(weekday)
                    )
                    if len(schedules) == 0:
                        res = "Группа не найдена..."
                    else:
                        res = list(schedules.values())[0]
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message=res,
                    )
                elif re.match("^БОТ " + group_name_pattern + "$", msg):
                    group = msg[4:]
                    if group not in schedule.get_groups_list():
                        vk.messages.send(
                            user_id=event.user_id,
                            random_id=get_random_id(),
                            message="Группа не найдена...",
                        )
                    else:
                        current_group = group
                        vk.messages.send(
                            user_id=event.user_id,
                            random_id=get_random_id(),
                            keyboard=group_keyboard.get_keyboard(),
                            message=f"Показать расписание группы {current_group}",
                        )
                elif re.match("^ПОГОДА$", msg):
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        keyboard=weather_keyboard.get_keyboard(),
                        message="Показать погоду в Москве...",
                    )
                elif re.match("^НАЙТИ ", msg):
                    current_teacher = msg[6:].lower().capitalize()
                    matching_teachers = []
                    for teacher in schedule.get_teachers_list():
                        if current_teacher == teacher[: len(current_teacher)]:
                            matching_teachers.append(teacher)
                    if len(matching_teachers) == 1:
                        current_teacher = matching_teachers[0]
                    else:
                        current_teacher = ""

                    if len(matching_teachers) == 0:
                        vk.messages.send(
                            user_id=event.user_id,
                            random_id=get_random_id(),
                            message="Преподаватель не найден",
                        )
                    elif len(matching_teachers) > 1:
                        vk.messages.send(
                            user_id=event.user_id,
                            random_id=get_random_id(),
                            keyboard=make_teachers_choice_keyboard(
                                matching_teachers
                            ).get_keyboard(),
                            message="Выберите преподавателя",
                        )
                    else:
                        vk.messages.send(
                            user_id=event.user_id,
                            random_id=get_random_id(),
                            keyboard=teacher_keyboard.get_keyboard(),
                            message=f"Показать расписание преподавателя {current_teacher}",
                        )
                elif re.match(teacher_name_pattern, event.text):
                    current_teacher = event.text
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        keyboard=teacher_keyboard.get_keyboard(),
                        message=f"Показать расписание преподавателя {current_teacher}",
                    )
                elif re.match("^СЕЙЧАС$", msg):
                    weather_data = weather.get_current_weather("Moscow")
                    with open(weather_data[1], "rb") as img_file:
                        upload_image = vk_upload.photo_messages(
                            photos=img_file, peer_id=event.user_id
                        )[0]
                        pic = "photo{}_{}".format(
                            upload_image["owner_id"], upload_image["id"]
                        )
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        attachment=pic,
                        message=weather_data[0],
                    )
                elif re.match("^СЕГОДНЯ$", msg):
                    weather_data = weather.get_forecast(
                        "Moscow", datetime.date.today()
                    )
                    with open(weather_data[1], "rb") as img_file:
                        upload_image = vk_upload.photo_messages(
                            photos=img_file, peer_id=event.user_id
                        )[0]
                        pic = "photo{}_{}".format(
                            upload_image["owner_id"], upload_image["id"]
                        )
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        attachment=pic,
                        message=weather_data[0],
                    )
                elif re.match("^ЗАВТРА$", msg):
                    weather_data = weather.get_forecast(
                        "Moscow",
                        datetime.date.today() + datetime.timedelta(days=1),
                    )
                    with open(weather_data[1], "rb") as img_file:
                        upload_image = vk_upload.photo_messages(
                            photos=img_file, peer_id=event.user_id
                        )[0]
                        pic = "photo{}_{}".format(
                            upload_image["owner_id"], upload_image["id"]
                        )
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        attachment=pic,
                        message=weather_data[0],
                    )
                elif re.match("^НА 5 ДНЕЙ$", msg):
                    weather_data = weather.get_brief_5d_forecast("Moscow")
                    with open(weather_data[1], "rb") as img_file:
                        upload_image = vk_upload.photo_messages(
                            photos=img_file, peer_id=event.user_id
                        )[0]
                        pic = "photo{}_{}".format(
                            upload_image["owner_id"], upload_image["id"]
                        )
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        attachment=pic,
                        message=weather_data[0],
                    )
                else:
                    vk.messages.send(
                        user_id=event.user_id,
                        random_id=get_random_id(),
                        message="Неизвестная команда",
                    )
    finally:
        print("Bot: stopped")
        schedule.stop()


if __name__ == "__main__":
    main()
