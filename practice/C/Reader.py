import traceback
from Person import Person


class Reader(Person):
    def __init__(self, first_name, last_name, age, card_number, card={}):
        super().__init__(first_name, last_name, age)
        self.card_number = card_number
        self.card = card

    def add_book(self, book_number, date):
        self.card[book_number] = date

    def get_book_date(self, book_number):
        try:
            return self.card[book_number]
        except KeyError:
            raise Exception("Книга не найдена")

    def print_card(self):
        print(f"Номер билета: {self.card_number}")
        for book_number, date in self.card.items():
            print(f"Номер книги: {book_number}, Дата взятия: {date}")

    def __str__(self):
        return f"Имя: {self.first_name} {self.last_name}, Возраст: {self.age}, Номер билета: {self.card_number}"


def test_reader():
    try:
        reader = Reader("Иван", "Иванов", 25, "123456")
        assert reader.first_name == "Иван"
        assert reader.last_name == "Иванов"
        assert reader.age == 25
        assert reader.card_number == "123456"
        assert reader.card == {}

        reader.add_book("123", "2022-03-27")
        assert reader.card == {"123": "2022-03-27"}

        assert reader.get_book_date("123") == "2022-03-27"

        expected_output = "Имя: Иван Иванов, Возраст: 25, Номер билета: 123456"
        assert str(reader) == expected_output
    except AssertionError:
        print("TEST ERROR")
        traceback.print_exc()
    except Exception as err:
        print("ERROR:", err)
    else:
        print("TEST PASSED")


# test_reader()
