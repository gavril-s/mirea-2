import pickle
import datetime
from C.Person import Person
from C.Reader import Reader
from C.Librarian import Librarian
from C.Library import Library

person = Person("Иван", "Иванов", 25)
reader = Reader("Иван", "Иванов", 25, "123456")
librarian = Librarian(
    "Иванов",
    "Иван",
    30,
    "00001",
    "Библиотекарь",
    {"пн": "10:00-18:00", "вт": "10:00-18:00"},
)

reader1 = Reader("Иванов", "Иван", 30, "111-222")
reader2 = Reader("Петров", "Петр", 25, "222-333")
librarian1 = Librarian(
    "Сидорова",
    "Елена",
    40,
    "222-333",
    "Библиотекарь",
    {"пн": "10-18", "вт": "12-20"},
)
librarian2 = Librarian(
    "Кузнецова",
    "Ольга",
    35,
    "333-444",
    "Главный библиотекарь",
    {"ср": "10-18", "чт": "12-20"},
)
library = Library(
    "Главная библиотека",
    "ул. Пушкина, д.10",
    [reader1, reader2],
    [librarian1, librarian2],
)

objects = [person, reader, librarian, library]

with open("objects.pickle", "wb") as outfile:
    pickle.dump(objects, outfile)
