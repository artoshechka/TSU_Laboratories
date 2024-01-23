#include <bits/stdc++.h>

using namespace std;

// класс "Массив"
class Array {
    int *a, n;

public:
    // конструктор 1
    // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по неубыванию
    // t = 3 – массив, упорядоченный по невозрастанию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(int len = 1, int t = 1, int d = 10);

    // конструктор 2
    Array(int *, int);

    // конструктор 3
    Array(Array &);

    // деструктор
    ~Array();

    int arrLength();

    Array &operator=(Array &);

    int &operator[](int);

    bool Test();

    bool operator==(Array);

    void Shell_sort();

    void Heapsort();

    void Hoar_sort();

    void Bit_sort();

    friend istream &operator>>(istream &, Array &);

    friend ostream &operator<<(ostream &, Array &);
};

Array::Array(int len, int t, int d) {
    n = len;
    a = new int[n];
    switch (t) {
        case 1:
            for (int i = 0; i < n; ++i) {
                a[i] = rand() % d;
            }
            break;
        case 2:
            for (int i = n - 1; i >= 0; --i) {
                a[i] = i;
            }
            break;
        case 3:
            for (int i = 0; i < n; ++i) {
                a[i] = i;
            }
            break;
        default:
            cout << "INVALID t";
            break;
    }
}

Array::Array(int *arr, int len) {
    n = len;
    a = new int[n];
    memcpy(a, arr, n * sizeof(int));
}

Array::Array(Array &other) {
    n = other.n;
    a = new int[n];
    memcpy(a, other.a, n * sizeof(int));
}

Array::~Array() {
    delete[] a;
    a = NULL;
}

int Array::arrLength() {
    return n;
}

Array &Array::operator=(Array &other) {
    if (this != &other) {
        n = other.n;
        delete[] a;
        a = new int[n];
        memcpy(a, other.a, n * sizeof(int));
    }
    return *this;
}

int &Array::operator[](int i) {
    if (i < 0 || i >= n) {
        cout << "OUT OF RANGE";
        return a[0];
    }
    return a[i];
}

bool Array::Test() {
    int test = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            return 0;
        }
    }
    return 1;
}

bool Array::operator==(Array other) {
    if (n != other.n)
        return false;

    // Создаем временные копии массивов
    int *copyA = new int[n];
    int *copyB = new int[other.n];
    memcpy(copyA, a, n * sizeof(int));
    memcpy(copyB, other.a, other.n * sizeof(int));

    // Сортируем временные копии
    sort(copyA, copyA + n);
    sort(copyB, copyB + other.n);

    // Сравниваем отсортированные копии
    bool result = equal(copyA, copyA + n, copyB);

    // Очищаем выделенную память
    delete[] copyA;
    delete[] copyB;

    return result;
}

void Array::Shell_sort() {
    int arrOfSteps[((int) (log2(n)))]; // длина массивов шагов
    int step = n;
    int stepCount = 0;
    for (int i = 0; step != 1; ++i) {
        step /= 2;
        arrOfSteps[stepCount++] = step;
    }
    for (int s = 0; s < stepCount; ++s) {
        int gap = arrOfSteps[s];

        for (int i = gap; i < n; ++i) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

// Функция для построения max-кучи без рекурсии
void buildMaxHeapIterative(int arr[], int n, int i) {
    while (true) {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < n && arr[leftChild] > arr[largest]) {
            largest = leftChild;
        }

        if (rightChild < n && arr[rightChild] > arr[largest]) {
            largest = rightChild;
        }

        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            i = largest;  // Обновляем индекс для проверки дочерних узлов
        } else {
            break;  // Если куча уже упорядочена, выходим из цикла
        }
    }
}

// Функция для пирамидальной сортировки без рекурсии
void heapSortIterative(int arr[], int n) {
    // Построение max-кучи
    for (int i = n / 2 - 1; i >= 0; --i) {
        buildMaxHeapIterative(arr, n, i);
    }

    // Поочередное извлечение элементов из кучи
    for (int i = n - 1; i > 0; --i) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        buildMaxHeapIterative(arr, i, 0);
    }
}

void Array::Heapsort() {
    heapSortIterative(a, n);
}

