"""
Создать txt-файл, вставить туда любую англоязычную статью из Википедии.
Реализовать одну функцию, которая выполняет следующие операции:
- прочитать файл построчно;
- непустые строки добавить в список;
- удалить из каждой строки все цифры, знаки препинания, скобки, кавычки и т.д. (остаются латинские буквы и пробелы);
- объединить все строки из списка в одну, используя метод join и пробел, как разделитель;
- создать словарь вида {“слово”: количество, “слово”: количество, … } для подсчета количества разных слов,
  где ключом будет уникальное слово, а значением - количество;
- вывести в порядке убывания 10 наиболее популярных слов, используя форматирование
  (вывод примерно следующего вида: “ 1 place --- sun --- 15 times \n....”);
- заменить все эти слова в строке на слово “PYTHON”;
- создать новый txt-файл;
- записать строку в файл, разбивая на строки, при этом на каждой строке записывать не более 100 символов
  при этом не делить слова.
"""


def wiki_function():
    # прочитать файл построчно
    # непустые строки добавить в список
    # удалить из каждой строки все цифры, знаки препинания, скобки, кавычки и т.д. (остаются латинские буквы и пробелы)
    beaver = open("beaver.txt", "r")
    lines_list = [line for line in beaver if line != "\n" and line != ""]
    for i in range(len(lines_list)):
        lines_list[i] = "".join(
            [i for i in lines_list[i] if i.isalpha() or i.isspace()]
        )
    beaver.close()

    # объединить все строки из списка в одну, используя метод join и пробел, как разделитель
    text = " ".join(lines_list)

    # создать словарь вида {“слово”: количество, “слово”: количество, … } для подсчета количества разных слов,
    # где ключом будет уникальное слово, а значением - количество
    words = dict()
    for word in text.split():
        if word not in words:
            words[word] = 1
        else:
            words[word] += 1
    words_list = [(word, words[word]) for word in words]
    words_list.sort(key=lambda x: -x[1])

    # вывести в порядке убывания 10 наиболее популярных слов, используя форматирование
    # (вывод примерно следующего вида: “ 1 place --- sun --- 15 times \n....”)
    place = 1
    for word, occurrences in words_list[:10]:
        print(f"{place} place --- {word} --- {occurrences} times")
        place += 1

    # заменить все эти слова в строке на слово “PYTHON”
    for word, occurrences in words_list[:10]:
        text = text.replace(f" {word} ", " PYTHON ")

    # создать новый txt-файл
    new_beaver = open("new_beaver.txt", "w")

    # записать строку в файл, разбивая на строки, при этом на каждой строке записывать не более 100 символов
    # при этом не делить слова
    formatted_text = ""
    current_line_length = 0
    for word in text.split():
        if current_line_length + len(word) + 2 > 100:
            formatted_text += f"\n{word}"
            current_line_length = len(word)
        elif current_line_length > 0:
            formatted_text += f" {word}"
            current_line_length += len(word) + 1
        else:
            formatted_text += word
            current_line_length += len(word)
    new_beaver.write(formatted_text)
    new_beaver.close()

    return 1


# Вызов функции
wiki_function()
