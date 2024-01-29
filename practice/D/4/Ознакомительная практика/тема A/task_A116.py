# Написать функцию all_different(start, finish), которая определяет количество чисел
# в интервале между числами start и finish (их не считая), в записи которых все цифры разные.
#
# Примеры:
# all_different(20,33) ==> 11 (кроме числа 22)
# all_different(0,101) ==> 90

import traceback


def all_different(start, finish):
    digits = [str(i) for i in range(10)]
    count = 0
    for num in range(start + 1, finish):
        not_reapeating = True
        for digit in digits:
            if str(num).count(digit) > 1:
                not_reapeating = False
                break
        if not_reapeating:
            count += 1
    return count


# Тесты
try:
    assert all_different(20, 33) == 11
    assert all_different(0, 10) == 9
    assert all_different(0, 101) == 90
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")
