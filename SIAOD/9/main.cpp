#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

struct specialization
{
    int code;
    std::string university_name;
    int start_year;
};

void fill_records(specialization* specializations, int size)
{
    for (int i = 0; i < size; i++)
    {
        specializations[i].code = i + 1;
        specializations[i].university_name = "uni №" + std::to_string(i + 1);
        specializations[i].start_year = 2000 + i;
    }
}

specialization* get_record(FILE* file, int position)
{
    fseek(file, (position) * sizeof(specialization), SEEK_SET);
    specialization* spec = (specialization*)malloc(sizeof(specialization));
    fread(spec, sizeof(*spec), 1, file);
    return spec;
}

specialization* get_last_record(FILE* file, int size)
{
    return get_record(file, size - 1);
}

void linear_search(FILE* file, int size, int code)
{
    for (int i = 0; i < size; ++i)
    {
        specialization* spec = get_record(file, i);
        if (spec->code == code)
        {
            std::cout << "Запись найдена линейным поиском\n";
            return;
        }
        free(spec);
    }
    std::cout << "Запись не была найдена линейным поиском\n";
}

struct search_record
{
    int key;
    int position;
};

bool compare_search_records(search_record lhs, search_record rhs) 
{ 
    return lhs.key < rhs.key; 
}

void create_search_table(search_record* table, int size, FILE* file)
{
    for (int i = 0; i < size; i++)
    {
        specialization* spec = get_record(file, i);
        table[i].key = spec->code;
        table[i].position = i;
        free(spec);
    }
    std::sort(table, table + size, compare_search_records);
}

void binary_search(search_record* table, int code, int left, int right)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (table[mid].key == code)
        {
            std::cout << "Запись найдена бинарным поиском\n";
            return;
        }
        else if (table[mid].key < code)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    std::cout << "Запись не была найдена бинарным поиском\n";
}

int main()
{
    int size = 0;
    std::cout << "Введите количество записей: ";
    std::cin >> size;

    specialization* specializations = new specialization[size];
    fill_records(specializations, size);

    FILE* file = fopen("records.bin", "wb+");
    size_t file_size = fwrite(specializations, sizeof(specialization), size, file);
    fclose(file);

    int mode = 0;
    while (true)
    {
        std::cout << "1 - Информация о файле\n"
                  << "2 - Замер времени работы линейного поиска\n"
                  << "3 - Замер времени работы бинарного поиска\n"
                  << "4 - Выход\n";
        std::cin >> mode;

        file = fopen("records.bin", "rb");
        if (mode == 1)
        {
            specialization* last_record = get_last_record(file, size);

            std::cout << "Количество записей: " << size << '\n'
                      << "Размер файла: " << size * sizeof(specialization) << " байт\n"
                      << "Последняя запись:\n"
                      << "\tКод: " << last_record->code << '\n'
                      << "\tНазвание ВУЗа: " << last_record->university_name << '\n'
                      << "\tГод начала обуения: " << last_record->start_year << '\n';

            free(last_record); 
        }
        else if (mode == 2)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            linear_search(file, size, size);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            std::cout << "Время выполнения линейного поиска (мкс): " << duration.count() << std::endl;
        }
        else if (mode == 3)
        {
            search_record* table = new search_record[size];

            auto begin = std::chrono::high_resolution_clock::now();
            create_search_table(table, size, file);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            std::cout << "Время создания таблицы для поиска (мкс): " << duration.count() << std::endl;

            begin = std::chrono::high_resolution_clock::now();
            binary_search(table, size, 0, size - 1);
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
            
            std::cout << "Время выполнения бинарного поиска (мкс): " << duration.count() << std::endl;

            delete table;
        }
        else if (mode == 4)
        {
            fclose(file);
            break;
        }
        else
        {
            std::cout << "Такого варианта нет!\n";
        }
        fclose(file);
    }

    return 0;
}