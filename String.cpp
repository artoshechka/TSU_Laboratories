#include <bits/stdc++.h>

using namespace std;
// Класс "Строка"
class String
{
    char *str;
    int len;

public:
    String(int l = 0);
    String(const char *);
    String(String &);
    ~String()
    {
        if (str)
            delete[] str;
        str = NULL;
    }
    int strLength();
    String &operator=(const String &);
    char &operator[](int);
    bool operator==(String &);
    bool operator!=(String &);
    String operator+(const String &);
    String &operator+=(const String &);
    friend istream &operator>>(istream &, String &);
    friend ostream &operator<<(ostream &, String &);
    int BMSearch(String &);
};
String::String(int l)
{
    len = l;
    str = new char[len];
    str[0] = '\0';
}
String::String(const char *other)
{
    len = strlen(other);
    str = new char[len + 1];
    strcpy(str, other);
}

String::String(String &other)
{
    len = other.len;
    str = new char[len + 1];
    strcpy(str, other.str);
}

int String::strLength()
{
    return len;
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        len = other.len;
        delete[] str;
        str = new char[len + 1];
        strcpy(str, other.str);
    }
    return *this;
}
bool String::operator!=(String &other)
{
    return strcmp(str, other.str) != 0;
}
bool String::operator==(String &other)
{
    return strcmp(str, other.str) == 0;
}
char &String::operator[](int i)
{
    if (i < 0 || i >= len)
    {
        cout << "OUT OF RANGE";
        return str[0];
    }
    return str[i];
}
String String::operator+(const String &other)
{
    String temp(len + other.len);
    strcpy(temp.str, str);
    strcat(temp.str, other.str);
    return temp;
}
String &String::operator+=(const String &other)
{
    char *temp = new char[len + 1];
    strcpy(temp, str);
    len += other.len;
    delete[] str;
    str = new char[len + 1];
    strcpy(str, temp);
    strcat(str, other.str);
    delete[] temp;
    return *this;
}
std::istream &operator>>(istream &in, String &other)
{
    other.len = 0;
    int size = 1;
    char *temp = new char[size];
    char c = in.get();
    while (c != '\n')
    {
        temp[(other.len)++] = c;
        if (other.len >= size)
        {
            size *= 2;
            char *newTemp = new char[size];
            strcpy(newTemp, temp);
            delete[] temp;
            temp = newTemp;
        }
        c = in.get();
    }
    temp[other.len] = '\0';
    other = temp;
    delete[] temp;
    return in;
}
std::ostream &operator<<(ostream &out, String &other)
{
    out << other.str;
    return out;
}
int String::BMSearch(String &pattern)
{
    int patternLen = pattern.strLength();
    int textLen = strLength();

    if (patternLen == 0)
    {
        return 0; // Пустой шаблон всегда считается найденным
    }

    // Создаем таблицу смещений для символов в шаблоне
    int badChar[256];
    for (int i = 0; i < 256; ++i)
    {
        badChar[i] = patternLen;
    }

    for (int i = 0; i < patternLen - 1; ++i)
    {
        badChar[static_cast<unsigned char>(pattern[i])] = patternLen - 1 - i;
    }

    // Начинаем поиск
    int i = patternLen - 1; // Индекс символа в тексте
    int j = patternLen - 1; // Индекс символа в шаблоне

    while (i < textLen)
    {
        if (str[i] == pattern[j])
        {
            // Символы совпадают, двигаемся назад по тексту и шаблону
            if (j == 0)
            {
                return i; // Найдено совпадение
            }
            --i;
            --j;
        }
        else
        {
            // Символы не совпадают, используем таблицу смещений для выбора максимального смещения
            i += max(badChar[static_cast<unsigned char>(str[i])], patternLen - 1 - j);
            j = patternLen - 1;
        }
    }

    return -1; // Совпадение не найдено
}
int main()
{
    // Создание объектов класса String
    String s1("Hello");
    String s2(" World");
    String s3;

    // Проверка методов класса String
    cout << "s1: " << s1 << endl; // Печать содержимого s1
    cout << "s2: " << s2 << endl; // Печать содержимого s2

    s3 = s1 + s2;                           // Конкатенация s1 и s2 и присвоение результата s3
    cout << "s3 (s1 + s2): " << s3 << endl; // Печать s3

    s1 += s2;                                // Изменение s1 путем добавления s2
    cout << "s1 (s1 += s2): " << s1 << endl; // Печать s1

    if (s1 == s3)
    {
        cout << "s1 and s3 are equal" << endl; // Проверка на равенство s1 и s3
    }
    else
    {
        cout << "s1 and s3 are not equal" << endl;
    }

    if (s1 != s2)
    {
        cout << "s1 and s2 are not equal" << endl; // Проверка на неравенство s1 и s2
    }
    else
    {
        cout << "s1 and s2 are equal" << endl;
    }

    // Использование оператора []
    cout << "Character at index 3 in s3: " << s3[3] << endl;

    // Ввод с клавиатуры
    cout << "Enter a string: ";
    cin >> s3;
    cout << "You entered: " << s3 << endl;
    // Ввод строки и паттерна с клавиатуры
    String inputString, pattern;

    cout << "Enter a string: ";
    cin >> inputString;

    cout << "Enter a pattern to search: ";
    cin >> pattern;

    // Вывод введенных строк
    cout << "Input string: " << inputString << endl;
    cout << "Pattern to search: " << pattern << endl;

    // Поиск паттерна в строке
    int index = inputString.BMSearch(pattern);

    if (index != -1)
    {
        cout << "Pattern found at index: " << index << endl;
    }
    else
    {
        cout << "Pattern not found" << endl;
    }

    return 0;
}