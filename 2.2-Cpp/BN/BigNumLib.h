#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

typedef unsigned int BASE;
typedef unsigned long long int DBASE;
#define BASE_SIZE (sizeof(BASE) * 8)
#define DBASE_SIZE (sizeof(DBASE) * 8)

class bigNumber {
private:
	BASE* coefficients;  // ������������
	int length;          // ����������� �����
	int maxLength;       // ����������� ��������� �����

public:
	// �����������
	bigNumber(int maxLen = 1, int parameter = 0);

	// ����������� �����������
	bigNumber(const bigNumber&);

	// ����������
	~bigNumber();

	// ������������
	void lenNorm();

	// ���������� ���������
	bool operator==(const bigNumber&) const;
	bool operator!=(const bigNumber&) const;
	bool operator<(const bigNumber&) const;
	bool operator>(const bigNumber&) const;
	bool operator<=(const bigNumber&) const;
	bool operator>=(const bigNumber&) const;

	// ���������� ��������
	bigNumber& operator=(const bigNumber&);
	bigNumber operator+(const bigNumber&) const;
	bigNumber& operator+=(const bigNumber&);
	bigNumber operator-(const bigNumber&) const;
	bigNumber& operator-=(const bigNumber&);
	bigNumber operator*(const BASE&) const;
	bigNumber& operator*=(const BASE&);
	bigNumber operator*(const bigNumber&) const;
	bigNumber& operator*=(const bigNumber&);
	bigNumber operator/(const BASE&) const;
	bigNumber operator%(const BASE&) const;
	bigNumber operator/(const bigNumber&) const;
	bigNumber operator%(const bigNumber&) const;

	// 16������ ���� � �����
	void printHex() const;
	void readHex();

	// 10������ ���� � �����
	friend istream& operator>>(istream&, bigNumber&);
	friend ostream& operator<<(ostream&, bigNumber&);
};
void bigNumber::lenNorm() {
	while (length > 1 && coefficients[length - 1] == 0) {
		length--;
	}
}
// �����������
bigNumber::bigNumber(int maxLen, int parameter) : length(1), maxLength(maxLen) {
	coefficients = new BASE[maxLen];
	if (maxLen == 1) {
		length = 1;
	}
	for (int i = 0; i < maxLength; i++) {
		coefficients[i] = 0;
	}
	// ���� �������� �� ����� 0, �������������� ���������� ����������
	if (parameter != 0) {
		length = maxLength;
		for (int i = 0; i < maxLength; i++) {
			coefficients[i] = rand();
		}
		if (sizeof(BASE) == sizeof(unsigned int)) {  // ����������� ��������� ������� ����� � ��������� � int
			for (int i = 0; i < maxLength; ++i) {
				coefficients[i] <<= 16;
				coefficients[i] |= rand();
			}
		}
	}
}

// ����������� �����������
bigNumber::bigNumber(const bigNumber& other) : length(other.length), maxLength(other.maxLength) {
	coefficients = new BASE[maxLength];
	int i = 0;
	while (i < maxLength) {
		coefficients[i] = other.coefficients[i];
		i++;
	}
}

// ����������
bigNumber::~bigNumber() {
	delete[] coefficients;
}

// �������� ������������
bigNumber& bigNumber::operator=(const bigNumber& other) {
	if (this != &other) {
		delete[] coefficients;
		maxLength = other.maxLength;
		length = other.length;
		coefficients = new BASE[maxLength];
		int i = 0;
		while (i < maxLength) {
			coefficients[i] = other.coefficients[i];
			i++;
		}
	}
	return *this;
}

// ������ ����� � ����������������� �������
void bigNumber::printHex() const {
	int i = length - 1;
	while (i >= 0) {
		cout.width(BASE_SIZE / 4);
		cout.fill('0');
		cout << hex << (int)coefficients[i] << " ";
		i--;
	}
}

