"""
Каждый класс реализовать в отдельном модуле, импортируя их в производные модули.
Создать класс Person с полями имя, фамилия, возраст. Добавить конструктор класса.
Создать производный от Person класс Reader. Новые поля: номер читательского билета, читательский билет
    (словарь вида номер книжки: дата взятия книжки из библиотеки). Определить конструктор, с вызовом родительского
    конструктора. Определить функции добавления новой книги в читательский билет, получения даты по номеру книги,
    форматированной печати всего читательского билета. Переопределить метод преобразования в строку для печати
    основной информации (ФИ, возраст, номер читательского билета).
Создать производный от Person класс Librarian. Новые поля: номер удостоверения, должность, график работы
    (словарь вида день недели: часы работы). Определить конструктор, с вызовом родительского конструктора.
    Определить функции изменения должности, добавления, удаления и изменения графика работы. Переопределить
    метод преобразования в строку для печати основной информации (ФИ, возраст, номер удостоверения, должность).
Создать класс Library. Поля: название библиотеки, адрес, список читателей (список экземпляров класса Reader),
    список библиотекарей (список экземпляров класса Librarian). Определить конструктор. Переопределить метод
    преобразования в строку для печати всей информации о библиотеке (с использованием переопределения в
    классах Reader и Librarian). Переопределить методы получения количества читателей функцией len, получения
    читателя по индексу, изменения по индексу, удаления по индексу (пусть номера читателей считаются с 1,
    а индекс 0 – список всех библиотекарей). Переопределить операции + и - для добавления или удаления читателя.
    Добавить функцию создания txt-файла и записи всей информации в него (в том числе читательского билета
    читателей и рабочих часов библиотекарей).
Предусмотреть хотя бы в 3 местах обработку возможных исключений.
В каждом модуле провести подробное тестирование всех создаваемых объектов и функций.
"""
