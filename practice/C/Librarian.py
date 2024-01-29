import traceback
from Person import Person
from Reader import Reader


class Librarian(Person):
    def __init__(
        self, first_name, last_name, age, id_number, position, work_schedule={}
    ):
        super().__init__(first_name, last_name, age)
        self.id_number = id_number
        self.position = position
        self.work_schedule = work_schedule

    def change_position(self, new_position):
        self.position = new_position

    def add_work_schedule(self, day, hours):
        self.work_schedule[day] = hours

    def remove_work_schedule(self, day):
        try:
            del self.work_schedule[day]
        except KeyError:
            raise Exception("Не найдено расписания на этот день")

    def change_work_schedule(self, day, new_hours):
        self.work_schedule[day] = new_hours

    def __str__(self):
        return f"Имя: {self.first_name} {self.last_name}, Возраст: {self.age}, Номер удостоверения: {self.id_number}, Должность: {self.position}"


def test_librarian():
    try:
        librarian = Librarian(
            "Иванов",
            "Иван",
            30,
            "00001",
            "Библиотекарь",
            {"пн": "10:00-18:00", "вт": "10:00-18:00"},
        )
        reader = Reader("Петров", "Петр", 20, "12345", {"00001": "2022-01-01"})

        librarian.change_position("Главный библиотекарь")
        assert librarian.position == "Главный библиотекарь"

        librarian.add_work_schedule("ср", "10:00-18:00")
        assert librarian.work_schedule["ср"] == "10:00-18:00"

        librarian.change_work_schedule("пн", "11:00-19:00")
        assert librarian.work_schedule["пн"] == "11:00-19:00"

        librarian.remove_work_schedule("вт")
        assert "вт" not in librarian.work_schedule

        assert (
            str(librarian)
            == "Имя: Иванов Иван, Возраст: 30, Номер удостоверения: 00001, Должность: Главный библиотекарь"
        )
    except AssertionError:
        print("TEST ERROR")
        traceback.print_exc()
    except Exception as err:
        print("ERROR:", err)
    else:
        print("TEST PASSED")


# test_librarian()
