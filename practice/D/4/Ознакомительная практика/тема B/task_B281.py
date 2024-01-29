# Написать функцию balance, которая получает небольшую чековую книжку в виде строки.
# На первой строчке: первоначальный баланс, на последующих через пробел: номер чека, категория, цена.
# Вернуть строку - видоизмененный чек с построчным добавлением остатка баланса.
# А на последних строчках добавить потраченную сумму и остаток.
#
# Примеры:
# book = "1000.00
# 125 Market 125.45
# 126 Hardware 34.95
# 127 Video 7.45
# 128 Book 14.32
# 129 Gasoline 16.10"
# balance(book) ==>
# "Original_Balance:_1000.00
# 125_Market_125.45_Balance_874.55
# 126_Hardware_34.95_Balance_839.60
# 127_Video_7.45_Balance_832.15
# 128_Book_14.32_Balance_817.83
# 129_Gasoline_16.10_Balance_801.73
# Total_expense__198.27
# Average_expense__39.65"

import traceback


def balance(book):
    allowed = ". \t\n\r"
    book = "".join([i for i in book if i.isalnum() or i in allowed])
    lines = book.split("\n")
    if "" in lines:
        lines.remove("")

    original_balance = 0
    balance = 0
    items = 0
    for i in range(len(lines)):
        if i == 0:
            balance = float(lines[0])
            original_balance = balance
            lines[0] = f"Original Balance: {lines[0]}"
        else:
            items += 1
            line = lines[i].split()
            balance -= float(line[-1])
            lines[
                i
            ] = f"{line[0]} {line[1]} {float(line[2]):.2f} Balance {balance:.2f}"

    total_expense = original_balance - balance
    average_exprense = total_expense / items
    lines.append(f"Total expense  {total_expense:.2f}")
    lines.append(f"Average expense  {average_exprense:.2f}")
    return "\n".join(lines)


# Тесты
b1 = """1000.00!=
125 Market !=:125.45
126 Hardware =34.95
127 Video! 7.45
128 Book :14.32
129 Gasoline ::16.10
"""

b1sol = """Original Balance: 1000.00
125 Market 125.45 Balance 874.55
126 Hardware 34.95 Balance 839.60
127 Video 7.45 Balance 832.15
128 Book 14.32 Balance 817.83
129 Gasoline 16.10 Balance 801.73
Total expense  198.27
Average expense  39.65"""

b2 = """1233.00
125 Hardware;! 24.8?;
123 Flowers 93.5
127 Meat 120.90
120 Picture 34.00
124 Gasoline 11.00
123 Photos;! 71.4?;
122 Picture 93.5
132 Tyres;! 19.00,?;
129 Stamps 13.6
129 Fruits{} 17.6
129 Market;! 128.00?;
121 Gasoline;! 13.6?;"""

b2sol = """Original Balance: 1233.00
125 Hardware 24.80 Balance 1208.20
123 Flowers 93.50 Balance 1114.70
127 Meat 120.90 Balance 993.80
120 Picture 34.00 Balance 959.80
124 Gasoline 11.00 Balance 948.80
123 Photos 71.40 Balance 877.40
122 Picture 93.50 Balance 783.90
132 Tyres 19.00 Balance 764.90
129 Stamps 13.60 Balance 751.30
129 Fruits 17.60 Balance 733.70
129 Market 128.00 Balance 605.70
121 Gasoline 13.60 Balance 592.10
Total expense  640.90
Average expense  53.41"""


try:
    assert balance(b1) == b1sol
    assert balance(b2) == b2sol
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")
