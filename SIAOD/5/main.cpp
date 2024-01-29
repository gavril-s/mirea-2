#include <iostream>
#include "list.h"

int main()
{
    list l;

    std::cout << "Введите элементы списка через пробел:\n";
    char pilot = std::cin.get();
    double elem = 0;
    while (pilot != '\n')
    {
        std::cin.putback(pilot);
        std::cin >> elem;
        l.append(elem);
        pilot = std::cin.get();
    }

    while (true)
    {
        std::cout << "Список: ";
        l.print();

        int choice = 0;
        std::cout << "Выберите функцию:\n"
                << "1 - Вставить два новых элемента перед последним\n"
                << "2 - Удалить из списка первое отрицательное значение\n"
                << "3 - Найти максимум в списке и переместить его в конец\n"
                << "4 - Выход\n";
        std::cin >> choice;
        if (choice == 1)
        {
            double value1 = 0, value2 = 0;
            std::cout << "Введите 2 значения для новых узлов: ";
            std::cin >> value1 >> value2;

            l.insert_two_before_last(value1, value2);
        }
        else if (choice == 2)
        {
            l.delete_first_negative();
        }
        else if (choice == 3)
        {
            l.move_max_to_end();
        }
        else if (choice == 4)
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