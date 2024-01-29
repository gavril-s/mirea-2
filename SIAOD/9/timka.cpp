#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct note
{
    int traint_num;
    string to;
    string from;
};

void create_rec(note *arr, int size){
    for (int i = 0; i < size; ++i){
        arr[i].traint_num = i+1;
        arr[i].from = "from" + to_string(100+i);
        arr[i].to = "to" + to_string(100+i);
    }
}

note get_last_rec(FILE* f, int size){
    fseek(f, (size - 1) * sizeof(note), SEEK_SET);
    note temp;
    fread(&temp, sizeof(note), 1, f);
    return temp;
}

void linear_search(FILE* f, int train_num, int size){
    for (int i = 0; i < size; ++i){
        fseek(f, (i) * sizeof(note), SEEK_SET);
        note temp;
        fread(&temp, sizeof(note), 1, f);
        if (temp.traint_num == train_num){
            cout << "последняя запись линейным поиском: номер поезда - " << temp.traint_num << " откуда - " << temp.from << " куда - " << temp.to << endl;  
            break;
        }
    }
}

struct search_record
{
    int key;
    int pos;
};

bool compare(search_record a, search_record b) 
{ 
    return a.key < b.key; 
}

void create_search_table(search_record* table, int size, FILE* f){
    int i = 0;
    while (i < size){
        fseek(f, (i) * sizeof(note), SEEK_SET);
        note temp;
        fread(&temp, sizeof(note), 1, f);
        table[i].key = temp.traint_num;
        table[i].pos = i;
        i++;
    }
    sort(table, table + size, compare);
}

void get_record(FILE* f, int pos){
    fseek(f, (pos) * sizeof(note), SEEK_SET);
    note temp;
    fread(&temp, sizeof(note), 1, f);
    cout << "последняя запись экспоненциальным поиском: номер поезда - " << temp.traint_num << " откуда - " << temp.from << " куда - " << temp.to << endl;  
}

void binary_search(search_record* table, int train_num, int left, int right, FILE* f){
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (table[mid].key == train_num){
            get_record(f, table[mid].pos);
            break;
        }
        else if (table[mid].key < train_num){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
}

void exponential_search(search_record* table, int train_num, int size, FILE* f){
    if (table[0].key == train_num){
        get_record(f, 0);
    }   
    int i = 1;
    while (i < size && table[i].key <= train_num){
        i = i*2;
    }
    binary_search(table, train_num, i/2, min(i, size-1), f);
}
 

int main()
{
    int size;
    cout << "введите размер" << endl;
    cin >> size;
    note* arr = new note[size];
    create_rec(arr, size);
    FILE* f = fopen("file9.txt", "wb+");
    int mode;
    while (mode != 0){
        cout << "чтобы вывести бинарный файл - нажмите 1" << endl;
        cout << "чтобы продемонстрировать линейный поиск - нажмите 2" << endl;
        cout << "чтобы продемонстрировать экспоненциальный поиск - нажмите 3" << endl;
        cin >> mode;
        if (mode == 1){
            size_t file_size = fwrite(arr, sizeof(note), size, f);
            note last_note = get_last_rec(f, size);
            cout << "количество записей: " << size << endl;
            cout << "размер файла: " << file_size << endl;
            cout << "последняя запись: номер поезда - " << last_note.traint_num << " откуда - " << last_note.from << " куда - " << last_note.to << endl;  
        }
        else if (mode == 2){
            auto start = high_resolution_clock::now();
            linear_search(f, size, size);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            cout << "время выполнения линейного поиска (микросекунды): " << duration.count() << endl;
        }
        else if (mode == 3){
            fclose(f);
            search_record * table = new search_record[size];
            f = fopen("file9.txt", "rb");
            auto start = high_resolution_clock::now();
            create_search_table(table, size, f);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            cout << "время создания структуры (микросекунды): " << duration.count() << endl;
            start = high_resolution_clock::now();
            exponential_search(table, size, size, f);
            end = high_resolution_clock::now();
            duration = duration_cast<microseconds>(end - start);
            cout << "время выполнения экспоненциального поиска (микросекунды): " << duration.count() << endl;
        }

    }
}
