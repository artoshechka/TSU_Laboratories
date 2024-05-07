#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

typedef unsigned char BASE;
typedef unsigned short DBASE;
#define BASE_SIZE (sizeof(BASE) * 8)

class bigNumber {
   private:
    BASE *coefficients;  // коэффициенты
    int length;          // фактическая длина
    int maxLength;       // максимально возможная длина

   public:
    // конструктор
    bigNumber(int maxLen = 1, int parameter = 0);

    // конструктор копирования
    bigNumber(const bigNumber &);

    // деструктор
    ~bigNumber();

    // перегрузка сравнений
    bool operator==(const bigNumber &) const;
    bool operator!=(const bigNumber &) const;
    bool operator<(const bigNumber &) const;
    bool operator>(const bigNumber &) const;
    bool operator<=(const bigNumber &) const;
    bool operator>=(const bigNumber &) const;

    // перегрузка операций
    bigNumber &operator=(const bigNumber &);
    bigNumber operator+(const bigNumber &) const;
    bigNumber &operator+=(const bigNumber &);
    bigNumber operator-(const bigNumber &) const;
    bigNumber &operator-=(const bigNumber &);

    // 16ричный ввод и вывод
    void printHex() const;
    void readHex();
};

// Конструктор
bigNumber::bigNumber(int maxLen, int parameter) : length(maxLen), maxLength(maxLen) {
    coefficients = new BASE[maxLen]();

    // Если параметр не равен 0, инициализируем случайными значениями
    if (parameter != 0) {
        for (int i = 0; i < maxLen; ++i) {
            coefficients[i] = rand();
        }
    }

    // Убираем ведущие нули
    while (length > 1 && coefficients[length - 1] == 0) {
        --length;
    }
}

// Конструктор копирования
bigNumber::bigNumber(const bigNumber &other) : length(other.length), maxLength(other.maxLength) {
    coefficients = new BASE[maxLength];
    for (int i = 0; i < maxLength; ++i) {
        coefficients[i] = other.coefficients[i];
    }
}

// Деструктор
bigNumber::~bigNumber() {
    delete[] coefficients;
}

// Оператор присваивания
bigNumber &bigNumber::operator=(const bigNumber &other) {
    if (this != &other) {
        delete[] coefficients;
        maxLength = other.maxLength;
        length = other.length;
        coefficients = new BASE[maxLength];
        for (int i = 0; i < maxLength; ++i) {
            coefficients[i] = other.coefficients[i];
        }
    }
    return *this;
}

// Печать числа в шестнадцатеричном формате
void bigNumber::printHex() const {
    for (int i = length - 1; i >= 0; i--) {
        cout.width(BASE_SIZE / 4);
        cout.fill('0');
        cout << hex << (int)coefficients[i] << " ";
    }
}

// Ввод числа в шестнадцатеричном формате
void bigNumber::readHex() {
    string inputString;
    getline(cin, inputString);
    int inputStringLength = inputString.length();
    int k = 0, j = 0;
    length = (inputStringLength - 1) / (BASE_SIZE / 4) + 1;
    maxLength = length;
    coefficients = new BASE[length];
    for (int i = 0; i < length; ++i) {
        coefficients[i] = 0;
    }

    // Преобразование строки в шестнадцатеричные коэффициенты
    for (int i = inputStringLength - 1; i >= 0; --i) {
        unsigned int temp = 0;
        if ('0' <= inputString[i] && inputString[i] <= '9') {
            temp = inputString[i] - '0';
        } else if ('a' <= inputString[i] && inputString[i] <= 'f') {
            temp = inputString[i] - 'a' + 10;
        } else if ('A' <= inputString[i] && inputString[i] <= 'F') {
            temp = inputString[i] - 'A' + 10;
        } else {
            throw invalid_argument("Invalid arguments.");
        }

        coefficients[j] |= temp << k;
        k += 4;
        if (k >= BASE_SIZE) {
            k = 0;
            j++;
        }
    }
}

// Оператор сложения
bigNumber bigNumber::operator+(const bigNumber &other) const {
    int maxOfLengths = max(length, other.length);
    int minOfLengths = min(length, other.length);
    int sumLength = maxOfLengths + 1;  // Инициализация с учетом возможного переноса
    bigNumber sumNumber(sumLength);    // Инициализация с учетом возможного переноса

    BASE carry = 0;
    for (int i = 0; i < minOfLengths; ++i) {
        DBASE tempSum = (DBASE)coefficients[i] + (DBASE)other.coefficients[i] + carry;
        sumNumber.coefficients[i] = (BASE)tempSum;
        carry = tempSum >> BASE_SIZE;  // Перенос для следующего разряда
    }

    for (int i = minOfLengths; i < length; ++i) {
        DBASE tempSum = (DBASE)coefficients[i] + carry;
        sumNumber.coefficients[i] = (BASE)tempSum;
        carry = tempSum >> BASE_SIZE;  // Перенос для следующего разряда
    }

    for (int i = minOfLengths; i < other.length; ++i) {
        DBASE tempSum = (DBASE)other.coefficients[i] + carry;
        sumNumber.coefficients[i] = (BASE)tempSum;
        carry = tempSum >> BASE_SIZE;  // Перенос для следующего разряда
    }

    sumNumber.coefficients[maxOfLengths] = carry;  // Установка старшего разряда

    // Корректировка длины результата
    sumNumber.length = sumLength;
    while (sumNumber.length > 1 && sumNumber.coefficients[sumNumber.length - 1] == 0) {
        --sumNumber.length;
    }

    return sumNumber;
}

