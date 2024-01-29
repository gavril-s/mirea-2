import traceback


class Person:
    def __init__(self, first_name, last_name, age):
        self.first_name = first_name
        self.last_name = last_name
        self.age = age


def test_person():
    try:
        person = Person("Иван", "Иванов", 25)

        assert person.first_name == "Иван"
        assert person.last_name == "Иванов"
        assert person.age == 25
    except AssertionError:
        print("TEST ERROR")
        traceback.print_exc()
    except Exception as err:
        print("ERROR:", err)
    else:
        print("TEST PASSED")


# test_person()
