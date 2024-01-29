import math


def T(x, a):
    if x <= 0:
        raise ValueError("x должен был положительным")
    return (
        (math.atan(math.sqrt(abs(x))) + x**2)
        / (math.log(2 * x) + math.e ** abs(-x - 5))
        + 3 * a
        - 0.2
    )


def k(x, a, b):
    if x == 0 or a == 0 or b == 0:
        raise ValueError("ни один аргумент не может быть равен 0")
    return (
        math.sin(6 * a) ** 2
        + 8 * math.tan(b**3)
        - (5 / (a * b * x)) * 3.82**a
    )

print(T(1, 0))
print(T(1, 1))
print(T(10, -5))
print(k(1, 1, 1))
print(k(1, 2, 3))
print(k(10, 10, 100))