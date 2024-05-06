#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

typedef unsigned short BASE;
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
    bool operator==(const bigNumber &);
    bool operator!=(const bigNumber &);
    bool operator<(const bigNumber &);
    bool operator>(const bigNumber &);
    bool operator<=(const bigNumber &);
    bool operator>=(const bigNumber &);

    // перегрузка операций
    bigNumber &operator=(const bigNumber &);

    // 16ричный ввод и вывод
    void printHex() const;
    void readHex();
};

bigNumber::bigNumber(int maxLen, int parameter) : length(maxLen), maxLength(maxLen) {
    coefficients = new BASE[maxLen]();

    if (parameter != 0) {
        for (int i = 0; i < maxLen; ++i) {
            coefficients[i] = rand();
        }
    }

    while (length > 1 && coefficients[length - 1] == 0) {
        --length;
    }
}

bigNumber::bigNumber(const bigNumber &other) : length(other.length), maxLength(other.maxLength) {
    coefficients = new BASE[maxLength];
    for (int i = 0; i < maxLength; ++i) {
        coefficients[i] = other.coefficients[i];
    }
}

bigNumber::~bigNumber() { delete[] coefficients; }

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

void bigNumber::printHex() const {
    for (int i = length - 1; i >= 0; --i) {
        cout << coefficients[i] << " ";
    }
}

void bigNumber::readHex() {
    string inputString;
    getline(cin, inputString);

    int k = 0, j = 0;
    for (int i = inputString.length() - 1; i >= 0; --i) {
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

        coefficients[j] |= temp << (k * 4);
        k++;
        if (k >= BASE_SIZE / 4) {
            k = 0;
            j++;
        }
    }
}

bool bigNumber::operator==(const bigNumber &other) {
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

bool bigNumber::operator!=(const bigNumber &other) {
    if (length == other.length) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        if (coefficients[i] == other.coefficients[i]) {
            return false;
        }
    }
    return true;
}

bool bigNumber::operator<(const bigNumber &other) {
    if (length < other.length) {
        return true;
    } else if (length > other.length) {
        return false;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] < other.coefficients[i]) {
            return true;
        } else if (coefficients[i] > other.coefficients[i]) {
            return false;
        }
    }
    return false;
}

bool bigNumber::operator>(const bigNumber &other) {
    if (length > other.length) {
        return true;
    } else if (length < other.length) {
        return false;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] > other.coefficients[i]) {
            return true;
        } else if (coefficients[i] < other.coefficients[i]) {
            return false;
        }
    }
    return false;
}

bool bigNumber::operator<=(const bigNumber &other) {
    if (length > other.length) {
        return false;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] <= other.coefficients[i]) {
            return true;
        } else if (coefficients[i] > other.coefficients[i]) {
            return false;
        }
    }
    return false;
}

bool bigNumber::operator>=(const bigNumber &other) {
    if (length < other.length) {
        return false;
    }
    for (int i = length - 1; i >= 0; --i) {
        if (coefficients[i] >= other.coefficients[i]) {
            return true;
        } else if (coefficients[i] < other.coefficients[i]) {
            return false;
        }
    }
    return false;
}

int main() {
    srand(time(NULL));

    bigNumber numA(1, 1);
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

    return 0;
}
