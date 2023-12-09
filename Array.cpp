#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Array {
    int *a, n;

public:
    // Конструктор 1
    Array(int len = 1, int t = 1, int d = 10);

    // Конструктор 2: по массиву
    Array(int *, int);

    // Конструктор копирования
    Array(Array &);

    // Деструктор
    ~Array();

    // Оператор присваивания
    Array &operator=(Array &);

    // Оператор индексации
    int &operator[](int);

    // Проверка на упорядоченность по неубыванию
    bool Test();

    // Оператор сравнения на равенство элементов массивов (но не порядка)
    bool operator==(Array);

    // Сортировка Шелла
    void Shell_sort();

    // Пирамидальная сортировка
    void Heapsort();

    // Сортировка Хоара (Quick sort)
    void Hoar_sort();

    // Битоническая сортировка
    void Bit_sort();

    // Перегрузка оператора ввода
    friend istream &operator>>(istream &, Array &);

    // Перегрузка оператора вывода
    friend ostream &operator<<(ostream &, Array &);
};

Array::Array(int len, int t, int d) : n(len) {
    a = new int[n];

    if (t == 1) {
        // Неупорядоченный массив
        srand(time(NULL));
        for (int i = 0; i < n; ++i) {
            a[i] = rand() % d;
        }
    } else if (t == 2) {
        // Упорядоченный по неубыванию массив
        for (int i = 0; i < n; ++i) {
            a[i] = i + 1;
        }
    } else if (t == 3) {
        // Упорядоченный по невозрастанию массив
        for (int i = 0; i < n; ++i) {
            a[i] = n - i;
        }
    } else {
        // Неправильное значение t
        cout << "Invalid value of t" << endl;
    }
}

Array::Array(int *arr, int len) : n(len) {
    a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = arr[i];
    }
}

Array::Array(Array &other) : n(other.n) {
    a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = other.a[i];
    }
}

Array::~Array() {
    delete[] a;
}

Array &Array::operator=(Array &other) {
    if (this != &other) {
        delete[] a;
        n = other.n;
        a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = other.a[i];
        }
    }
    return *this;
}

int &Array::operator[](int index) {
    if (index < 0 || index >= n) {
        cout << "Out of range" << endl;
        return a[0];
    }
    return a[index];
}

bool Array::Test() {
    for (int i = 1; i < n; ++i) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

bool Array::operator==(Array other) {
    if (n != other.n) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] != other.a[i]) {
            return false;
        }
    }
    return true;
}

void Array::Shell_sort() {
    // Реализация сортировки Шелла
    // TODO: Дополнить код сортировки Шелла
}

void Array::Heapsort() {
    // Реализация пирамидальной сортировки
    // TODO: Дополнить код пирамидальной сортировки
}

void Array::Hoar_sort() {
    // Реализация сортировки Хоара (Quick sort)
    // TODO: Дополнить код сортировки Хоара
}

void Array::Bit_sort() {
    // Реализация битонической сортировки
    // TODO: Дополнить код битонической сортировки
}

istream &operator>>(istream &in, Array &arr) {
    for (int i = 0; i < arr.n; ++i) {
        in >> arr.a[i];
    }
    return in;
}

ostream &operator<<(ostream &out, Array &arr) {
    for (int i = 0; i < arr.n; ++i) {
        out << arr.a[i] << " ";
    }
    out << endl;
    return out;
}

int main() {
    // Пример использования класса Array

    // Создание массива случайных чисел
    Array arr1(10, 1, 100);
    cout << "Original Array (Unordered): " << arr1;

    // Создание упорядоченного массива по неубыванию
    Array arr2(10, 2);
    cout << "Original Array (Non-decreasing): " << arr2;

    // Создание упорядоченного массива по невозрастанию
    Array arr3(10, 3);
    cout << "Original Array (Non-increasing): " << arr3;

    // Создание массива по заданному массиву
    int customArr[] = {5, 3, 8, 2, 1};
    Array arr4(customArr, 5);
    cout << "Original Array (Custom): " << arr4;

    // Проверка метода Test
    cout << "Is arr1 non-decreasing? " << (arr1.Test() ? "Yes" : "No") << endl;
    cout << "Is arr2 non-decreasing? " << (arr2.Test() ? "Yes" : "No") << endl;

    // Проверка оператора ==
    cout << "Is arr2 equal to arr3? " << (arr2 == arr3 ? "Yes" : "No") << endl;
    cout << "Is arr3 equal to arr4? " << (arr3 == arr4 ? "Yes" : "No") << endl;

    // Пример сортировки Шелла
    Array arr5(10, 1, 100);
    cout << "Original Array (Unordered): " << arr5;
    arr5.Shell_sort();
    cout << "Sorted Array (Shell Sort): " << arr5;

    // Пример пирамидальной сортировки
    Array arr6(10, 1, 100);
    cout << "Original Array (Unordered): " << arr6;
    arr6.Heapsort();
    cout << "Sorted Array (Heapsort): " << arr6;

    // Пример сортировки Хоара (Quick sort)
    Array arr7(10, 1, 100);
    cout << "Original Array (Unordered): " << arr7;
    arr7.Hoar_sort();
    cout << "Sorted Array (Hoare Sort): " << arr7;

    // Пример битонической сортировки
    Array arr8(8, 1, 100);
    cout << "Original Array (Unordered): " << arr8;
    arr8.Bit_sort();
    cout << "Sorted Array (Bitonic Sort): " << arr8;

    return 0;
}