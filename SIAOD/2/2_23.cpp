#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <vector>

#define ROWS 3
#define COLUMNS 3

int rand_int()
{
    return (std::rand() % 201) - 100;
}

// Static

void print_matrix(int matrix[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void read_matrix(int matrix[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            std::cin >> matrix[i][j];
        }
    }
}

void fill_matrix_random(int matrix[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            matrix[i][j] = rand_int();
        }
    }
}

int determinant(int matrix[ROWS][COLUMNS], int from_row=0, int from_column=0)
{
    if (ROWS - from_row == 1 && COLUMNS - from_column == 1)
    {
        return matrix[from_row][from_column];
    }

    for (int i = from_row + 1; i < ROWS; i++)
    {
        for (int j = from_column + 1; j < COLUMNS; j++)
        {
            matrix[i][j] *= matrix[from_row][from_column];
            matrix[i][j] -= matrix[i][from_column] * matrix[from_row][j];
        }
        matrix[i][from_column] = 0;
    }

    int det = determinant(matrix, from_row + 1, from_column + 1);
    for (int i = from_row + 2; i < ROWS; i++)
    {
        det /= matrix[from_row][from_column];
    }
    return det;
}

// Dynamic

void print_matrix(int** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void read_matrix(int** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cin >> matrix[i][j];
        }
    }
}

void fill_matrix_random(int** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = rand_int();
        }
    }
}

int determinant(int** matrix, int rows, int columns, 
                int from_row=0, int from_column=0)
{
    if (rows - from_row == 1 && columns - from_column == 1)
    {
        return matrix[from_row][from_column];
    }

    for (int i = from_row + 1; i < rows; i++)
    {
        for (int j = from_column + 1; j < columns; j++)
        {
            matrix[i][j] *= matrix[from_row][from_column];
            matrix[i][j] -= matrix[i][from_column] * matrix[from_row][j];
        }
        matrix[i][from_column] = 0;
    }

    int det = determinant(matrix, rows, columns, 
                          from_row + 1, from_column + 1);
    for (int i = from_row + 2; i < rows; i++)
    {
        det /= matrix[from_row][from_column];
    }
    return det;
}

// std::vector

int count_different_pairs(std::string str)
{
    const char* letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::vector<bool>> matrix (52, std::vector<bool>(52, false));
    for (int i = 0; i < str.length() - 1; i++)
    {
        int first_index = -1;
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            first_index = str[i] - 'a';
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            first_index = str[i] - 'A' + 26;   
        }

        int second_index = -1;
        if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
        {
            second_index = str[i + 1] - 'a';
        }
        else if (str[i + 1] >= 'A' && str[i + 1] <= 'Z')
        {
            second_index = str[i + 1] - 'A' + 26;   
        }

        if (first_index != -1 && second_index != -1)
        {
            matrix[first_index][second_index] = true;
        }
    }

    int count = 0;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j])
            {
                count++;
            }
        }
    }

    return count;
}

int main()
{
    std::srand(std::time(nullptr));

    int mode = 0;
    std::cout << "1 - Найти определитель квадратной матрицы методом Гаусса\n"
              << "2 - Определить количество различных пар букв в тексте\n";
    std::cin >> mode;
    
    if (mode == 1)
    {
        int matrix[ROWS][COLUMNS];

        int array_type = 0;
        std::cout << "Выберите тип массива:\n"
                  << "1 - статический (размера "
                  << ROWS << " x " << COLUMNS << ")\n"
                  << "2 - диинамический\n";
        std::cin >> array_type;

        if (array_type == 1)
        {
            int fill_method = 0;
            std::cout << "Выберите способ заполнения матрицы:\n"
                      << "1 - вручную (с клаиватуры)\n"
                      << "2 - автоматически (случайными значениями)\n";
            std::cin >> fill_method;
            
            if (fill_method == 1)
            {
                read_matrix(matrix);
            }
            else if (fill_method == 2)
            {
                fill_matrix_random(matrix);
                print_matrix(matrix);
            }
            else
            {
                std::cout << "Такого варианта нет!" << std::endl;
            }

            std::cout << "Определитель матрицы равен "
                      << determinant(matrix);
        }
        else if (array_type == 2)
        {
            int rows = 0, columns = 0;
            std::cout << "Введите количество строк (оно же количество столбцов)\n";
            std::cin >> rows;
            columns = rows;

            int** matrix = new int*[rows];
            for (int row = 0; row < rows; row++)
            {
                matrix[row] = new int[columns];
            }

            int fill_method = 0;
            std::cout << "Выберите способ заполнения матрицы:\n"
                      << "1 - вручную (с клаиватуры)\n"
                      << "2 - автоматически (случайными значениями)\n";
            std::cin >> fill_method;
            
            if (fill_method == 1)
            {
                read_matrix(matrix, rows, columns);
            }
            else if (fill_method == 2)
            {
                fill_matrix_random(matrix, rows, columns);
                print_matrix(matrix, rows, columns);
            }
            else
            {
                std::cout << "Такого варианта нет!" << std::endl;
            }

            std::cout << "Определитель матрицы равен "
                      << determinant(matrix, rows, columns);

            for (int row = 0; row < rows; row++)
            {
                delete[] matrix[row];
            }          
            delete[] matrix;
        }
        else
        {
            std::cout << "Такого варианта нет!" << std::endl;
        }
    }
    else if (mode == 2)
    {
        std::string text;

        std::cout << "Введите текст:\n";
        char tmp = ' ';
        while (tmp != '.')
        {
            tmp = std::cin.get();
            text += tmp;
        }

        std::cout << "Количество различных пар букв: "
                  << count_different_pairs(text);
    }
    else
    {
        std::cout << "Такого варианта нет!" << std::endl;
    }

    return 0;
}