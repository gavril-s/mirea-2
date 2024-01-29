import pickle
import datetime
from C.Person import Person
from C.Reader import Reader
from C.Librarian import Librarian
from C.Library import Library

with open("objects.pickle", "rb") as infile:
    objects = pickle.load(infile)

person = objects[0]
reader = objects[1]
librarian = objects[2]
library = objects[3]

reader.add_book("123", "2022-03-27")

librarian.change_position("Главный библиотекарь")
librarian.add_work_schedule("ср", "10:00-18:00")
librarian.change_work_schedule("пн", "11:00-19:00")
librarian.remove_work_schedule("вт")

new_reader = Reader("Сидоров", "Игорь", 20, "444-555")
library[1] = new_reader
del library[2]
new_reader = Reader("Сидоров", "Сидор", 30, "333-444")
library + new_reader
library - new_reader
