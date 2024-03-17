#include <bits/stdc++.h>

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

    int weight(); //вес вектора
    BoolV operator<<(int); //сдвиг на k бит влево
    BoolV operator>>(int); //сдвиг на k бит вправо
    friend class BoolM;
};

// Класс булева матрица
class BoolM {
    BoolV *bm;
    int m, n; // m – количество строк, n – количество столбцов
public:
    BoolM(int k = 1, int l = 1); // формируется нулевая булева матрица размера kl
    BoolM(const BoolM &);

    BoolV &operator[](int);

    BoolM operator=(const BoolM &);

    friend ostream &operator<<(ostream &, BoolM &);

    bool topsort(int *a);

    int BuildMatrix();
};


BoolV::BoolV(int nn) {
    nbit = nn;
    m = (nbit - 1) / 32 + 1;
    v = new unsigned int[m];
    for (int i = 0; i < m; ++i) {
        v[i] = 0;
    }
}

BoolV::BoolV(const char *str) {//оптимизировать через задачу перемнных
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

BoolV BoolV::operator|(const BoolV &other) {//тернарные исправить на условия для оптимальности
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
    for (int i = 0; i < nbit; ++i) {
        ((temp.v[i / 32] & (1 << (i % 32))) == 0 ? temp.Set1(i) : temp.Set0(i));
    }
    return temp;
}

// Реализация метода weight
int BoolV::weight() {
    int count = 0;
    for (int i = 0; i < nbit; ++i) {
        if (v[i / 32] & (1 << (i % 32))) {
            count++;
        }
    }
    return count;
}

// Реализация оператора <<
BoolV BoolV::operator<<(int k) {
    BoolV result(*this); // создаем копию текущего вектора

    // Сдвигаем биты влево на k позиций
    for (int i = 0; i < nbit; ++i) {
        int newIndex = i + k;
        if (newIndex < nbit) {
            ((v[i / 32] & (1 << (i % 32))) ? result.Set1(newIndex) : result.Set0(newIndex));
        }
    }

    return result;
}

// Реализация оператора >>
BoolV BoolV::operator>>(int k) {
    BoolV result(*this); // создаем копию текущего вектора

    // Сдвигаем биты вправо на k позиций
    for (int i = nbit - 1; i >= 0; --i) {
        int newIndex = i - k;
        if (newIndex >= 0) {
            ((v[i / 32] & (1 << (i % 32))) ? result.Set1(newIndex) : result.Set0(newIndex));

        }
    }

    return result;
}

// Конструктор для создания нулевой булевой матрицы размера kl
BoolM::BoolM(int k, int l) {
    m = k;
    n = l;
    bm = new BoolV[m];
    BoolV bv(n);
    for (int i = 0; i < m; ++i) {
        bm[i] = bv;
    }
}

// Конструктор копирования
BoolM::BoolM(const BoolM &other) {
    m = other.m;
    n = other.n;
    bm = new BoolV[m];
    for (int i = 0; i < m; ++i) {
        bm[i] = other.bm[i];
    }
}

// Перегрузка оператора [] для доступа к строке матрицы
BoolV &BoolM::operator[](int row) {
    if (row >= 0 && row < m) {
        return bm[row];
    } else {
        cout << "Invalid row index";
        // Вернуть ссылку на первую строку в случае ошибки (это можно изменить в зависимости от требований)
        return bm[0];
    }
}

// Перегрузка оператора присваивания для копирования матрицы
BoolM BoolM::operator=(const BoolM &other) {
    if (this != &other) {
        m = other.m;
        n = other.n;
        delete[] bm;
        bm = new BoolV[m];
        for (int i = 0; i < m; ++i) {
            bm[i] = other.bm[i];
        }
    }
    return *this;
}

// Перегрузка оператора вывода для вывода матрицы в поток
ostream &operator<<(ostream &out, BoolM &boolM) {
    for (int i = 0; i < boolM.m; ++i) {
        out << boolM.bm[i] << endl;
    }
    return out;
}

void topsort(BoolM &M, int m, int *a) {
    BoolV v0(m); // Какие вершины использовали rоторые уже рассмотрели
    BoolV v1(m); // Вершины в которые нет пути
    BoolV v2(m); // Ответ на данном шаге цикла while
    BoolV NullV(m);//вектор с 0 везде
    int k = 0;
    for (int i = 0; i < m; i++) {//jтветы заполняем нулями
        a[i] = 0;
    }
    while (v0.weight() != m) {//
        v1 = NullV;//обноляем на каждом шаге
        for (int i = 0; i < m; i++) {
            v1 = v1 | M[i];//находим вершины в которые у нас есть пути

        }
        v1 = ~v1;// вершины в которые у нас нет пути
        v2 = v1 & (~v0);//нет пути но мы их не использовались
        if (v2 == NullV) {//условие для неприминимости топологической сортировки
            throw invalid_argument("Error Matrix");
        }
        for (int i = 0; i < m; i++) { // пробегаем по всему v2

            if (v2[i] == 1) {
                a[k] = i + 1;//добавляем вершину в массив ответов
                M[i] = NullV;//удаляем исходящие пути
                k++;//увеличиваем указатель для массива ответов
            }
        }

        v0 = v0 | v2;//добавляем рассмотренные вершины


    }
}

int BoolM::BuildMatrix() {//построение матрицы из файла
    ifstream fin("graf.txt");
    if (fin.is_open()) {
        int a, b;
        int m;
        fin >> m;//колличество вершин
        BoolM BM(m, m);//строим пустую матрицу
        do {
            fin >> a;// вершина начала пути
            fin >> b;//вершина конца пути
            BM[a - 1].Set1(b - 1);// установка единицы в ячейку матрицы
        } while (!fin.eof());// пока можем считать с файла
        fin.close();
        *this = BM;
        return m;//возвращаем колличество вершин
    }
    return 0;
}

void matrix() {//матрица+ответ сортировки
    BoolM a;
    int m;
    m = a.BuildMatrix();
    int *b = new int[m];//массив ответов
    cout << a;//выводим матрицу
    topsort(a, m, b);//производим топологическую сортировку
    printf("Otvet: ");
    for (int i = 0; i < m - 1; i++) {//выводим массив ответов
        cout << b[i] << ", ";
    }
    cout << b[m - 1] << endl;
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
    // Пример использования метода weight для вектора
    cout << "Weight of bv1: " << bv1.weight() << endl;

    // Пример использования операторов << и >> для вектора
    int shiftAmount;
    cout << "Enter shift amount for bv1 to the left:";
    cin >> shiftAmount;
    BoolV bvLeftShifted = bv1 << shiftAmount;
    cout << "bv1 after left shift by " << shiftAmount << " bits: " << bvLeftShifted << endl;

    cout << "Enter shift amount for bv1 to the right:";
    cin >> shiftAmount;
    BoolV bvRightShifted = bv1 >> shiftAmount;
    cout << "bv1 after right shift by " << shiftAmount << " bits: " << bvRightShifted << endl;
    cout << "Enter a binary string:";
    cin >> bv6; // Ввод булевого вектора с клавиатуры
    cout << "You entered: " << bv6 << endl << endl;

    // Пример использования булевой матрицы
    BoolM matrix1(3, 4); // Создание булевой матрицы 3x4

    // Установка значений в матрице
    matrix1[0].Set1(1);
    matrix1[1].Set1(2);
    matrix1[2].Set1(3);

    cout << "Matrix1:" << endl;
    cout << matrix1 << endl; // Вывод матрицы на экран

    BoolM matrix2 = matrix1; // Копирование матрицы

    cout << "Matrix2 (copied from Matrix1):" << endl;
    cout << matrix2 << endl; // Вывод скопированной матрицы
    matrix();

    return 0;
}

