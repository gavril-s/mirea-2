#include <iostream>
#include <string>
#include "queue.h"

std::string rebase_iterative(int number, int base)
{
    std::string res_reverse;
    while (number > 0)
    {
        res_reverse += std::to_string(number % base);
        number /= base;
    }

    std::string res;
    for (int i = res_reverse.length(); i >= 0; i--)
    {
        res += res_reverse[i];
    }

    if (res.length() == 0)
    {
        res = "0";
    }
    return res;
}

std::string rebase_recursive(int number, int base, bool root=true)
{
    if (number == 0)
    {
        return (root ? "0" : "");
    }
    std::string digit = std::to_string(number % base);
    return rebase_recursive(number / base, base, false) + digit;
}

void delete_queue(queue& q)
{
    if (!q.empty())
    {
        q.elems.print();
        q.pop();
        delete_queue(q);
    }
}

int main()
{
    while (true)
    {
        int choice = 0;
        std::cout << "Выберите функцию:\n"
                << "1 - Перевести число в выбранную систему счисления\n"
                << "2 - Удалить очередь\n"
                << "3 - Выход\n";
        std::cin >> choice;

        if (choice == 1)
        {
            int number = 0, base = 0;
            std::cout << "Введите число: ";
            std::cin >> number;
            std::cout << "Введите основание системы счисления (от 2 до 10): ";
            std::cin >> base;

            if (base >= 2 && base <= 10)
            {
                int way = 0;
                std::cout << "Выберите реализацию функции перевода числа в другую систему счисления:\n"
                          << "1 - Итеративная\n"
                          << "2 - Рекурсивная\n";
                std::cin >> way;

                if (way == 1)
                {
                    std::cout << "Результат перевода: "
                              << rebase_iterative(number, base) << '\n';
                }
                else if (way == 2)
                {
                    std::cout << "Результат перевода: "
                              << rebase_recursive(number, base) << '\n';
                }
                else 
                {
                    std::cout << "Такого варианта нет!\n";
                }
            }
            else 
            {
                std::cout << "Некорректное основание!\n";
            }
        }
        else if (choice == 2)
        {
            queue q;

            std::cout << "Введите элементы очереди через пробел:\n";
            std::cin.get();
            char pilot = std::cin.get();
            double elem = 0;
            while (pilot != '\n')
            {
                std::cin.putback(pilot);
                std::cin >> elem;
                q.push(elem);
                pilot = std::cin.get();
            }

            std::cout << "Очередь: ";
            q.elems.print();
            delete_queue(q);
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            std::cout << "Такого варианта нет!\n";
        }
    }

    return 0;
}