void hoar_sort(int a[], int l, int r) {

    if (l >= r)
        return;

    int x = a[(l + r) / 2];
    int i = l - 1;
    int j = r + 1;

    while (true) {
        do {
            i++;
        } while (a[i] < x);

        do {
            j--;
        } while (a[j] > x);

        if (i >= j)
            break;

        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    hoar_sort(a, l, j);
    hoar_sort(a, j + 1, r);
}

void Array::Hoar_sort() {
    int l = 0, r = arrLength() - 1;
    hoar_sort(a, l, r);
}

void bit_sort(int a[], int l, int r, int k) {
    if (l >= r || k < 0) {
        return;
    }

    int i = l, j = r;

    while (i <= j) {//заменить маску
        // Перемещение i до тех пор, пока k-ый бит равен 0
        while (i <= j && ((a[i] >> k) & 1) == 0) {
            i++;
        }

        // Перемещение j до тех пор, пока k-ый бит равен 1
        while (i <= j && ((a[j] >> k) & 1) == 1) {
            j--;
        }

        // Обмен a[i] и a[j]
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    // Рекурсивная сортировка подмассива [l, j] по (k-1)-ому биту
    bit_sort(a, l, j, k - 1);

    // Рекурсивная сортировка подмассива [i, r] по (k-1)-ому биту
    bit_sort(a, i, r, k - 1);
}

void Array::Bit_sort() {
    bit_sort(a, 0, arrLength() - 1, sizeof(int) * 8 - 1);
}


istream &operator>>(istream &in, Array &array) {
    cout << "Enter len";
    in >> array.n;
    cout << "Enter numbers";
    for (int i = 0; i < array.n; ++i) {
        in >> array.a[i];
    }
    return in;
}

ostream &operator<<(ostream &out, Array &array) {
    for (int i = 0; i < array.n; ++i) {
        out << array.a[i] << " ";
    }
    out << endl;
    return out;
}

int main() {
    srand(time(NULL));

    // Маленький массив
    Array smallArray(20, 1, 100);
    Array smallArrayCopy(smallArray);

    auto startSmallShell = chrono::high_resolution_clock::now();
    //cout << smallArray;
    smallArray.Shell_sort();
    //cout << smallArray;
    auto endSmallShell = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSmallShell = endSmallShell - startSmallShell;
    cout << "Small array (Shell sort) time: " << durationSmallShell.count() << " milliseconds" << endl;
    cout << "Is small array sorted? " << smallArray.Test() << " Are elements equal? " << (smallArray == smallArrayCopy)
         << endl;

    Array smallArrayHeap(smallArrayCopy);
    auto startSmallHeap = chrono::high_resolution_clock::now();
    //cout << smallArrayHeap;
    smallArrayHeap.Heapsort();
    //cout << smallArrayHeap;
    auto endSmallHeap = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSmallHeap = endSmallHeap - startSmallHeap;
    cout << "Small array (Heapsort) time: " << durationSmallHeap.count() << " milliseconds" << endl;
    cout << "Is small array sorted? " << smallArrayHeap.Test() << " Are elements equal? "
         << (smallArrayHeap == smallArrayCopy) << endl;

    Array smallArrayHoar(smallArrayCopy);
    auto startSmallHoar = chrono::high_resolution_clock::now();
    //cout << smallArrayHoar;
    smallArrayHoar.Hoar_sort();
    //cout << smallArrayHoar;
    auto endSmallHoar = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSmallHoar = endSmallHoar - startSmallHoar;
    cout << "Small array (Hoar sort) time: " << durationSmallHoar.count() << " milliseconds" << endl;
    cout << "Is small array sorted? " << smallArrayHoar.Test() << " Are elements equal? "
         << (smallArrayHoar == smallArrayCopy) << endl;

    Array smallArrayBit(smallArrayCopy);
    auto startSmallBit = chrono::high_resolution_clock::now();
    //cout << smallArrayBit;
    smallArrayBit.Bit_sort();
    //cout << smallArrayBit;
    auto endSmallBit = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSmallBit = endSmallBit - startSmallBit;
    cout << "Small array (Bit sort) time: " << durationSmallBit.count() << " milliseconds" << endl;
    cout << "Is small array sorted? " << smallArrayBit.Test() << " Are elements equal? "
         << (smallArrayBit == smallArrayCopy) << endl;

    // Большой массив
    Array largeArray(1000000, 1, 10000000);
    Array largeArrayCopy(largeArray);

    auto startLargeShell = chrono::high_resolution_clock::now();
    largeArray.Shell_sort();
    auto endLargeShell = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationLargeShell = endLargeShell - startLargeShell;
    cout << "Large array (Shell sort) time: " << durationLargeShell.count() << " milliseconds" << endl;
    cout << "Is large array sorted? " << largeArray.Test() << " Are elements equal? " << (largeArray == largeArrayCopy)
         << endl;

    Array largeArrayHeap(largeArrayCopy);
    auto startLargeHeap = chrono::high_resolution_clock::now();
    largeArrayHeap.Heapsort();
    auto endLargeHeap = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationLargeHeap = endLargeHeap - startLargeHeap;
    cout << "Large array (Heapsort) time: " << durationLargeHeap.count() << " milliseconds" << endl;
    cout << "Is large array sorted? " << largeArrayHeap.Test() << " Are elements equal? "
         << (largeArrayHeap == largeArrayCopy) << endl;

    Array largeArrayHoar(largeArrayCopy);
    auto startLargeHoar = chrono::high_resolution_clock::now();
    largeArrayHoar.Hoar_sort();
    auto endLargeHoar = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationLargeHoar = endLargeHoar - startLargeHoar;
    cout << "Large array (Hoar sort) time: " << durationLargeHoar.count() << " milliseconds" << endl;
    cout << "Is large array sorted? " << largeArrayHoar.Test() << " Are elements equal? "
         << (largeArrayHoar == largeArrayCopy) << endl;

    Array largeArrayBit(largeArrayCopy);
    auto startLargeBit = chrono::high_resolution_clock::now();
    largeArrayBit.Bit_sort();
    auto endLargeBit = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationLargeBit = endLargeBit - startLargeBit;
    cout << "Large array (Bit sort) time: " << durationLargeBit.count() << " milliseconds" << endl;
    cout << "Is large array sorted? " << largeArrayBit.Test() << " Are elements equal? "
         << (largeArrayBit == largeArrayCopy) << endl;

    return 0;
}