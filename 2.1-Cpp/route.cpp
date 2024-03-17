#include <bits/stdc++.h>

using namespace std;

// Класс "Маршрут"
class route
{
private:
    int *r; // массив, представляющий маршрут
    int n;  // количество городов

public:
    route(int num = 0);              // создает начальную перестановку по возрастанию
    route(const route &);            // конструктор копирования
    route &operator=(const route &); // операция присваивания
    ~route();                        // деструктор

    int routePrice(int **); // вычисляет стоимость маршрута по матрице стоимости
    bool nextRoute();       // вычисляет следующий маршрут, используя алгоритм Дейкстры

    friend ostream &operator<<(ostream &, const route &); // вывод маршрута
};

route::route(int num)
{
    n = num;
    r = new int[n];
    for (int i = 0; i < n; ++i)
    {
        r[i] = i;
    }
}

route::route(const route &other)
{
    n = other.n;
    r = new int[n];
    memcpy(r, other.r, n * sizeof(int));
}

route &route::operator=(const route &other)
{
    if (this != &other)
    {
        n = other.n;
        delete[] r;
        r = new int[n];
        memcpy(r, other.r, n * sizeof(int));
    }
    return *this;
}

route::~route()
{
    delete[] r;
    r = NULL;
}

int route::routePrice(int **costMatrix)
{
    int price = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        price += costMatrix[r[i]][r[i + 1]];
    }
    price += costMatrix[r[n - 1]][r[0]]; // Возвращаемся в начальный город
    return price;
}

bool route::nextRoute()
{
    int i = 0;
    for (i = n - 1; (i > 0) && (r[i - 1] >= r[i]); --i)
        ;
    if (i == 1)
    {
        return false;
    }
    i--;
    int j = 0;
    for (j = n - 1; (j > i) && (r[i] >= r[j]); --j)
        ;
    int tmp = r[j];
    r[j] = r[i];
    r[i] = tmp;
    for (int j = i + 1, k = (n - 1); j < k; j++, k--)
    {
        tmp = r[j];
        r[j] = r[k];
        r[k] = tmp;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const route &r)
{
    for (int i = 0; i < r.n; ++i)
    {
        os << r.r[i] + 1 << " ";
    }
    os << r.r[0] + 1; // Возвращаемся в начальный город
    return os;
}

int main()
{
    int numCities;
    cout << "Enter number of cities: ";
    cin >> numCities;

    int **costMatrix = new int *[numCities];
    for (int i = 0; i < numCities; ++i)
    {
        costMatrix[i] = new int[numCities];
        for (int j = 0; j < numCities; ++j)
        {
            cin >> costMatrix[i][j];
        }
    }

    route initialRoute(numCities);

    int minCost = initialRoute.routePrice(costMatrix);
    route minRoute = initialRoute;

    do
    {
        int currentCost = initialRoute.routePrice(costMatrix);
        if (currentCost < minCost)
        {
            minCost = currentCost;
            minRoute = initialRoute;
        }
        cout << "route: " << initialRoute << "\t"
             << "cost: " << currentCost << endl;
    } while (initialRoute.nextRoute());
    cout << "Best route: " << minRoute << endl;
    cout << "Best cost: " << minCost << endl;

    // Освобождение памяти
    for (int i = 0; i < numCities; ++i)
    {
        delete[] costMatrix[i];
    }
    delete[] costMatrix;

    return 0;
}
