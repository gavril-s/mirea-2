# Написать функцию fragmentation, которая получает на вход строку s и целое положительное число count,
# разбивает строку на подстроки по count символоа и возвращает список этих строк. Если в последней
# подстроке недостаточно символов, дополнить ее символами нижнего подчеркивания.
#
# Примеры:
# fragmentation("this is my string", 4) ==> ["this", " is ", "my s", "trin", "g____"]

import traceback


def fragmentation(s, count):
    res = [""]
    for symbol in s:
        if len(res[-1]) >= count:
            res.append(symbol)
        else:
            res[-1] += symbol
    if len(res[-1]) < count:
        res[-1] += "_" * (count - len(res[-1]))
    return res


# Тесты
try:
    assert fragmentation("this is my string", 4) == [
        "this",
        " is ",
        "my s",
        "trin",
        "g___",
    ]
    assert fragmentation("Tomorrow is going to be raining.", 8) == [
        "Tomorrow",
        " is goin",
        "g to be ",
        "raining.",
    ]
    assert fragmentation("", 5) == ["_____"]
    assert fragmentation("abcdef", 1) == ["a", "b", "c", "d", "e", "f"]
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")