// ���� ����� � ����������������� �������
void bigNumber::readHex() { //toDo: ����������� �����
	string inputString;
	getline(cin, inputString);
	int inputStringLength = inputString.length();
	int k = 0, j = 0;
	length = (inputStringLength - 1) / (BASE_SIZE / 4) + 1;
	maxLength = length;
	coefficients = new BASE[length];
	int i = 0;
	while (i < length) {
		coefficients[i] = 0;
		i++;
	}

	// �������������� ������ � ����������������� ������������
	int idx = inputStringLength - 1;
	while (idx >= 0) {
		unsigned int temp = 0;
		if ('0' <= inputString[idx] && inputString[idx] <= '9') {
			temp = inputString[idx] - '0';
		}
		else if ('a' <= inputString[idx] && inputString[idx] <= 'f') {
			temp = inputString[idx] - 'a' + 10;
		}
		else if ('A' <= inputString[idx] && inputString[idx] <= 'F') {
			temp = inputString[idx] - 'A' + 10;
		}
		else {
			throw invalid_argument("Invalid arguments.");
		}

		coefficients[j] |= temp << k;
		k += 4;
		if (k >= BASE_SIZE) {
			k = 0;
			j++;
		}
		idx--;
	}
	lenNorm();
}

// �������� ��������
bigNumber bigNumber::operator+(const bigNumber& other) const {
	int maxOfLengths = max(length, other.length);
	int minOfLengths = min(length, other.length);
	int sumLength = maxOfLengths + 1;  // ������������� � ������ ���������� ��������
	bigNumber sumNumber(sumLength);
	BASE carry = 0;
	int i = 0;
	while (i < minOfLengths) {
		DBASE tempSum = (DBASE)coefficients[i] + (DBASE)other.coefficients[i] + carry;
		sumNumber.coefficients[i] = (BASE)tempSum;
		carry = tempSum >> BASE_SIZE;
		i++;
	}

	while (i < length) {
		DBASE tempSum = (DBASE)coefficients[i] + carry;
		sumNumber.coefficients[i] = (BASE)tempSum;
		carry = tempSum >> BASE_SIZE;
		i++;
	}

	while (i < other.length) {
		DBASE tempSum = (DBASE)other.coefficients[i] + carry;
		sumNumber.coefficients[i] = (BASE)tempSum;
		carry = tempSum >> BASE_SIZE;
		i++;
	}

	sumNumber.coefficients[maxOfLengths] = carry;  // ��������� �������� �������

	// ������������� ����� ����������
	sumNumber.length = sumLength;
	sumNumber.lenNorm();

	return sumNumber;
}

// �������� �������� � �������������
bigNumber& bigNumber::operator+=(const bigNumber& other) {
	*this = *this + other;
	return *this;
}

// �������� ���������
bigNumber bigNumber::operator-(const bigNumber& other) const {
	if (*this < other) {
		throw invalid_argument("Invalid argument");  // ���� ������� ����� ������ �������, ����������� ����������
	}

	int j = 0;
	int borrow = 0;  // ����������� �����
	DBASE temp;
	bigNumber subtractionNum(length);
	while (j < other.length) {
		// ��������� �������� � ������ �����
		temp = ((DBASE)1 << BASE_SIZE) | coefficients[j];
		temp = temp - (DBASE)other.coefficients[j] - borrow;

		// ���������� �������� ��������
		subtractionNum.coefficients[j] = (BASE)temp;

		// ���������� ����� ����������� �����
		borrow = !(temp >> BASE_SIZE);

		j++;
	}

	while (j < length) {
		// ��������� ���� � �������� ���
		temp = ((DBASE)1 << BASE_SIZE) | coefficients[j];
		temp -= borrow;

		// ���������� ��������
		subtractionNum.coefficients[j] = (BASE)temp;

		// ���������� ����� ����������� �����
		borrow = !(temp >> BASE_SIZE);

		j++;
	}

	// ������������ ����������� ����� ����������
	subtractionNum.length = length;
	subtractionNum.lenNorm();

	return subtractionNum;  // ���������� ���������
}

// �������� ��������� � �������������
bigNumber& bigNumber::operator-=(const bigNumber& other) {
	*this = *this - other;
	return *this;
}

