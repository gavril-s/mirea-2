#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <random>
#include <ctime>

std::string read_file(std::string filename)
{
    std::ifstream f(filename);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

void fill_LPS(std::string pattern, std::vector<int>& lps, int& comparisons)
{
    int len = 0;
    lps[0] = 0;

    for (int i = 1; i < lps.size(); i++)
    {
        comparisons += 2;
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
        }
        else
        {
            comparisons++;
            if (len != 0)
            {
                len = lps[len - 1];
                i--;
            }
            else
            {
                lps[i] = 0;
            }
        }
    }
}

std::vector<int> KMP(std::string text, std::string pattern, int& comparisons)
{
    std::vector<int> found_indexes;
    std::vector<int> lps(pattern.length());
    fill_LPS(pattern, lps, comparisons);

    int i = 0, j = 0;
    comparisons++;
    while ((text.length() - i) >= (pattern.length() - j))
    {
        comparisons++;
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        comparisons++;
        if (j == pattern.length())
        {
            found_indexes.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < text.length() && pattern[j] != text[i])
        {
            comparisons += 3;
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return found_indexes;
}
 
bool is_phone_number(std::string input)
{
    std::regex pattern("\\+7-\\d{3}-\\d{3}-\\d{2}-\\d{2}");
    return std::regex_match(input, pattern);
}

int main()
{
    while (true)
    {
        std::cout << "1 - Поиск выступавших в тексте протокола заседания\n"
                  << "2 - Проверка строки на соответствие шаблону номера телефона\n"
                  << "3 - Тестирование алгоритма Кнута-Морисса-Прата\n"
                  << "4 - Выход\n";

        int mode = 0;
        std::cin >> mode;
        if (mode == 1)
        {
            std::vector<std::string> filenames;
            std::cout << "Введите имена файлов, содержащих протоколы "
                      << "собраний через пробел (enter - вариант по умолчанию):\n";
            std::string name;
            std::cin.get();
            char next = std::cin.get();
            while (next != '\n')
            {
                std::cin.putback(next);
                std::cin >> name;
                filenames.push_back(name);
                next = std::cin.get();
            }
            if (filenames.size() == 0)
            {
                filenames.push_back("text10.txt");
            }

            std::cout << std::endl;
            for (std::string filename : filenames)
            {
                std::string pattern = "Слушали сообщение: ";
                std::string text = read_file(filename);

                int comparisons = 0;
                auto start = std::chrono::high_resolution_clock::now();
                std::vector<int> indexes = KMP(text, pattern, comparisons);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = 
                    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Время поиска: " << duration.count() << " мкс" << std::endl;
                std::cout << "Количество сравнений: " << comparisons << std::endl;

                std::vector<std::string> full_names;
                for (int i = 0; i < indexes.size(); i++)
                {
                    std::string full_name;
                    for (int j = indexes[i] + pattern.length();; j++)
                    {
                        if (text[j] == ' ')
                        {
                            full_name += text.substr(j, 7);
                            break;
                        }
                        else
                        {
                            full_name += text[j];
                        }
                    }
                    full_names.push_back(full_name);
                }

                if (full_names.size() == 0)
                {
                    std::cout << "Выступавшие не найдены! (" << filename << ")\n";
                }
                else
                {
                    std::cout << "Список имён выступавших (" << filename << "):\n";
                    for (std::string name : full_names)
                    {
                        std::cout << '\t' << name << '\n';
                    }
                }
                std::cout << std::endl;
            }
        }
        else if (mode == 2)
        {
            std::cout << "Введите строку для поверки её на соответствие "
                      << "шаблону номера телефона:\n";
            std::string input;
            std::cin >> input;

            if (is_phone_number(input))
            {
                std::cout << "Строка является номером телефона!\n";
            }
            else
            {
                std::cout << "Строка не является номером телефона!\n";
            }
        }
        else if (mode == 3)
        {
            std::srand(time(NULL));
            std::string charset = "abcdefghijklmnopqrstuvwxyz";

            int text_length = 0;
            std::cout << "Введите количество символов в тексте для поиска: ";
            std::cin >> text_length;

            int wanted_string_length = 0;
            std::cout << "Введите количество символов в искомой строке: ";
            std::cin >> wanted_string_length;

            std::string text, wanted_string;
            for (int i = 0; i < text_length; i++)
            {
                text += charset[std::rand() % charset.length()];

                if (i >= text_length - wanted_string_length)
                {
                    wanted_string += text[i];
                }
            }

            std::ofstream of("test_file.txt");
            of << text;
            of.close();

            int comparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> indexes = KMP(text, wanted_string, comparisons);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = 
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Время поиска: " << duration.count() << " мкс" << std::endl;
            std::cout << "Количество сравнений: " << comparisons << std::endl;
        }
        else if (mode == 4)
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