// Оператор сложения с присваиванием
bigNumber &bigNumber::operator+=(const bigNumber &other) {
    *this = *this + other;
    return *this;
}

// Оператор вычитания
bigNumber bigNumber::operator-(const bigNumber &other) const {
    if (*this < other) {
        throw invalid_argument("Invalid argument");
    }

    bigNumber subtractionNumber(*this);  // Создание копии числа для вычитания

    int borrow = 0;
    for (int i = 0; i < other.length; ++i) {
        DBASE tempSub = (DBASE)subtractionNumber.coefficients[i] - (DBASE)other.coefficients[i] - borrow;
        if (tempSub < 0) {
            tempSub += (1 << BASE_SIZE);  // Коррекция для заема
            borrow = 1;
        } else {
            borrow = 0;
        }
        subtractionNumber.coefficients[i] = (BASE)tempSub;
    }

    for (int i = other.length; i < subtractionNumber.length; ++i) {
        DBASE tempSub = (DBASE)subtractionNumber.coefficients[i] - borrow;
        if (tempSub < 0) {
            tempSub += (1 << BASE_SIZE);  // Коррекция для заема
            borrow = 1;
        } else {
            borrow = 0;
        }
        subtractionNumber.coefficients[i] = (BASE)tempSub;
    }

    // Корректировка длины результата
    subtractionNumber.length = max(subtractionNumber.length, other.length);
    while (subtractionNumber.length > 1 && subtractionNumber.coefficients[subtractionNumber.length - 1] == 0) {
        --subtractionNumber.length;
    }

    return subtractionNumber;
}

// Оператор вычитания с присваиванием
bigNumber &bigNumber::operator-=(const bigNumber &other) {
    *this = *this - other;
    return *this;
}

bool bigNumber::operator==(const bigNumber &other) const {
    if (length != other.length) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        if (coefficients[i] != other.coefficients[i]) {
            return false;
        }
    }
    return true;
}

bool bigNumber::operator!=(const bigNumber &other) const {
    if (length != other.length) {
        return true;
    }
    for (int i = 0; i < length; ++i) {
        if (coefficients[i] != other.coefficients[i]) {
            return true;
        }
    }
    return false;
}

bool bigNumber::operator<(const bigNumber &other) const {
    if (length < other.length) {
        return true;
    }
    if (length > other.length) {
        return false;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] < other.coefficients[i]) {
            return true;
        }
        if (coefficients[i] > other.coefficients[i]) {
            return false;
        }
    }
    return false;
}

bool bigNumber::operator>(const bigNumber &other) const {
    if (length > other.length) {
        return true;
    }

    if (length < other.length) {
        return false;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] > other.coefficients[i]) {
            return true;
        }
        if (coefficients[i] < other.coefficients[i]) {
            return false;
        }
    }
    return false;
}

bool bigNumber::operator<=(const bigNumber &other) const {
    if (length > other.length) {
        return false;
    }
    if (length < other.length) {
        return true;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] < other.coefficients[i]) {
            return true;
        }
        if (coefficients[i] > other.coefficients[i]) {
            return false;
        }
    }
    return true;
}

bool bigNumber::operator>=(const bigNumber &other) const {
    if (length < other.length) {
        return false;
    }
    if (length > other.length) {
        return true;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] > other.coefficients[i]) {
            return true;
        }
        if (coefficients[i] < other.coefficients[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL));

    bigNumber numA(3, 3);
    bigNumber numB;

    cout << "Enter a big number in hexadecimal format: ";
    numB.readHex();

    cout << "A: ";
    numA.printHex();
    cout << endl
         << "B: ";
    numB.printHex();
    cout << endl;

    if (numA == numB) {
        cout << "A is equal to B" << endl;
    } else {
        cout << "A is not equal to B" << endl;
    }

    if (numA < numB) {
        cout << "A is less than B" << endl;
    } else {
        cout << "A is not less than B" << endl;
    }

    if (numA > numB) {
        cout << "A is greater than B" << endl;
    } else {
        cout << "A is not greater than B" << endl;
    }
    bigNumber numC = numA += numB;
    cout << "Summary: ";
    numC.printHex();

    cout << "\n"
         << "Subtraction: ";
    numC -= numB;
    numC.printHex();

    return 0;
}