// ��������� �� ��������� �������� ���� BASE
bigNumber bigNumber::operator*(const BASE& multiplier) const {
	int j = 0;
	BASE carry = 0;
	bigNumber resNumber(length + 1);  // ������� ������ ��� ���������� � ����������� ��������� ������
	DBASE tmp;

	while (j < length) {
		tmp = (DBASE)coefficients[j] * (DBASE)multiplier + (DBASE)carry;
		resNumber.coefficients[j] = (BASE)tmp;
		carry = (BASE)(tmp >> BASE_SIZE);
		j++;
	}
	resNumber.coefficients[j] = carry;
	resNumber.length = length + 1;
	resNumber.lenNorm();
	return resNumber;
}

// �������� ��������� � ������������� ��� ������� ������� bigNumber
bigNumber& bigNumber::operator*=(const BASE& multiplier) {
	*this = *this * multiplier;  // ���������� �������� ��������� ��� �������� ������� � ������� bigNumber
	return *this;
}

// ��������� �� ������ ������ bigNumber
bigNumber bigNumber::operator*(const bigNumber& other) const {
	if (other.length == 1 && other.coefficients[0] == 0) {
		return bigNumber();
	}
	bigNumber resNumber(length + other.length);
	DBASE tmp;
	int j = 0;
	while (j < other.length) {
		if (other.coefficients[j] != 0) {
			BASE carry = 0;
			int i = 0;
			while (i < length) {
				tmp = (DBASE)coefficients[i] * (DBASE)other.coefficients[j] + (DBASE)resNumber.coefficients[i + j] + (DBASE)carry;
				resNumber.coefficients[i + j] = (BASE)tmp;
				carry = (BASE)(tmp >> BASE_SIZE);
				i++;
			}
			resNumber.coefficients[length + j] = carry;
		}
		j++;
	}
	resNumber.length = length + other.length;
	resNumber.lenNorm();
	return resNumber;
}

// �������� ��������� � ������������� ��� ���������� �������� BASE
bigNumber& bigNumber::operator*=(const bigNumber& other) {
	*this = *this * other;
	return *this;
}

// �������� ������� �� BASE
bigNumber bigNumber::operator/(const BASE& number) const { //�������������� j
	int j = 0;
	DBASE tmp = 0;
	BASE left = 0;
	bigNumber resNumber(length);
	while (j < length) {
		tmp = ((DBASE)left << BASE_SIZE) + (DBASE)coefficients[length - 1 - j];
		resNumber.coefficients[length - 1 - j] = (BASE)(tmp / (DBASE)number);
		left = (BASE)(tmp % (DBASE)number);
		j++;
	}

	resNumber.length = length;
	resNumber.lenNorm();
	return resNumber;
}

