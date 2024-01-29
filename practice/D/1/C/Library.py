import traceback
from .Person import Person
from .Reader import Reader
from .Librarian import Librarian
from .Logger import Logger


class Library:
    def __init__(self, name, address, readers, librarians):
        self.name = name
        self.address = address
        self.readers = readers
        self.librarians = librarians
        Logger.log(Logger.LogKey.CRE, "Library: создан экземпляр")

    def __str__(self):
        result = f'Библиотека "{self.name}" по адресу: {self.address}\n'
        result += "Библиотекари:\n"
        for librarian in self.librarians:
            result += f"\t{str(librarian)}\n"
        result += "Читатели:\n"
        for i, reader in enumerate(self.readers):
            result += f"\t{i+1}. {str(reader)}\n"
        return result

    def __len__(self):
        return len(self.readers)

    def __getitem__(self, index):
        try:
            if index == 0:
                return self.librarians
            else:
                return self.readers[index - 1]
        except IndexError:
            raise Exception("Нет читателя с таким индексом")

    def __setitem__(self, index, value):
        self.readers[index - 1] = value
        Logger.log(Logger.LogKey.INF, "Library: изменён читатель")

    def __delitem__(self, index):
        try:
            del self.readers[index - 1]
        except IndexError:
            Logger.log(
                Logger.LogKey.ERR,
                "Library: __delitem__: нет читателя с тами индексом",
            )
            raise Exception("Нет читателя с таким индексом")

    def __add__(self, reader):
        self.readers.append(reader)
        Logger.log(Logger.LogKey.INF, "Library: добавлен читатель")

    def __sub__(self, reader):
        self.readers.remove(reader)
        Logger.log(Logger.LogKey.INF, "Library: удалён читатель")

    def create_txt_file(self, filename):
        with open(filename, "w", encoding="utf-8") as f:
            f.write(str(self))


def test_library():
    try:
        # Создаем тестовых читателей и библиотекарей
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

        # Создаем тестовую библиотеку
        library = Library(
            "Главная библиотека",
            "ул. Пушкина, д.10",
            [reader1, reader2],
            [librarian1, librarian2],
        )

        # Проверяем конструктор
        assert library.name == "Главная библиотека"
        assert library.address == "ул. Пушкина, д.10"
        assert len(library.readers) == 2
        assert len(library.librarians) == 2

        # Проверяем метод __str__
        expected_output = (
            'Библиотека "Главная библиотека" по адресу: ул. Пушкина, д.10\n'
        )
        expected_output += "Библиотекари:\n"
        expected_output += "\tИмя: Сидорова Елена, Возраст: 40, Номер удостоверения: 222-333, Должность: Библиотекарь\n"
        expected_output += "\tИмя: Кузнецова Ольга, Возраст: 35, Номер удостоверения: 333-444, Должность: Главный библиотекарь\n"
        expected_output += "Читатели:\n"
        expected_output += (
            "\t1. Имя: Иванов Иван, Возраст: 30, Номер билета: 111-222\n"
        )
        expected_output += (
            "\t2. Имя: Петров Петр, Возраст: 25, Номер билета: 222-333\n"
        )
        assert str(library) == expected_output

        # Проверяем метод create_txt_file
        library.create_txt_file("test_library.txt")
        with open("test_library.txt", "r", encoding="utf-8") as f:
            file_content = f.read()
        assert file_content == expected_output

        # Проверяем метод __len__
        assert len(library) == 2

        # Проверяем метод __getitem__
        assert library[0] == [librarian1, librarian2]
        assert library[1] == reader1
        assert library[2] == reader2

        # Проверяем метод __setitem__
        reader3 = Reader("Сидоров", "Игорь", 20, "444-555")
        library[1] = reader3
        assert library[1] == reader3

        # Проверяем метод __delitem__
        del library[2]
        assert len(library.readers) == 1

        # Проверяем метод __add__
        new_reader = Reader("Сидоров", "Сидор", 30, "333-444")
        library + new_reader
        assert len(library.readers) == 2
        assert library.readers[1].first_name == "Сидоров"

        # Проверяем метод __sub__
        library - new_reader
        assert len(library.readers) == 1
        assert new_reader not in library.readers
    except AssertionError:
        print("TEST ERROR")
        traceback.print_exc()
    except Exception as err:
        print("ERROR:", err)
    else:
        print("TEST PASSED")


# test_library()
