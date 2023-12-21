#include <bits/stdc++.h>
int BITS = sizeof(unsigned int) * 8;
using namespace std;

// Класс булев вектор
class BoolV
{
    unsigned int *v;
    int nbit, m; // nbit – количество бит вектора, m – количество элементов массива v
public:
    BoolV(int nn = 1);   // формируется булев вектор из nn бит; все биты со значениями 0
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
};

BoolV::BoolV(int nn)
{
    nbit = nn;
    m = (nbit + BITS - 1) / 32;
    v = new unsigned int[m];
}

BoolV::BoolV(const char *other)
{
    nbit = strlen(other);
    m = (nbit + BITS - 1) / 32;
    v = new unsigned int[m];
    for (int i = 0; i < nbit; ++i)
    {
        if (other[i] == '1')
        {
            Set1(i);
        }
    }
}

BoolV::BoolV(const BoolV &other)
{
    if (this != &other)
    {
        nbit = other.nbit;
        m = other.m;
        delete[] v;
        v = new unsigned int[m];
        memcpy(v, other.v, m * sizeof(unsigned int));
    }
}

BoolV::~BoolV()
{
    delete[] v;
    v = NULL;
}

void BoolV::Set1(int bit)
{
    v[bit / BITS] |= (1 << (bit % BITS));
}

void BoolV::Set0(int bit)
{
    v[bit / BITS] &= ~(1 << (bit % BITS));
}

int BoolV::operator[](int bit)
{
    return ((v[bit / 32] >> (bit % 32)) & 1);
}

BoolV BoolV::operator=(const BoolV &other)
{
    if (this != &other)
    {
        nbit = other.nbit;
        m = other.m;
        delete[] v;
        v = new unsigned int[m];
        memcpy(v, other.v, m * sizeof(unsigned int));
    }
    return *this;
}

bool BoolV::operator==(const BoolV &other)
{
    bool flag = true;
    int i = 0;
    if (nbit == other.nbit)
    {
        for (int i = 0; i < m; ++i)
        {
            if (v[i] != other.v[i])
            {
                flag = false;
                break;
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}

BoolV BoolV::operator|(const BoolV &other)
{
    BoolV result(max(nbit, other.nbit));
    for (int i = 0; i < result.m; ++i)
    {
        result.v[i] = v[i] | other.v[i];
    }
    return result;
}

BoolV BoolV::operator&(const BoolV &other)
{
    BoolV result(max(nbit, other.nbit));
    for (int i = 0; i < result.m; ++i)
    {
        result.v[i] = v[i] & other.v[i];
    }
    return result;
}

BoolV BoolV::operator~()
{
    BoolV result(nbit);
    for (int i = 0; i < m; ++i)
    {
        result.v[i] = ~v[i];
    }
    return result;
}
istream &operator>>(istream &in, BoolV &bv)
{
    string bools;
    in >> bools;
    BoolV temp(bools.c_str());
    bv = temp;
    return in;
}

ostream &operator<<(ostream &out, const BoolV &bv)
{
    for (int i = bv.nbit - 1; i >= 0; --i)
    {
        out << bv.v[i];
    }
    return out;
}
int main()
{
    // Пример использования булевого вектора
    BoolV bv1(8); // Создание булевого вектора из 8 бит
    cout << bv1;
    bv1.Set1(1); // Установка второго бита в 1
    bv1.Set1(3); // Установка четвертого бита в 1

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

    if (bv1 == bv6)
    {
        cout << "bv1 is equal to bv6" << endl;
    }
    else
    {
        cout << "bv1 is not equal to bv6" << endl;
    }

    cout << "Enter a binary string: ";
    cin >> bv6; // Ввод булевого вектора с клавиатуры
    cout << "You entered: " << bv6 << endl;

    return 0;
}