// �������� ������ ������� �� ������� �� BASE
bigNumber bigNumber::operator%(const BASE& number) const {
	int j = 0;
	DBASE tmp = 0;
	BASE left = 0;
	bigNumber resNumber(1);

	while (j < length) {
		tmp = ((DBASE)left << BASE_SIZE) + (DBASE)coefficients[length - 1 - j];
		left = (BASE)(tmp % (DBASE)number);
		j++;
	}

	resNumber.coefficients[0] = left;
	//resNumber.lenNorm();

	return resNumber;
}
bigNumber bigNumber::operator/(const bigNumber& divisor) const {
	if (divisor.length == 1 && divisor.coefficients[0] == 0) {
		throw std::invalid_argument("Division by zero.");
	}

	if (*this < divisor) {
		bigNumber result(1);
		return result;
	}

	if (divisor.length == 1) {
		return *this / divisor.coefficients[0];
	}

	DBASE base = ((DBASE)1 << BASE_SIZE);
	DBASE d = base / (DBASE)(divisor.coefficients[divisor.length - 1] + (BASE)1);
	int j = length - divisor.length;

	bigNumber dividend(*this);
	dividend *= d;
	bigNumber divisor_copy(divisor);
	divisor_copy *= d;

	bigNumber result(j + 1);
	result.length = j + 1;

	/*if (dividend.length == length) {
		dividend.maxLength++;
		dividend.length = maxLength;
		delete[] dividend.coefficients;
		dividend.coefficients = new BASE[maxLength];
		for (int i = 0; i < length; i++) {
			dividend.coefficients[i] = coefficients[i];
		}
		dividend *= d;
		dividend.length++;
		dividend.coefficients[dividend.length - 1] = 0;
	}*/

	while (j >= 0) {
		DBASE q = (DBASE)(((DBASE)((DBASE)(dividend.coefficients[j + divisor_copy.length]) * (DBASE)(base)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 1])) / (DBASE)(divisor_copy.coefficients[divisor_copy.length - 1]));//����� �������� �������
		DBASE r = (DBASE)(((DBASE)((DBASE)(dividend.coefficients[j + divisor_copy.length]) * (DBASE)(base)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 1])) % (DBASE)(divisor_copy.coefficients[divisor_copy.length - 1]));

		if (q == base || (DBASE)((DBASE)(q) * (DBASE)(divisor_copy.coefficients[divisor_copy.length - 2])) > (DBASE)(((DBASE)(base) * (DBASE)(r)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 2]))) {
			q--;
			r = (DBASE)(r)+(DBASE)(divisor_copy.coefficients[divisor_copy.length - 1]);
			if ((DBASE)(r) < base) {
				if (q == base || (DBASE)((DBASE)(q) * (DBASE)(divisor_copy.coefficients[divisor_copy.length - 2])) > (DBASE)(((DBASE)(base) * (DBASE)(r)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 2]))) {
					q--;
				}
			}
		}

		bigNumber u(divisor_copy.length + 1);
		u.length = divisor_copy.length + 1;
		for (int i = 0; i < divisor_copy.length + 1; i++) {
			u.coefficients[i] = dividend.coefficients[j + i];
		}

		if (u < divisor_copy * (BASE)(q)) {//�������������� ���������
			q--;
		}

		u = u - divisor_copy * (BASE)(q);
		result.coefficients[j] = (BASE)(q);

		for (int i = 0; i < divisor_copy.length + 1; i++) {
			dividend.coefficients[j + i] = u.coefficients[i];
		}

		j--;
	}

	result.lenNorm();

	return result;
}

bigNumber bigNumber::operator%(const bigNumber& divisor) const {
	if (divisor.length == 1 && divisor.coefficients[0] == 0) {
		throw std::invalid_argument("Division by zero.");
	}

	if (*this < divisor) {
		return *this;
	}

	if (divisor.length == 1) {
		return *this % divisor.coefficients[0];
	}

	int result_len = length - divisor.length;
	int base_size = BASE_SIZE;
	DBASE base = ((DBASE)1 << base_size);
	BASE d = (BASE)((DBASE)base / (DBASE)(divisor.coefficients[divisor.length - 1] + 1));
	int j = result_len;
	int k = 0;

	bigNumber dividend(*this);
	dividend *= d;
	bigNumber divisor_copy(divisor);
	divisor_copy *= d;

	if (dividend.length == length) {
		dividend.maxLength++;
		dividend.length = maxLength;
		dividend.coefficients = new BASE[maxLength];
		for (int i = 0; i < length; i++) {
			dividend.coefficients[i] = coefficients[i];
		}
		dividend *= d;
		dividend.length++;
		dividend.coefficients[dividend.length - 1] = 0;
	}

	while (j >= 0) {
		DBASE q = (DBASE)(((DBASE)((DBASE)(dividend.coefficients[j + divisor_copy.length]) * (DBASE)(base)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 1])) / (DBASE)(divisor_copy.coefficients[divisor_copy.length - 1]));
		DBASE r = (DBASE)(((DBASE)((DBASE)(dividend.coefficients[j + divisor_copy.length]) * (DBASE)(base)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 1])) % (DBASE)(divisor_copy.coefficients[divisor_copy.length - 1]));

		if (q == base || (DBASE)((DBASE)(q) * (DBASE)(divisor_copy.coefficients[divisor_copy.length - 2])) > (DBASE)(((DBASE)(base) * (DBASE)(r)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 2]))) {
			q--;
			r = (DBASE)(r)+(DBASE)(divisor_copy.coefficients[divisor_copy.length - 1]);
			if ((DBASE)(r) < base) {
				if (q == base || (DBASE)((DBASE)(q) * (DBASE)(divisor_copy.coefficients[divisor_copy.length - 2])) > (DBASE)(((DBASE)(base) * (DBASE)(r)) + (DBASE)(dividend.coefficients[j + divisor_copy.length - 2]))) {
					q--;
				}
			}
		}

		bigNumber u(divisor_copy.length + 1);
		u.length = divisor_copy.length + 1;
		for (int i = 0; i < divisor_copy.length + 1; i++) {
			u.coefficients[i] = dividend.coefficients[j + i];
		}

		if (u < divisor_copy * (BASE)(q)) {
			q--;
		}

		u = u - (divisor_copy * (BASE)(q));

		for (int i = 0; i < divisor_copy.length + 1; i++) {
			dividend.coefficients[j + i] = u.coefficients[i];
		}

		j--;
	}

	dividend.lenNorm();

	return dividend / d;
}

