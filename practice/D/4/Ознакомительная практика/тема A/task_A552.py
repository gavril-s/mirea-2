# Создать список (коллекция фильмов), состоящий из словарей (фильмы). Словари должны содержать как минимум 5 полей
# (например, номер, название, год выхода...). В список добавить хотя бы 10 словарей.
# Конструкция вида:
# films = [{"id" : 123456, "title" : "Титаник", "year" : "1997",...} , {...}, {...}, ...]
# Реализовать функции:
# – вывода информации о всех фильмах;
# – вывода информации о фильме по введенному с клавиатуры номеру;
# – вывода количества фильмов, новее введённого года;
# – обновлении всей информации о фильме по введенному номеру;
# – удалении фильма по номеру.
# Провести тестирование функций.

films = [
    {
        "id": 1,
        "title": "The Shawshank Redemption",
        "year": 1994,
        "rating": 9.3,
        "genre": "Drama",
    },
    {
        "id": 2,
        "title": "The Godfather",
        "year": 1972,
        "rating": 9.2,
        "genre": "Crime, Drama",
    },
    {
        "id": 3,
        "title": "The Dark Knight",
        "year": 2008,
        "rating": 9.0,
        "genre": "Action, Crime, Drama",
    },
    {
        "id": 4,
        "title": "The Godfather Part II",
        "year": 1974,
        "rating": 9.0,
        "genre": "Crime, Drama",
    },
    {
        "id": 5,
        "title": "12 Angry Men",
        "year": 1957,
        "rating": 9.0,
        "genre": "Crime, Drama",
    },
    {
        "id": 6,
        "title": "Schindler's List",
        "year": 1993,
        "rating": 9.0,
        "genre": "Biography, Drama, History",
    },
    {
        "id": 7,
        "title": "The Lord of the Rings: The Return of the King",
        "year": 2003,
        "rating": 9.0,
        "genre": "Action, Adventure, Drama",
    },
    {
        "id": 8,
        "title": "Pulp Fiction",
        "year": 1994,
        "rating": 8.9,
        "genre": "Crime, Drama",
    },
    {
        "id": 9,
        "title": "The Lord of the Rings: The Fellowship of the Ring",
        "year": 2001,
        "rating": 8.8,
        "genre": "Action, Adventure, Drama",
    },
    {
        "id": 10,
        "title": "The Good, the Bad and the Ugly",
        "year": 1966,
        "rating": 8.8,
        "genre": "Adventure, Western",
    },
]


def get_film_by_id(id):
    if id - 1 >= len(films) or id - 1 < 0:
        raise (IndexError("Фильма с таким номером нет"))
    return films[id - 1]


def print_film(film):
    print(
        film["id"],
        " : ",
        film["title"],
        ", ",
        film["year"],
        " (рейтинг - ",
        film["rating"],
        ", жанр - ",
        film["genre"],
        ")",
        sep="",
    )


def print_film_by_id(id):
    film = get_film_by_id(id)
    print_film(film)


def print_all_films():
    for film in films:
        print_film(film)


def print_films_after(year):
    for film in films:
        if film["year"] >= year:
            print_film(film)


def print_film_by_id_input():
    print("Введите номер фильма в списке: ", end="")
    film_id = int(input())
    print_film_by_id(film_id)


def print_films_after_by_year_input():
    print("Введите год: ", end="")
    year = int(input())
    print_films_after(year)


def update_film_by_id_input():
    print("Введите номер фильма в списке: ", end="")
    film_id = int(input())
    film = get_film_by_id(film_id)

    print("Введите новое название (enter - не менять): ", end="")
    new_title = input()

    print("Введите новый год (enter - не менять): ", end="")
    new_year = input()

    print("Введите новый рейтинг (enter - не менять): ", end="")
    new_rating = input()

    print("Введите новый жанр (enter - не менять): ", end="")
    new_genre = input()

    if new_title != "":
        film["title"] = new_title

    if new_year != "":
        film["year"] = int(new_year)

    if new_rating != "":
        film["rating"] = float(new_rating)

    if new_genre != "":
        film["genre"] = new_genre

    print_film(film)


def delete_film_by_id_input():
    print("Введите номер фильма в списке: ", end="")
    film_id = int(input())
    film = get_film_by_id(film_id)
    films.remove(film)


def test_all_functions():
    print("-" * 100)
    print("Тест вывода информации о всех фильмах:")
    print_all_films()

    print("-" * 100)
    print("Тест вывода информации о фильме по введенному с клавиатуры номеру:")
    print_film_by_id_input()

    print("-" * 100)
    print("Тест вывода количества фильмов, новее введённого года:")
    print_films_after_by_year_input()

    print("-" * 100)
    print("Тест обновлении всей информации о фильме по введенному номеру:")
    update_film_by_id_input()

    print("-" * 100)
    print("Тест удалении фильма по номеру:")
    delete_film_by_id_input()
    print_all_films()


test_all_functions()
