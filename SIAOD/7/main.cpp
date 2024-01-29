#include <iostream>
#include <string>
#include <algorithm>
#include "double_stack.h"
#include "array_stack.h"

int precedence(char op)
{
    switch (op)
    {
    case '+': case '-':
        return 0;
    case '*': case '/':
        return 1;
    case '^':
        return 2;
    default:
        return -1;
    }
} 

std::string infix_to_prefix(std::string expression)
{
    array_stack stack;
    std::string prefix;

    std::reverse(expression.begin(), expression.end());
    for (char& ch : expression)
    {
        if (ch == '(' || ch == ')')
        {
            ch = (ch == '(' ? ')' : '(');
        }
    }

    for (char ch : expression)
    {
        switch (ch)
        {
        case '(':
            stack.push(ch);
            break;
        case ')':
            while (stack.top() != '(')
            {
                prefix += stack.pop();
            }
            stack.pop();
            break;
        case '+': 
        case '-':
        case '*':
        case '/':
        case '^':
            if (stack.is_empty())
            {
                stack.push(ch);
            }
            else
            {
                if (stack.top() != '(')
                {
                    while (precedence(ch) < precedence(stack.top()) ||
                           (precedence(ch) == precedence(stack.top()) && 
                            ch == '^'))
                    {
                        prefix += stack.pop();
                        if (stack.is_empty()) 
                        {
                            break;
                        }
                    }
                }
                stack.push(ch);
            }
            break;
        case ' ':
            break;
        default:
            prefix += ch;
            break;
        }
    }

    while (!stack.is_empty())
    {
        prefix += stack.pop();
    }
    std::reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main()
{
    double_stack stack;

    while (true)
    {
        int choice = 0;
        std::cout << "Выберите функцию:\n"
                  << "1 - Перевести арифметическое выражение из инфиксной"
                  << " записи в префиксную\n"
                  << "2 - Провести операцию со стэком\n"
                  << "3 - Выход\n";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string expression;
            std::cout << "Введите выражение: ";

            std::cin.get();
            char head = std::cin.get();
            while (head != '\n')
            {
                expression += head;
                head = std::cin.get();
            }

            std::cout << "Результат: " << infix_to_prefix(expression) << '\n';
        }
        else if (choice == 2)
        {
            int stack_side_choice = 0;
            side stack_side;
            std::cout << "Выберите стэк:\n"
                      << "1 - левый\n"
                      << "2 - правый\n";
            std::cin >> stack_side_choice;

            if (stack_side_choice == 1)
            {
                stack_side = left;
            }
            else if (stack_side_choice == 2)
            {
                stack_side = right;
            }
            else
            {
                std::cout << "Такого варианта нет!\n";
                continue;
            }

            int operation = 0;
            std::cout << "Выберите операцию:\n"
                      << "1 - Проверить, пуст ли стэк\n"
                      << "2 - Посмотреть вершину стэка\n"
                      << "3 - Положить элемент в стэк\n"
                      << "4 - Убрать верхний элемент стэка\n"
                      << "5 - Очистить стэк\n";
            std::cin >> operation;

            if (operation == 1)
            {
                bool empty = stack.is_empty(stack_side);
                std::cout << (empty ? "Стэк пуст" : "Стэк не пуст") << '\n';
            }
            else if (operation == 2)
            {
                if (!stack.is_empty(stack_side))
                {
                    int value = stack.top(stack_side);
                    std::cout << "Вершина стэка: " << value << '\n';
                }
                else
                {
                    std::cout << "Стэк пуст\n";
                }
            }
            else if (operation == 3)
            {
                int value = 0;
                std::cout << "Введите значение нового элемента: ";
                std::cin >> value;
                stack.push(stack_side, value);
            }
            else if (operation == 4)
            {
                if (!(stack.is_empty(stack_side)))
                {
                    std::cout << "Удалённый элемент: "
                              << stack.pop(stack_side) << '\n';
                }
                else
                {
                    std::cout << "Стэк пуст\n";
                }
            }
            else if (operation == 5)
            {
                stack.clear(stack_side);
                std::cout << "Стэк очищен\n";
            }
            else
            {
                std::cout << "Такого варианта нет!\n";
            }
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