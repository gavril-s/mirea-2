#include <iostream>
#include <vector>

#define STATIC_ARRAY_SIZE 10

// Static and dynamic

void read_array(int array[], int size=STATIC_ARRAY_SIZE)
{
    for (int i = 0; i < size; i++)
    {
        std::cin >> array[i];
    }
}

void print_array(int array[], int size=STATIC_ARRAY_SIZE)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

bool is_sorted(int array[], int size=STATIC_ARRAY_SIZE)
{
    for (int i = 1; i < size; i++)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}


// Static

int delete_multiples(int array[], int num)
{
    int deleted = 0;
    for (int i = 0; i < STATIC_ARRAY_SIZE - deleted; i++)
    {
        if (array[i] % num == 0)
        {
            for (int j = i; j < STATIC_ARRAY_SIZE - 1; j++)
            {
                array[j] = array[j + 1];
            }
            if (STATIC_ARRAY_SIZE > 0)
            {
                array[STATIC_ARRAY_SIZE - 1] = 0;
            }
            deleted++;
            i--;
        }
    }
    return deleted;
}

int insert_first(int array[], int num)
{
    for (int i = STATIC_ARRAY_SIZE - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    }

    if (STATIC_ARRAY_SIZE > 0)
    {
        array[0] = num;
        return 1;
    }

    return 0;
}


// Dynamic

int delete_multiples(int*& array, int size, int num)
{
    int deleted = 0;
    for (int i = 0; i < size - deleted; i++)
    {
        if (array[i] % num == 0)
        {
            for (int j = i; j < size - 1; j++)
            {
                array[j] = array[j + 1];
            }
            if (size > 0)
            {
                array[size - 1] = 0;
            }
            deleted++;
            i--;
        }
    }
    int new_size = size - deleted;
    realloc(array, sizeof(int) * new_size);
    return deleted;
}

int insert_first(int*& array, int size, int num)
{
    realloc(array, sizeof(int) * (size + 1));
    for (int i = size; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = num;
    return 1;
}


// std::vector

void read_array(std::vector<int>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        std::cin >> array[i];
    }
}

void print_array(const std::vector<int>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        std::cout << array[i] << ' ';
    }
}

bool is_sorted(const std::vector<int>& array)
{
    for (int i = 1; i < array.size(); i++)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}

void delete_multiples(std::vector<int>& array, int num)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] % num == 0)
        {
            array.erase(array.begin() + i);
            i--;
        }
    }
}

void insert_first(std::vector<int>& array, int num)
{
    array.push_back(0);
    for (int i = array.size() - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    }
    array[0] = num;
}

