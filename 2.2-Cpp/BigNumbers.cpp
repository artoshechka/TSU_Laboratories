#include <cstring>
#include <ctime>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

typedef unsigned char BASE;
typedef unsigned short int DBASE;
#define BASE_SIZE (sizeof(BASE) * 8)
#define DBASE_SIZE (sizeof(DBASE) * 8)

class bigNumber {
   private:
    BASE* coefficients;  // коэффициенты
    int length;          // фактическая длина
    int maxLength;       // максимально возможная длина

   public:
    // конструктор
    bigNumber(int maxLen = 1, int parameter = 0);

    // конструктор копирования
    bigNumber(const bigNumber&);

    // деструктор
    ~bigNumber();

    // Нормирование
    void lenNorm();

    // перегрузка сравнений
    bool operator==(const bigNumber&) const;
    bool operator!=(const bigNumber&) const;
    bool operator<(const bigNumber&) const;
    bool operator>(const bigNumber&) const;
    bool operator<=(const bigNumber&) const;
    bool operator>=(const bigNumber&) const;

    // перегрузка операций
    bigNumber& operator=(const bigNumber&);
    bigNumber operator+(const bigNumber&) const;
    bigNumber& operator+=(const bigNumber&);
    bigNumber operator-(const bigNumber&) const;
    bigNumber& operator-=(const bigNumber&);
    bigNumber operator*(const BASE&) const;
    bigNumber& operator*=(const BASE&);
    bigNumber operator*(const bigNumber&) const;
    bigNumber& operator*=(const bigNumber&);
    bigNumber operator/(const BASE&) const;
    bigNumber operator%(const BASE&) const;
    bigNumber operator/(const bigNumber&) const;
    bigNumber operator%(const bigNumber&) const;

    // 16ричный ввод и вывод
    void printHex() const;
    void readHex();
};
void bigNumber::lenNorm() {
    while (length > 1 && coefficients[length - 1] == 0) {
        length--;
    }
}
// Конструктор
bigNumber::bigNumber(int maxLen, int parameter) : length(1), maxLength(maxLen) {
    coefficients = new BASE[maxLen];
    if (maxLen == 1) {
        length = 1;
    }
    for (int i = 0; i < maxLength; i++) {
        coefficients[i] = 0;
    }
    // Если параметр не равен 0, инициализируем случайными значениями
    if (parameter != 0) {
        length = maxLength;
        for (int i = 0; i < maxLength; i++) {
            coefficients[i] = rand();
        }
        if (sizeof(BASE) == sizeof(unsigned int)) {
            for (int i = 0; i < maxLength; ++i) {
                coefficients[i] <<= 16;
                coefficients[i] |= rand();
            }
        }
        lenNorm();
    }
}

// Конструктор копирования
bigNumber::bigNumber(const bigNumber& other) : length(other.length), maxLength(other.maxLength) {
    coefficients = new BASE[maxLength];
    int i = 0;
    while (i < maxLength) {
        coefficients[i] = other.coefficients[i];
        i++;
    }
}

// Деструктор
bigNumber::~bigNumber() {
    delete[] coefficients;
}

// Оператор присваивания
bigNumber& bigNumber::operator=(const bigNumber& other) {
    if (this != &other) {
        delete[] coefficients;
        maxLength = other.maxLength;
        length = other.length;
        coefficients = new BASE[maxLength];
        int i = 0;
        while (i < maxLength) {
            coefficients[i] = other.coefficients[i];
            i++;
        }
    }
    return *this;
}