bool bigNumber::operator==(const bigNumber& other) const {
	if (length != other.length) {
		return false;
	}
	for (int i = 0; i < length; ++i) {
		if (coefficients[i] != other.coefficients[i]) {
			return false;
		}
	}
	return true;
}

bool bigNumber::operator!=(const bigNumber& other) const {
	if (length != other.length) {
		return true;
	}
	for (int i = 0; i < length; ++i) {
		if (coefficients[i] != other.coefficients[i]) {
			return true;
		}
	}
	return false;
}

bool bigNumber::operator<(const bigNumber& other) const {
	if (length < other.length) {
		return true;
	}
	if (length > other.length) {
		return false;
	}
	for (int i = length - 1; i >= 0; --i) {
		if (coefficients[i] < other.coefficients[i]) {
			return true;
		}
		if (coefficients[i] > other.coefficients[i]) {
			return false;
		}
	}
	return false;
}

bool bigNumber::operator>(const bigNumber& other) const {
	if (length > other.length) {
		return true;
	}

	if (length < other.length) {
		return false;
	}
	for (int i = length - 1; i >= 0; --i) {
		if (coefficients[i] > other.coefficients[i]) {
			return true;
		}
		if (coefficients[i] < other.coefficients[i]) {
			return false;
		}
	}
	return false;
}

bool bigNumber::operator<=(const bigNumber& other) const {
	if (length > other.length) {
		return false;
	}
	if (length < other.length) {
		return true;
	}
	for (int i = length - 1; i >= 0; --i) {
		if (coefficients[i] < other.coefficients[i]) {
			return true;
		}
		if (coefficients[i] > other.coefficients[i]) {
			return false;
		}
	}
	return true;
}

bool bigNumber::operator>=(const bigNumber& other) const {
	if (length < other.length) {
		return false;
	}
	if (length > other.length) {
		return true;
	}
	for (int i = length - 1; i >= 0; --i) {
		if (coefficients[i] > other.coefficients[i]) {
			return true;
		}
		if (coefficients[i] < other.coefficients[i]) {
			return false;
		}
	}
	return true;
}

istream& operator>>(istream& in, bigNumber& bNum) {
	int j = 0;
	string inputString;
	getline(in, inputString);
	int inputStringLength = inputString.length();
	BASE t = 0;

	bigNumber temp((inputStringLength - 1) / (BASE_SIZE / 4) + 1);

	while (j < inputStringLength) {
		if ('0' > inputString[j] || inputString[j] > '9') {
			throw invalid_argument("Invalid arguments");
		}
		t = inputString[j] - '0';
		temp = temp * ((BASE)10);

		bigNumber newNum;
		newNum.coefficients[0] = (BASE)t;
		temp += newNum;
		j++;
	}

	temp.length = temp.maxLength;
	temp.lenNorm();

	bNum = temp;

	return in;
}

ostream& operator<<(ostream& out, bigNumber& bN) {
	bigNumber newNum = bN;  // ���������� ���������� ������ bN
	bigNumber zero(newNum.length);
	string s;
	while (newNum != zero) {
		bigNumber t = newNum % 10;
		s.push_back(t.coefficients[0] + '0');
		newNum = newNum / 10;
	}
	reverse(s.begin(), s.end());
	out << s;  // ������� ������ s � ����� out
	return out;
}