int main()
{
    int array_type = 0, operation = 0;
    const char* operation_prompt = 
        "Выберите операцию\n"
        "1 - определить, упорядоченны ли "
        "значения в массиве по возрастанию\n"
        "2 - если значения в массиве упорядочены, "
        "удалить элементы кратные введённому значению\n"
        "3 - если значения в массиве не упорядочены, "
        "вставить новый элемент перед первым элементом";
    

    std::cout << "Выберите тип массива, с которым будете работать\n" 
              << "1 - статический (размером " << STATIC_ARRAY_SIZE << ")\n"
              << "2 - динамический\n" 
              << "3 - std::vector\n";
    std::cin >> array_type;

    if (array_type == 1)
    {
        int static_array[STATIC_ARRAY_SIZE];
        std::cout << "Введите " << STATIC_ARRAY_SIZE 
                  << " чисел через пробел" << std::endl;
        read_array(static_array);

        std::cout << operation_prompt << std::endl;
        std::cin >> operation;

        if (operation == 1)
        {
            if (is_sorted(static_array))
            {
                std::cout << "Массив упорядочен по возрастанию" << std::endl;
            }
            else
            {
                std::cout << "Массив не упорядочен по возрастанию" << std::endl;
            }
        }
        else if (operation == 2)
        {
            if (is_sorted(static_array))
            {
                int num = 0;
                std::cout << "Массив упорядочен по возрастанию, "
                        << "введите число, все кратные которому вы "
                        << "хотите удалить: ";
                std::cin >> num;
                int deleted = delete_multiples(static_array, num);
                print_array(static_array, STATIC_ARRAY_SIZE - deleted);
            }
            else
            {
                std::cout << "Массив не упорядочен по возрастанию" << std::endl;
                print_array(static_array, STATIC_ARRAY_SIZE);
            }
        }
        else if (operation == 3)
        {
            if (!is_sorted(static_array))
            {
                int num = 0;
                std::cout << "Массив не упорядочен по возрастанию, "
                        << "введите число, все которое вы хотите "
                        << "вставить в начало массива: ";
                std::cin >> num;
                int inserted = insert_first(static_array, num);
                print_array(static_array, STATIC_ARRAY_SIZE);
            }
            else
            {
                std::cout << "Массив упорядочен по возрастанию" << std::endl;
                print_array(static_array, STATIC_ARRAY_SIZE);
            }
        }
        else 
        {
            std::cout << "Такого варианта нет!";
        }
    }
    else if (array_type == 2)
    {
        int size = 0;
        std::cout << "Введите размер массива: ";
        std::cin >> size;

        int* dynamic_array = new int[size];
        std::cout << "Введите " << size 
                  << " чисел через пробел" << std::endl;
        read_array(dynamic_array, size);

        std::cout << operation_prompt << std::endl;
        std::cin >> operation;

        if (operation == 1)
        {
            if (is_sorted(dynamic_array, size))
            {
                std::cout << "Массив упорядочен по возрастанию" << std::endl;
            }
            else
            {
                std::cout << "Массив не упорядочен по возрастанию" << std::endl;
            }
        }
        else if (operation == 2)
        {
            if (is_sorted(dynamic_array, size))
            {
                int num = 0;
                std::cout << "Массив упорядочен по возрастанию, "
                        << "введите число, все кратные которому вы "
                        << "хотите удалить: ";
                std::cin >> num;
                int deleted = delete_multiples(dynamic_array, size, num);
                print_array(dynamic_array, size - deleted);
            }
            else
            {
                std::cout << "Массив не упорядочен по возрастанию" << std::endl;
                print_array(dynamic_array, size);
            }
        }
        else if (operation == 3)
        {
            if (!is_sorted(dynamic_array, size))
            {
                int num = 0;
                std::cout << "Массив не упорядочен по возрастанию, "
                        << "введите число, все которое вы хотите "
                        << "вставить в начало массива: ";
                std::cin >> num;
                int inserted = insert_first(dynamic_array, size, num);
                print_array(dynamic_array, size + inserted);
            }
            else
            {
                std::cout << "Массив упорядочен по возрастанию" << std::endl;
                print_array(dynamic_array, size);
            }
        }
        else 
        {
            std::cout << "Такого варианта нет!";
        }
    }
    else if (array_type == 3)
    {
        int size = 0;
        std::cout << "Введите размер массива: ";
        std::cin >> size;

        std::vector<int> vector(size, 0);
        std::cout << "Введите " << size 
                  << " чисел через пробел" << std::endl;
        read_array(vector);

        std::cout << operation_prompt << std::endl;
        std::cin >> operation;

        if (operation == 1)
        {
            if (is_sorted(vector))
            {
                std::cout << "Массив упорядочен по возрастанию" << std::endl;
            }
            else
            {
                std::cout << "Массив не упорядочен по возрастанию" << std::endl;
            }
        }
        else if (operation == 2)
        {
            if (is_sorted(vector))
            {
                int num = 0;
                std::cout << "Массив упорядочен по возрастанию, "
                        << "введите число, все кратные которому вы "
                        << "хотите удалить: ";
                std::cin >> num;
                delete_multiples(vector, num);
                print_array(vector);
            }
            else
            {
                std::cout << "Массив не упорядочен по возрастанию" << std::endl;
                print_array(vector);
            }
        }
        else if (operation == 3)
        {
            if (!is_sorted(vector))
            {
                int num = 0;
                std::cout << "Массив не упорядочен по возрастанию, "
                        << "введите число, все которое вы хотите "
                        << "вставить в начало массива: ";
                std::cin >> num;
                insert_first(vector, num);
                print_array(vector);
            }
            else
            {
                std::cout << "Массив упорядочен по возрастанию" << std::endl;
                print_array(vector);
            }
        }
        else 
        {
            std::cout << "Такого варианта нет!";
        }
    }
    else
    {
        std::cout << "Такого варианта нет!";
    }

    return 0;
}