import settings
import requests
import datetime
import json
import os
from PIL import Image


def get_wind_direction(angle):
    directions = [
        "северный",
        "северо-восточный",
        "восточный",
        "юго-восточный",
        "южный",
        "юго-западный",
        "западный",
        "северо-западный",
    ]
    index = round(angle / 45) % 8
    return directions[index]


def download_icons(urls, save_path):
    paths = []
    if not os.path.exists(save_path):
        os.mkdir(save_path)

    for url in urls:
        response = requests.get(url)
        path = os.path.join(save_path, url.split("/")[-1])
        paths.append(path)
        with open(path, "wb") as file:
            file.write(response.content)

    return paths


def combine_images(images, output_path):
    widths, heights = zip(*(i.size for i in images))

    total_width = sum(widths)
    max_height = max(heights)

    new_image = Image.new("RGBA", (total_width, max_height))

    x_offset = 0
    for image in images:
        new_image.paste(image, (x_offset, 0))
        x_offset += image.width

    new_image.save(output_path)
    new_image.close()


def get_weather_desctiption(weather):
    text = f"Состояние погоды: {weather['weather'][0]['description']}\n"
    text += f"Температура: {weather['main']['temp']}°C\n"
    text += f"Давление: {round(weather['main']['pressure'] * 0.750062, 1)} мм рт. ст.\n"
    text += f"Влажность: {weather['main']['humidity']}%\n"
    text += f"Сила ветра: {weather['wind']['speed']}м/с\n"
    text += f"Направление ветра: {get_wind_direction(weather['wind']['deg'])}"
    return text


def get_current_weather(city):
    icon_dir = "weather_data"
    url = f"http://api.openweathermap.org/data/2.5/weather?q={city},ru&appid={settings.openweather_key}&lang=ru&units=metric"
    response = requests.get(url)
    data = response.json()

    text = get_weather_desctiption(data)
    icon_url = (
        f"http://openweathermap.org/img/wn/{data['weather'][0]['icon']}.png"
    )
    icons_paths = download_icons([icon_url], icon_dir)

    return (text.strip(), icons_paths[0])


def get_forecast(city, date):
    icon_dir = "weather_data"
    url = f"http://api.openweathermap.org/data/2.5/forecast/?q={city},ru&appid={settings.openweather_key}&lang=ru&units=metric"
    response = requests.get(url)
    data = response.json()
    forecast = data["list"]

    icons_urls = []
    text = ""

    for item in forecast:
        time = datetime.datetime.fromtimestamp(item["dt"])

        if time.hour == 9 and time.date() == date:
            text += "Утро:\n" + get_weather_desctiption(item) + "\n\n"
            icons_urls.append(
                f"http://openweathermap.org/img/wn/{item['weather'][0]['icon']}.png"
            )
        if time.hour == 15 and time.date() == date:
            text += "День:\n" + get_weather_desctiption(item) + "\n\n"
            icons_urls.append(
                f"http://openweathermap.org/img/wn/{item['weather'][0]['icon']}.png"
            )
        if time.hour == 21 and time.date() == date:
            text += "Вечер:\n" + get_weather_desctiption(item) + "\n\n"
            icons_urls.append(
                f"http://openweathermap.org/img/wn/{item['weather'][0]['icon']}.png"
            )
        if time.hour == 3 and time.date() == date:
            text += "Ночь:\n" + get_weather_desctiption(item) + "\n\n"
            icons_urls.append(
                f"http://openweathermap.org/img/wn/{item['weather'][0]['icon']}.png"
            )

    icons_paths = download_icons(icons_urls, icon_dir)
    icons = [Image.open(file) for file in icons_paths]

    out_path = os.path.join(icon_dir, "out.png")
    combine_images(icons, out_path)
    for icon in icons:
        icon.close()

    return (text.strip(), out_path)


def get_brief_5d_forecast(city):
    icon_dir = "weather_data"
    url = f"http://api.openweathermap.org/data/2.5/forecast?q={city},ru&appid={settings.openweather_key}&lang=ru&units=metric"
    response = requests.get(url)
    data = response.json()
    forecast = data["list"]

    icons_urls = []
    text = ""

    for item in forecast:
        time = datetime.datetime.fromtimestamp(item["dt"])

        if time.hour == 12:
            text += (
                f"{time.date()}:\n" + get_weather_desctiption(item) + "\n\n"
            )
            icons_urls.append(
                f"http://openweathermap.org/img/wn/{item['weather'][0]['icon']}.png"
            )

    icons_paths = download_icons(icons_urls, icon_dir)
    icons = [Image.open(file) for file in icons_paths]

    out_path = os.path.join(icon_dir, "out.png")
    combine_images(icons, out_path)
    for icon in icons:
        icon.close()

    return (text.strip(), out_path)
