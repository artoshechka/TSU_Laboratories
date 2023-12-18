#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstring>

using namespace std;

class Array
{
    int *a, n;

public:
    // конструктор 1
    // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по неубыванию
    // t = 3 – массив, упорядоченный по невозрастанию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(int len = 1, int t = 1, int d = 10);
    Array(int *, int);
    Array(Array &);
    ~Array();
    Array &operator=(Array &);
    int &operator[](int);
    bool Test();
    bool operator==(Array);
    void Shell_sort();
    void Heapsort();
    void Hoar_sort(int, int);
    void Bit_sort();
    friend istream &operator>>(istream &, Array &);
    friend ostream &operator<<(ostream &, Array &);
};

Array::Array(int len, int t, int d)
{
    n = len;
    a = new int[n];
    switch (t)
    {
    case 1:
        srand(time(NULL));
        for (int i = 0; i < n; ++i)
        {
            a[i] = rand() % d;
        }
        break;
    case 2:
        for (int i = n - 1; i >= 0; --i)
        {
            a[i] = i;
        }
        break;
    case 3:
        for (int i = 0; i < n; ++i)
        {
            a[i] = i;
        }
        break;
    default:
        cout << "INVALID t";
        break;
    }
}

Array::Array(int *arr, int len)
{
    n = len;
    a = new int[n];
    memcpy(a, arr, n * sizeof(int));
}

Array::Array(Array &other)
{
    n = other.n;
    a = new int[n];
    memcpy(a, other.a, n * sizeof(int));
}

Array::~Array()
{
    delete[] a;
    a = NULL;
}

Array &Array::operator=(Array &other)
{
    if (this != &other)
    {
        n = other.n;
        delete[] a;
        a = new int[n];
        memcpy(a, other.a, n * sizeof(int));
    }
    return *this;
}

int &Array::operator[](int i)
{
    if (i < 0 || i >= n)
    {
        cout << "OUT OF RANGE";
        return a[0];
    }
    return a[i];
}

bool Array::Test()
{
    int test = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (a[i] < a[i + 1])
        {
            ++test;
        }
    }
    return test == (n - 1);
}

bool Array::operator==(Array other)
{
    return n == other.n && equal(a, a + n, other.a);
}

void Array::Shell_sort()
{
    const int maxSteps = static_cast<int>(log2(n)) + 1;
    int arrOfSteps[maxSteps];
    int step = n;
    int stepCount = 0;
    for (int i = 0; step != 1; ++i)
    {
        step /= 2;
        arrOfSteps[stepCount++] = step;
    }
    for (int s = 0; s < stepCount; ++s)
    {
        int gap = arrOfSteps[s];

        for (int i = gap; i < n; ++i)
        {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
            {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

void Array::Heapsort()
{
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        int parent = i;
        while (2 * parent + 1 < n)
        {
            int leftChild = 2 * parent + 1;
            int rightChild = 2 * parent + 2;
            int largest = parent;

            if (leftChild < n && a[leftChild] > a[largest])
            {
                largest = leftChild;
            }

            if (rightChild < n && a[rightChild] > a[largest])
            {
                largest = rightChild;
            }

            if (largest != parent)
            {
                swap(a[parent], a[largest]);
                parent = largest;
            }
            else
            {
                break;
            }
        }
    }

    for (int i = n - 1; i > 0; --i)
    {
        swap(a[0], a[i]);
        int parent = 0;
        while (2 * parent + 1 < i)
        {
            int leftChild = 2 * parent + 1;
            int rightChild = 2 * parent + 2;
            int largest = parent;

            if (leftChild < i && a[leftChild] > a[largest])
            {
                largest = leftChild;
            }

            if (rightChild < i && a[rightChild] > a[largest])
            {
                largest = rightChild;
            }

            if (largest != parent)
            {
                swap(a[parent], a[largest]);
                parent = largest;
            }
            else
            {
                break;
            }
        }
    }
}

void Array::Hoar_sort(int l, int r)
{
    if (r == -1)
        r = n - 1;

    if (l >= r)
        return;

    int x = a[(l + r) / 2];
    int i = l - 1;
    int j = r + 1;

    while (true)
    {
        do
        {
            i++;
        } while (a[i] < x);

        do
        {
            j--;
        } while (a[j] > x);

        if (i >= j)
            break;

        swap(a[i], a[j]);
    }

    Hoar_sort(l, j);
    Hoar_sort(j + 1, r);
}

void Array::Bit_sort()
{
    int maxBits = 32;
    const int RADIX = 2;
    int *output = new int[n];
    int *count = new int[RADIX];
    int shift = 0;

    while (shift < maxBits)
    {
        memset(count, 0, RADIX * sizeof(int));

        for (int i = 0; i < n; ++i)
        {
            int index = (a[i] >> shift) & 1;
            count[index]++;
        }

        count[1] += count[0];

        for (int i = n - 1; i >= 0; --i)
        {
            int index = (a[i] >> shift) & 1;
            output[--count[index]] = a[i];
        }

        memcpy(a, output, n * sizeof(int));

        shift++;
    }

    delete[] output;
    delete[] count;
}

istream &operator>>(istream &in, Array &array)
{
    cout << "Enter len";
    in >> array.n;
    cout << "Enter numbers";
    for (int i = 0; i < array.n; ++i)
    {
        in >> array.a[i];
    }
    return in;
}

ostream &operator<<(ostream &out, Array &array)
{
    for (int i = 0; i < array.n; ++i)
    {
        out << array.a[i] << " ";
    }
    out << endl;
    return out;
}

int main()
{
    Array a(10);
    a.Heapsort();
    cout << a;
    return 0;
}
