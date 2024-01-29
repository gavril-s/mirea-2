#include <iostream>
#include <cstring>
#include <string>

#define MAXIMUM_CODE_LENGTH 1024
#define MAXIMUM_WORD_LENGTH 64
#define NUMBER_OF_KEYWORDS 97

// https://en.cppreference.com/w/cpp/keyword
const char* const keywords[NUMBER_OF_KEYWORDS] = {
    "alignas",
    "alignof",
    "and",
    "and_eq",
    "asm",
    "atomic_cancel",
    "atomic_commit",
    "atomic_noexcept",
    "auto",
    "bitand",
    "bitor",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "char8_t",
    "char16_t",
    "char32_t",
    "class",
    "compl",
    "concept",
    "const",
    "consteval",
    "constexpr",
    "constinit",
    "const_cast",
    "continue",
    "co_await",
    "co_return",
    "co_yield",
    "decltype",
    "default",
    "delete",
    "do",
    "double",
    "dynamic_cast",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "float",
    "for",
    "friend",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "noexcept",
    "not",
    "not_eq",
    "nullptr",
    "operator",
    "or",
    "or_eq",
    "private",
    "protected",
    "public",
    "reflexpr",
    "register",
    "reinterpret_cast",
    "requires",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_assert",
    "static_cast",
    "struct",
    "switch",
    "synchronized",
    "template",
    "this",
    "thread_local",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while",
    "xor",
    "xor_eq"
};

void print_keywords(char* code)
{
    int count = 0;
    char current_word[MAXIMUM_WORD_LENGTH] = "";
    int last_symbol_index = -1;

    std::cout << "Список ключевых слов в коде:" << std::endl;

    for (int i = 0; code[i] != '\0'; i++)
    {
        if (code[i] == ' ' || code[i] == '\n' || code[i] == '\t')
        {
            for (int j = 0; j < NUMBER_OF_KEYWORDS; j++)
            {
                if (strcmp(current_word, keywords[j]) == 0)
                {
                    std::cout << keywords[j] << std::endl;
                    count++;
                }
            }
            memset(current_word, 0, sizeof(current_word));
            last_symbol_index = -1;
        }
        else if (last_symbol_index + 1 < MAXIMUM_WORD_LENGTH)
        {
            last_symbol_index++;
            current_word[last_symbol_index] = code[i];
        }
    }

    std::cout << "Всего ключевых слов: " << count << std::endl;
}

void print_keywords(std::string code)
{
    int count = 0;
    std::string current_word = "";

    std::cout << "Список ключевых слов в коде:" << std::endl;

    for (int i = 0; code[i] != '\0'; i++)
    {
        if (code[i] == ' ' || code[i] == '\n' || code[i] == '\t')
        {
            for (int j = 0; j < NUMBER_OF_KEYWORDS; j++)
            {
                if (current_word == keywords[j])
                {
                    std::cout << keywords[j] << std::endl;
                    count++;
                }
            }
            current_word.clear();
        }
        else
        {
            current_word += code[i];
        }
    }

    std::cout << "Всего ключевых слов: " << count << std::endl;
}

int main()
{
    int mode = 0;
    std::cout << "Выберите тип строки:" << std::endl
              << "1 - char[]" << std::endl
              << "2 - std::string" << std::endl;
    std::cin >> mode;

    if (mode == 1)
    {
        std::cout << "Введите код (для завершения ввода нажмите enter 2 раза):" 
                  << std::endl;
                  
        char code[MAXIMUM_CODE_LENGTH] = "";
        int last_symbol_index = -1;

        char current = ' ';
        char prev = ' ';
        while (!(current == '\n' && prev == '\n'))
        {
            prev = current;
            current = std::cin.get();

            if (last_symbol_index + 2 < MAXIMUM_CODE_LENGTH)
            {
                last_symbol_index++;
                code[last_symbol_index] = current;
            }
            else
            {
                break;
            }
        }
        
        print_keywords(code);
    }
    else if (mode == 2)
    {
        std::cout << "Введите код (для завершения ввода нажмите enter 2 раза):" 
                  << std::endl;

        std::string code;
    
        char current = ' ';
        char prev = ' ';
        while (!(current == '\n' && prev == '\n'))
        {
            prev = current;
            current = std::cin.get();
            code += current;
        }
    
        print_keywords(code);
    }
    else
    {
        std::cout << "Такого варианта нет!" << std::endl;
    }
    
    return 0;
}