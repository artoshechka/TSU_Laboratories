#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
//Класс "Комплексное число"
class complex {
    double re, im;
public:
    complex(double Re = 0, double Im = 0);

    double getRe();

    void setRe(double);

    double getIm();

    void setIm(double);

    bool operator==(const complex &);

    bool operator!=(const complex &);

    double mod(); // возвращает модуль комплексного числа
    operator char *(); // преобразует комплексное число в строку
    complex operator~(); // возвращает комплексно сопряженное число
    complex operator+(const complex &);

    complex operator+=(const complex &);

    complex operator-(const complex &);

    complex operator-=(const complex &);

    complex operator*(const complex &);

    complex operator*=(const complex &);

    complex operator/(const complex &);

    complex operator/=(const complex &);

    friend istream &operator>>(istream &, complex &);

    friend ostream &operator<<(ostream &, complex &);
};

complex::complex(double Re, double Im) {
    re = Re;
    im = Im;
}

double complex::getRe() {
    return re;
}

void complex::setRe(double Re) {
    re = Re;
}

double complex::getIm() {
    return im;
}

void complex::setIm(double Im) {
    im = Im;
}

bool complex::operator==(const complex &other) {
    return (re == other.re && im == other.im);
}

bool complex::operator!=(const complex &other) {
    return (re != other.re || im != other.im);
}

double complex::mod() {
    return sqrt(re * re + im * im);
}

complex::operator char *() {
    char *str = new char[25];
    char *str_2 = new char[8];
    sprintf(str, "%5.2f", re);
    if (im > 0) {
        strcat(str, " +");
    }
    else if (im < 0) {
        strcat(str, " -");
    }
    if (im != 0) {
        sprintf(str_2, "%5.2f", fabs(im));
        strcat(str, str_2);
        strcat(str, "i");
    }
    return str;
}

complex complex::operator~() {
    im = -im;
    return *this;
}

complex complex::operator+(const complex &other) {
    complex temp;
    temp.re = re + other.re;
    temp.im = im + other.im;
    return temp;
}

complex complex::operator+=(const complex &other) {
    re += other.re;
    im += other.im;
    return *this;
}

complex complex::operator-(const complex &other) {
    complex temp;
    temp.re = re - other.re;
    temp.im = im - other.im;
    return temp;
}

complex complex::operator-=(const complex &other) {
    re -= other.re;
    im -= other.im;
    return *this;
}

complex complex::operator*(const complex &other) {
    complex temp;
    temp.re = re * other.re;
    temp.im = im * other.im;
    return temp;
}

complex complex::operator*=(const complex &other) {
    re *= other.re;
    im *= other.im;
    return *this;
}

complex complex::operator/(const complex &other) {
    complex temp;
    double r = other.re * other.re + other.im * other.im;
    if (r == 0) {
        cout << "Divide by zero" << endl;
        exit(0);
    }
    temp.re = (re * other.re + im * other.im) / r;
    temp.im = (im * other.re - re * other.im) / r;

    return temp;
}

complex complex::operator/=(const complex &other) {
    double r = other.re * other.re + other.im * other.im;
    if (r == 0) {
        cout << "Divide by zero" << endl;
        exit(0);
    }
    re = (re * other.re + im * other.im) / r;
    im = (im * other.re - re * other.im) / r;
    return *this;
}

istream &operator>>(istream &in, complex &other) {
    cout << "Real part:";
    in >> other.re;
    cout << "Imagine part:";
    in >> other.im;
    return in;
}

ostream &operator<<(ostream &out, complex &other) {
    out << (char *) other;
    return out;
}

int main() {
    complex value1, value2;
    cout << "Enter the 1st complex number\n";
    cin >> value1;
    cout << "Enter the 2st complex number\n";
    cin >> value2;
    cout << endl << "1st complex number -> " << value1 << endl << "2nd complex number -> " << value2 << "\n\n";
    cout << "mod 1st complex number: " << value1.mod() << endl << "mod 2nd complex number: " << value2.mod() << endl;
    cout << "conjugate 1st complex number: " << ~value1 << endl << "conjugate 2nd complex number: " << ~value2 << endl;
    ~value1;
    ~value2;
    cout << "+: " << value1 + value2 << endl;
    cout << "+=: " << value1 + value2 << endl;
    cout << "-: " << value1 - value2 << endl;
    cout << "-=: " << value1 - value2 << endl;
    cout << "*: " << value1 * value2 << endl;
    cout << "*=: " << value1 * value2 << endl;
    cout << "/: " << value1 / value2 << endl;
    cout << "/=: " << value1 / value2 << endl;
    cout << "==: " << (value1 == value2) << endl;
    cout << "!=: " << (value1 != value2) << endl;
    return 0;
}