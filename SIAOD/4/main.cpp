#include <iostream>
#include <string>
#include "Sits.h"

#define DELIMITER_LENGTH 100

void print_sit_info(const Sit& sit)
{
    std::cout << "Фильм: \"" << sit.movie_name << "\", "
              << "дата и время: " << sit.date.day << '.' 
              << sit.date.month << '.' << sit.date.year << ' '
              << sit.time.hours << ':' << sit.time.minutes 
              << ':' << sit.time.seconds << ", "
              << "ряд и место: " << sit.row << ' ' << sit.place << ", "
              << "зал: " << (sit.room == Room::big ? "большой" : "малый") 
              << '\n';
}

void print_sits_info(const Sits& sits)
{
    for (int i = 0; i < DELIMITER_LENGTH; i++)
    {
        std::cout << '-';
    }
    std::cout << '\n';

    for (int i = 0; i < sits.size; i++)
    {
        print_sit_info(sits.sits[i]);
    }

    for (int i = 0; i < DELIMITER_LENGTH; i++)
    {
        std::cout << '-';
    }
    std::cout << '\n';
}

void read_movie_name(char movie_name[MAX_MOVIE_NAME_LENGTH])
{
    std::cout << "Введите название фильма: ";
    std::cin >> movie_name;
}

void read_date(Date& date)
{
    std::cout << "Введите дату (день, месяц и год через пробел): ";
    std::cin >> date.day >> date.month >> date.year;
}

void read_time(Time& time)
{
    std::cout << "Введите время (часы, минуты и секунды через пробел): ";
    std::cin >> time.hours >> time.minutes >> time.seconds;
}

void read_sit_info(Sit& sit)
{
    read_movie_name(sit.movie_name);
    read_date(sit.date);
    read_time(sit.time);
    std::cout << "Введите место в зале (номер ряда и номер места через пробел): ";
    std::cin >> sit.row >> sit.place;
    std::cout << "Введите номер зала (маленький - 1, большой - 2): ";
    std::cin >> sit.room;
}

int main()
{
    Sits sits;
    
    while (true)
    {
        std::cout << "Выберите операцию:\n"
                << "1 - Заполнение записи по одному проданному билету с клавиатуры\n"
                << "2 - Удаление записи по заданной дате\n"
                << "3 - Определение количества свободных мест на заданный фильм в указанную дату и время\n"
                << "4 - Выход\n";
        int choice = 0;
        std::cin >> choice;

        if (choice == 1)
        {
            Sit sit;
            read_sit_info(sit);
            sits.insert(sit);
            print_sits_info(sits);
        }
        else if (choice == 2)
        {
            Date date;
            read_date(date);
            sits.delete_by_date(date);

            print_sits_info(sits);          
        }
        else if (choice == 3)
        {
            char movie_name[MAX_MOVIE_NAME_LENGTH];
            Date date;
            Time time;
            read_movie_name(movie_name);
            read_date(date);
            read_time(time);

            std::cout << "Свободных мест - "
                      << sits.free_places(movie_name, date, time)
                      << '\n';
        }
        else
        {
            break;
        }
    }

    return 0;
}