// Печать числа в шестнадцатеричном формате
void bigNumber::printHex() const {
    int i = length - 1;
    while (i >= 0) {
        cout.width(BASE_SIZE / 4);
        cout.fill('0');
        cout << hex << (int)coefficients[i] << " ";
        i--;
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
    int i = 0;
    while (i < length) {
        coefficients[i] = 0;
        i++;
    }

    // Преобразование строки в шестнадцатеричные коэффициенты
    int idx = inputStringLength - 1;
    while (idx >= 0) {
        unsigned int temp = 0;
        if ('0' <= inputString[idx] && inputString[idx] <= '9') {
            temp = inputString[idx] - '0';
        } else if ('a' <= inputString[idx] && inputString[idx] <= 'f') {
            temp = inputString[idx] - 'a' + 10;
        } else if ('A' <= inputString[idx] && inputString[idx] <= 'F') {
            temp = inputString[idx] - 'A' + 10;
        } else {
            throw invalid_argument("Invalid arguments.");
        }

        coefficients[j] |= temp << k;
        k += 4;
        if (k >= BASE_SIZE) {
            k = 0;
            j++;
        }
        idx--;
    }
}

// Оператор сложения
bigNumber bigNumber::operator+(const bigNumber& other) const {
    int maxOfLengths = max(length, other.length);
    int minOfLengths = min(length, other.length);
    int sumLength = maxOfLengths + 1;  // Инициализация с учетом возможного переноса
    bigNumber sumNumber(sumLength);
    BASE carry = 0;
    int i = 0;
    while (i < minOfLengths) {
        DBASE tempSum = (DBASE)coefficients[i] + (DBASE)other.coefficients[i] + carry;
        sumNumber.coefficients[i] = (BASE)tempSum;
        carry = tempSum >> BASE_SIZE;
        i++;
    }

    while (i < length) {
        DBASE tempSum = (DBASE)coefficients[i] + carry;
        sumNumber.coefficients[i] = (BASE)tempSum;
        carry = tempSum >> BASE_SIZE;
        i++;
    }

    while (i < other.length) {
        DBASE tempSum = (DBASE)other.coefficients[i] + carry;
        sumNumber.coefficients[i] = (BASE)tempSum;
        carry = tempSum >> BASE_SIZE;
        i++;
    }

    sumNumber.coefficients[maxOfLengths] = carry;  // Установка старшего разряда

    // Корректировка длины результата
    sumNumber.length = sumLength;
    sumNumber.lenNorm();

    return sumNumber;
}

// Оператор сложения с присваиванием
bigNumber& bigNumber::operator+=(const bigNumber& other) {
    *this = *this + other;
    return *this;
}

// Оператор вычитания
bigNumber bigNumber::operator-(const bigNumber& other) const {
    if (*this < other) {
        throw invalid_argument("Invalid argument");  // Если текущее число меньше другого, выбрасываем исключение
    }

    int j = 0;
    int borrow = 0;  // Коэффициент заема
    DBASE temp;
    bigNumber subtractionNum(length);
    while (j < other.length) {
        // Вычисляем разность с учетом заема
        temp = ((DBASE)1 << BASE_SIZE) | coefficients[j];
        temp = temp - (DBASE)other.coefficients[j] - borrow;

        // Записываем значение разности
        subtractionNum.coefficients[j] = (BASE)temp;

        // Определяем новый коэффициент заема
        borrow = !(temp >> BASE_SIZE);

        j++;
    }

    while (j < length) {
        // Учитываем заем и вычитаем его
        temp = ((DBASE)1 << BASE_SIZE) | coefficients[j];
        temp -= borrow;

        // Записываем значение
        subtractionNum.coefficients[j] = (BASE)temp;

        // Определяем новый коэффициент заема
        borrow = !(temp >> BASE_SIZE);

        j++;
    }

    // Корректируем фактическую длину результата
    subtractionNum.length = length;
    subtractionNum.lenNorm();

    return subtractionNum;  // Возвращаем результат
}

// Оператор вычитания с присваиванием
bigNumber& bigNumber::operator-=(const bigNumber& other) {
    *this = *this - other;
    return *this;
}

// Умножение на отдельное значение типа BASE
bigNumber bigNumber::operator*(const BASE& multiplier) const {
    int j = 0;
    BASE carry = 0;
    bigNumber resNumber(length + 1);  // Создаем объект для результата с максимально возможной длиной
    DBASE tmp;

    while (j < length) {
        tmp = (DBASE)coefficients[j] * (DBASE)multiplier + (DBASE)carry;
        resNumber.coefficients[j] = (BASE)tmp;
        carry = (BASE)(tmp >> BASE_SIZE);
        j++;
    }
    resNumber.coefficients[j] = carry;
    resNumber.length = length + 1;
    resNumber.lenNorm();
    return resNumber;
}

// Оператор умножения с присваиванием для другого объекта bigNumber
bigNumber& bigNumber::operator*=(const BASE& multiplier) {
    *this = *this * multiplier;  // Используем операцию умножения для текущего объекта и другого bigNumber
    return *this;
}

// Умножение на другой объект bigNumber
bigNumber bigNumber::operator*(const bigNumber& other) const {
    if (other.length == 1 && other.coefficients[0] == 0) {
        return bigNumber();
    }
    bigNumber resNumber(length + other.length);  // Создаем объект для результата с достаточной длиной
    DBASE tmp;
    int j = 0;
    while (j < other.length) {
        if (other.coefficients[j] != 0) {
            BASE carry = 0;
            int i = 0;
            while (i < length) {
                tmp = (DBASE)coefficients[i] * (DBASE)other.coefficients[j] + (DBASE)resNumber.coefficients[i + j] + (DBASE)carry;  // Умножение текущих коэффициентов и прибавление переноса
                resNumber.coefficients[i + j] = (BASE)tmp;                                                                          // Записываем младшие разряды результата
                carry = (BASE)(tmp >> BASE_SIZE);                                                                                   // Обновляем перенос для следующей итерации
                i++;
            }
            resNumber.coefficients[length + j] = carry;  // Прибавляем оставшийся перенос к старшему разряду
        }
        j++;
    }
    resNumber.length = length + other.length;
    resNumber.lenNorm();
    return resNumber;
}

// Оператор умножения с присваиванием для отдельного значения BASE
bigNumber& bigNumber::operator*=(const bigNumber& other) {
    *this = *this * other;  // Используем операцию умножения для текущего объекта и множителя
    return *this;
}

// Оператор деления на BASE
bigNumber bigNumber::operator/(const BASE& number) const {
    int j = 0;
    DBASE tmp = 0;
    BASE left = 0;
    bigNumber resNumber(length);
    while (j < length) {
        tmp = ((DBASE)left << BASE_SIZE) + (DBASE)coefficients[length - 1 - j];
        resNumber.coefficients[length - 1 - j] = (BASE)(tmp / (DBASE)number);
        left = (BASE)(tmp % (DBASE)number);
        j++;
    }

    resNumber.length = length;
    resNumber.lenNorm();
    return resNumber;
}

// Оператор взятия остатка от деления на BASE
bigNumber bigNumber::operator%(const BASE& number) const {
    int j = 0;
    DBASE tmp = 0;
    BASE left = 0;
    bigNumber resNumber(1);

    while (j < length) {
        tmp = ((DBASE)left << BASE_SIZE) + (DBASE)coefficients[length - 1 - j];
        left = (BASE)(tmp % (DBASE)number);
        j++;
    }

    resNumber.coefficients[0] = left;
    resNumber.lenNorm();
    return resNumber;
}

bool bigNumber::operator==(const bigNumber& other) const {
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

bool bigNumber::operator!=(const bigNumber& other) const {
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

bool bigNumber::operator<(const bigNumber& other) const {
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

bool bigNumber::operator>(const bigNumber& other) const {
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

bool bigNumber::operator<=(const bigNumber& other) const {
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

bool bigNumber::operator>=(const bigNumber& other) const {
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

    bigNumber numC = numA + numB;
    cout << "Summary: ";
    numC.printHex();

    cout << "\nSubtraction: ";
    numC -= numB;
    numC.printHex();

    // Ввод целого числа
    int intNum;
    cout << "\nEnter an integer number: ";
    cin >> intNum;

    // Проверка умножения на целое число
    bigNumber numD = numA * intNum;
    cout << "\nMultiplication by integer: ";
    numD.printHex();

    // Проверка умножения на bigNumber
    bigNumber numE = numA * numB;
    cout << "\nMultiplication by BigNumber: ";
    numE.printHex();

    // Проверка деления на целое число
    bigNumber numF = numE / intNum;
    cout << "\nDevision by integer: ";
    numF.printHex();

    // Проверка остатка деления на bigNumber
    bigNumber numG = numE % intNum;
    cout << "\nThe remainder of the division by BigNumber: ";
    numG.printHex();

    return 0;
}
