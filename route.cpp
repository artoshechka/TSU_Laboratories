#include <bits/stdc++.h>

using namespace std;

//Класс "Маршрут"
class route {
private:
    int *r;  // массив, представляющий маршрут
    int n;   // количество городов

public:
    route(int num = 0);          // создает начальную перестановку по возрастанию
    route(const route &);        // конструктор копирования
    route &operator=(const route &); // операция присваивания
    ~route();                   // деструктор

    int routePrice(int **);     // вычисляет стоимость маршрута по матрице стоимости
    bool nextRoute();           // вычисляет следующий маршрут, используя алгоритм Дейкстры

    friend ostream &operator<<(ostream &, const route &); // вывод маршрута
};


route::route(int num) {
    n = num;
    r = new int[n];
    for (int i = 0; i < n; ++i) {
        r[i] = i;
    }
}

route::route(const route &other) {
    n = other.n;
    r = new int[n];
    memcpy(r, other.r, n * sizeof(int));
}

route &route::operator=(const route &other) {
    if (this != &other) {
        n = other.n;
        delete[] r;
        r = new int[n];
        memcpy(r, other.r, n * sizeof(int));
    }
    return *this;
}

route::~route() {
    delete[] r;
    r = NULL;
}

int route::routePrice(int **costMatrix) {
    int price = 0;
    for (int i = 0; i < n - 1; ++i) {
        price += costMatrix[r[i]][r[i + 1]];
    }
    price += costMatrix[r[n - 1]][r[0]]; // Возвращаемся в начальный город
    return price;
}

bool route::nextRoute() {
    int i = n - 2;
    while (i >= 0 && r[i] > r[i + 1]) {
        i--;
    }

    if (i < 0) {
        // Перестановок больше нет
        return false;
    }

    int j = n - 1;
    while (r[j] < r[i]) {
        j--;
    }

    // Меняем местами r[i] и r[j] без использования
    int temp = r[i];
    r[i] = r[j];
    r[j] = temp;

    // Разворачиваем оставшуюся часть перестановки вручную
    int left = i + 1, right = n - 1;
    while (left < right) {
        temp = r[left];
        r[left] = r[right];
        r[right] = temp;
        left++;
        right--;
    }

    return true;
}

std::ostream &operator<<(std::ostream &os, const route &r) {
    for (int i = 0; i < r.n; ++i) {
        os << r.r[i] + 1 << " ";
    }
    os << r.r[0] + 1; // Возвращаемся в начальный город
    return os;
}


int main() {
    int numCities;
    cout << "Enter number of cities: ";
    cin >> numCities;

    int **costMatrix = new int *[numCities];
    for (int i = 0; i < numCities; ++i) {
        costMatrix[i] = new int[numCities];
        for (int j = 0; j < numCities; ++j) {
            cin >> costMatrix[i][j];
        }
    }

    route initialRoute(numCities);

    int minCost = initialRoute.routePrice(costMatrix);
    route minRoute = initialRoute;

    do {
        int currentCost = initialRoute.routePrice(costMatrix);
        if (currentCost < minCost) {
            minCost = currentCost;
            minRoute = initialRoute;
        }
    } while (initialRoute.nextRoute());

    cout << "Best route: " << minRoute << endl;
    cout << "Best cost: " << minCost << endl;

    // Освобождение памяти
    for (int i = 0; i < numCities; ++i) {
        delete[] costMatrix[i];
    }
    delete[] costMatrix;

    return 0;
}
