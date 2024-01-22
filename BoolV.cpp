#include <bits/stdc++.h>

int BITS = sizeof(unsigned int) * 8;
using namespace std;

/// Класс булев вектор
class BoolV {
    unsigned int *v;
    int nbit, m; // nbit – количество бит вектора, m – количество элементов массива v
public:
    BoolV(int nn = 1); // формируется булев вектор из nn бит; все биты со значениями 0
    BoolV(const char *); // формируется булев вектор по строке из нулей и единиц
    BoolV(const BoolV &);

    ~BoolV();

    void Set1(int); // устанавливает указанный бит в 1
    void Set0(int); // устанавливает указанный бит в 0
    int operator[](int);

    BoolV operator=(const BoolV &);

    bool operator==(const BoolV &); // равенство векторов
    BoolV operator|(const BoolV &);

    BoolV operator&(const BoolV &);

    BoolV operator~();

    friend ostream &operator<<(ostream &, const BoolV &);

    friend istream &operator>>(istream &, BoolV &);

    // Дополнительно (не обязательно)
    int weight(); //вес вектора
    BoolV operator<<(int); //сдвиг на k бит влево
    BoolV operator>>(int); //сдвиг на k бит вправо
};

BoolV::BoolV(int nn) {
    nbit = nn;
    m = (nbit - 1) / 32 + 1;
    v = new unsigned int[m];
    for (int i = 0; i < m; ++i) {
        v[i] = 0;
    }
}

BoolV::BoolV(const char *str) {
    nbit = strlen(str);
    m = (nbit - 1) / 32 + 1;
    v = new unsigned int[m];
    for (int i = 0; i < m; ++i) {
        v[i] = 0;
    }
    for (int i = 0; i < nbit; ++i) {
        if (str[nbit - i - 1] == '1') {
            v[i / 32] = v[i / 32] | (1 << (i % 32));
        }
    }
}

BoolV::BoolV(const BoolV &other) {
    nbit = other.nbit;
    m = other.m;
    v = new unsigned int[m];
    for (int i = 0; i < m; ++i) {
        v[i] = other.v[i];
    }
}

BoolV::~BoolV() {
    if (v)
        delete[] v;
    v = NULL;
}

void BoolV::Set1(int bit) {
    if ((bit < nbit) && (bit >= 0)) {
        v[bit / 32] = v[bit / 32] | (1 << (bit % 32));//для эдемента в котором лежит бит
    } else {
        cout << "out of bit indexes";
    }

}

void BoolV::Set0(int bit) {
    if ((bit < nbit) && (bit >= 0)) {
        v[bit / 32] = v[bit / 32] & ~(1 << (bit % 32));//для эдемента в котором лежит бит
    } else {
        cout << "out of bit indexes";
    }
}

int BoolV::operator[](int bitId) {
    if ((bitId < nbit) && (bitId >= 0)) {
        return ((v[bitId / 32] & (1 << (bitId % 32))) == 0 ? 0 : 1);
    } else {
        cout << "out of bit indexes";
        return -1;
    }
}

BoolV BoolV::operator=(const BoolV &other) {
    if (this != &other) {
        nbit = other.nbit;
        m = other.m;
        delete[] v;
        v = new unsigned int[m];
        for (int i = 0; i < other.m; ++i) {
            v[i] = other.v[i];
        }
    }
    return *this;
}

bool BoolV::operator==(const BoolV &other) {
    if (nbit != other.nbit || m != other.m) {
        return false;
    }
    for (int i = 0; i < m; ++i) {
        if (v[i] != other.v[i]) {
            return false;
        }
    }
    return true;
}

BoolV BoolV::operator|(const BoolV &other) {
    BoolV temp(nbit > other.nbit ? *this : other);
    for (int i = 0; i < (nbit < other.nbit ? other.m : m); ++i) {
        temp.v[i] |= (nbit < other.nbit ? other.v[i] : v[i]);
    }
    return temp;
}

BoolV BoolV::operator&(const BoolV &other) {
    BoolV temp(nbit > other.nbit ? *this : other);
    for (int i = 0; i < (nbit < other.nbit ? other.m : m); ++i) {
        temp.v[i] &= (nbit < other.nbit ? other.v[i] : v[i]);
    }
    return temp;
}


ostream &operator<<(ostream &out, const BoolV &boolV) {
    for (int i = boolV.nbit - 1; i >= 0; --i) {
        out << ((boolV.v[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1);
    }
    return out;
}

istream &operator>>(istream &in, BoolV &boolV) {
    string str;
    in >> str;
    BoolV temp(str.c_str());
    boolV = temp;
    return in;

}

BoolV BoolV::operator~() {
    BoolV temp(*this);
    for (int i = 0; i < m; ++i) {
        temp.v[i] = ~temp.v[i];
    }
    return temp;
}

int main() {
    // Пример использования булевого вектора
    BoolV bv1(8); // Создание булевого вектора из 8 бит
    cout << "created bv1: " << bv1 << endl;
    bv1.Set1(1); // Установка второго бита в 1
    bv1.Set1(2); // Установка четвертого бита в 1

    cout << "bv1: " << bv1 << endl; // Вывод на экран

    BoolV bv2("10101010"); // Создание булевого вектора из строки
    cout << "bv2: " << bv2 << endl;

    BoolV bv3 = bv1 | bv2; // Побитовое ИЛИ
    cout << "bv3 (bv1 | bv2): " << bv3 << endl;

    BoolV bv4 = bv1 & bv2; // Побитовое И
    cout << "bv4 (bv1 & bv2): " << bv4 << endl;

    BoolV bv5 = ~bv1; // Побитовое НЕ
    cout << "bv5 (~bv1): " << bv5 << endl;

    BoolV bv6 = bv1; // Копирование
    cout << "bv6 (copied from bv1): " << bv6 << endl;

    if (bv1 == bv6) {
        cout << "bv1 is equal to bv6" << endl;
    } else {
        cout << "bv1 is not equal to bv6" << endl;
    }

    cout << "Enter a binary string:";
    cin >> bv6; // Ввод булевого вектора с клавиатуры
    cout << "You entered: " << bv6 << endl;

    return 0;
}
