#include <iostream>

typedef unsigned short BASE;
#define BASE_SIZE (sizeof(BASE) * 8)

using namespace std;
class bigNumber {
   private:
    BASE *coef;
    int lenght;
    int maxLenght;

   public:
    bigNumber(int maxLen = 1, int number = 0);
    bigNumber(const bigNumber &);
    ~bigNumber() {
        if (coef) {
            delete[] coef;
            coef = nullptr;
        }
    };
    bigNumber operator=(const bigNumber &);
};

bigNumber::bigNumber(int maxLen, int number) {
    coef = new BASE[maxLen];
    int size = BASE_SIZE;
    int len = maxLen;
    int maxLen = maxLen;
    for (int i = 0; i < maxLenght; ++i) {
        coef[i] = 0;
    }
    if (number != 0) {
        for (int i = 0; i < maxLen; ++i) {
            coef[i] = rand();
            if (size > 12) {
                for (int j = 0; j < ceil(size / 12); ++j) {
                    coef[i] <<= ((j * 12) | rand());
                }
            }
        }
        while (len > 1 && coef[len - 1] == 0) {
            --len;
        }
    }
}

bigNumber::bigNumber(const bigNumber &other) {
    maxLenght = other.maxLenght;
    lenght = other.lenght;
    coef = new BASE[maxLenght];
    for (int i = 0; i < maxLenght; ++i) {
        coef[i] = other.coef[i];
    }
}

bigNumber bigNumber::operator=(const bigNumber &other) {
    if (this != &other) {
        delete[] coef;
        maxLenght = other.maxLenght;
        lenght = other.lenght;
        coef = new BASE[maxLenght];
        for (int i = 0; i < maxLenght; ++i) {
            coef[i] = other.coef[i];
        }
    }
    return *this;
}
