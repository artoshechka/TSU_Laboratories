#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>

using namespace std;

// Структура для хранения диапазона символов
struct Range {
	char symbol;
	int frequency;
	int lower_bound;
	int upper_bound;
};

// Компаратор для сортировки по убыванию частоты
struct SortByFrequency {
	bool operator() (Range l, Range r) {
		return l.frequency > r.frequency;
	}
};

// Функция для подсчета частоты символов в файле
map<char, int> countFrequencies(const string& inputFilename, int& total_count) {
	ifstream inputFile(inputFilename, ios::binary);
	map<char, int> frequency_map;
	total_count = 0;

	while (!inputFile.eof()) {
		char c = inputFile.get();
		if (inputFile.eof()) break;  // Проверка на конец файла
		frequency_map[c]++;
		total_count++;
	}
	return frequency_map;
}

// Функция для создания и сортировки диапазонов символов
list<Range> createAndSortRanges(const map<char, int>& frequency_map) {
	list<Range> ranges;
	for (const auto& pair : frequency_map) {
		Range range;
		range.symbol = pair.first;
		range.frequency = pair.second;
		ranges.push_back(range);
	}
	ranges.sort(SortByFrequency());
	return ranges;
}

// Функция для установки начальных значений диапазонов
void setRangeBounds(list<Range>& ranges) {
	ranges.begin()->upper_bound = ranges.begin()->frequency;
	ranges.begin()->lower_bound = 0;
	auto it = ranges.begin();
	auto prev_it = it;
	it++;

	for (; it != ranges.end(); it++) {
		it->lower_bound = prev_it->upper_bound;
		it->upper_bound = it->lower_bound + it->frequency;
		prev_it++;
	}
}

// Функция для записи диапазонов символов в файл
void saveRanges(const list<Range>& ranges, const string& rangesFilename) {
	ofstream rangesFile(rangesFilename, ios::binary);
	for (const auto& range : ranges) {
		rangesFile.write(reinterpret_cast<const char*>(&range.symbol), sizeof(range.symbol));
		rangesFile.write(reinterpret_cast<const char*>(&range.frequency), sizeof(range.frequency));
		rangesFile.write(reinterpret_cast<const char*>(&range.lower_bound), sizeof(range.lower_bound));
		rangesFile.write(reinterpret_cast<const char*>(&range.upper_bound), sizeof(range.upper_bound));
	}
}

// Функция для чтения диапазонов символов из файла
list<Range> loadRanges(const string& rangesFilename) {
	ifstream rangesFile(rangesFilename, ios::binary);
	list<Range> ranges;
	while (!rangesFile.eof()) {
		Range range;
		rangesFile.read(reinterpret_cast<char*>(&range.symbol), sizeof(range.symbol));
		rangesFile.read(reinterpret_cast<char*>(&range.frequency), sizeof(range.frequency));
		rangesFile.read(reinterpret_cast<char*>(&range.lower_bound), sizeof(range.lower_bound));
		rangesFile.read(reinterpret_cast<char*>(&range.upper_bound), sizeof(range.upper_bound));
		if (rangesFile.eof()) break;  // Проверка на конец файла
		ranges.push_back(range);
	}
	return ranges;
}

// Функция кодирования
double encode(const string& inputFilename, const string& outputFilename, const string& rangesFilename) {
	ifstream inputFile(inputFilename, ios::binary);
	ofstream outputFile(outputFilename, ios::binary);

	if (!inputFile || !outputFile) {
		cerr << "Error opening input or output file." << endl;
		return 0;
	}

	int total_count = 0;
	auto frequency_map = countFrequencies(inputFilename, total_count);
	auto ranges = createAndSortRanges(frequency_map);
	setRangeBounds(ranges);
	saveRanges(ranges, rangesFilename);

	// Сброс указателей на начало файла
	inputFile.clear();
	inputFile.seekg(0);

	// Начальные параметры для кодирования
	int low = 0, high = 65535;
	int divider = ranges.back().upper_bound;
	int first_quarter = (high + 1) / 4, half = first_quarter * 2, third_quarter = first_quarter * 3;
	int bits_to_follow = 0;
	char buffer = 0;
	int bit_count = 0;

	// Основной цикл кодирования
	while (!inputFile.eof()) {
		char c = inputFile.get();
		if (inputFile.eof()) break;  // Проверка на конец файла

		auto it = ranges.begin();
		for (; it != ranges.end(); it++) {
			if (c == it->symbol) break;
		}

		int range = high - low + 1;
		high = low + (it->upper_bound * range) / divider - 1;
		low = low + (it->lower_bound * range) / divider;

		while (true) {
			if (high < half) {
				// Выход 0
				buffer <<= 1;
				bit_count++;
				if (bit_count == 8) {
					outputFile.put(buffer);
					buffer = 0;
					bit_count = 0;
				}
				for (; bits_to_follow > 0; bits_to_follow--) {
					buffer = (buffer << 1) | 1;
					bit_count++;
					if (bit_count == 8) {
						outputFile.put(buffer);
						buffer = 0;
						bit_count = 0;
					}
				}
			}
			else if (low >= half) {
				// Выход 1
				buffer = (buffer << 1) | 1;
				bit_count++;
				if (bit_count == 8) {
					outputFile.put(buffer);
					buffer = 0;
					bit_count = 0;
				}
				for (; bits_to_follow > 0; bits_to_follow--) {
					buffer <<= 1;
					bit_count++;
					if (bit_count == 8) {
						outputFile.put(buffer);
						buffer = 0;
						bit_count = 0;
					}
				}
				low -= half;
				high -= half;
			}
			else if (low >= first_quarter && high < third_quarter) {
				// Следующий бит
				bits_to_follow++;
				low -= first_quarter;
				high -= first_quarter;
			}
			else {
				break;
			}
			low <<= 1;
			high = (high << 1) + 1;
		}
	}

	// Записываем остаток буфера
	buffer <<= (8 - bit_count);
	outputFile.put(buffer);

	inputFile.close();
	outputFile.close();
	return static_cast<double>(outputFile.tellp()) / total_count;
}

// Функция декодирования
bool decode(const string& inputFilename, const string& outputFilename, const string& rangesFilename) {
	ifstream inputFile(inputFilename, ios::binary);
	ofstream outputFile(outputFilename, ios::binary);

	if (!inputFile || !outputFile) {
		cerr << "Error opening input or output file." << endl;
		return false;
	}

	auto ranges = loadRanges(rangesFilename);
	if (ranges.empty()) {
		cerr << "Error loading ranges from file." << endl;
		return false;
	}

	int low = 0, high = 65535, divider = ranges.back().upper_bound;
	int first_quarter = (high + 1) / 4, half = first_quarter * 2, third_quarter = first_quarter * 3;
	int value = (inputFile.get() << 8) | inputFile.get();
	char buffer = inputFile.get();
	int bit_count = 0;

	while (!inputFile.eof()) {
		int range = high - low + 1;
		int freq = ((value - low + 1) * divider - 1) / range;

		auto it = ranges.begin();
		for (; it != ranges.end(); it++) {
			if (it->upper_bound > freq) break;
		}

		high = low + (it->upper_bound * range) / divider - 1;
		low = low + (it->lower_bound * range) / divider;

		while (true) {
			if (high < half) {
				// Ничего не делаем
			}
			else if (low >= half) {
				low -= half;
				high -= half;
				value -= half;
			}
			else if (low >= first_quarter && high < third_quarter) {
				low -= first_quarter;
				high -= first_quarter;
				value -= first_quarter;
			}
			else {
				break;
			}
			low <<= 1;
			high = (high << 1) + 1;
			value = (value << 1) + (((short)buffer >> (7 - bit_count)) & 1);
			bit_count++;
			if (bit_count == 8) {
				buffer = inputFile.get();
				bit_count = 0;
			}
		}

		outputFile.put(it->symbol);
	}

	inputFile.close();
	outputFile.close();
	return true;
}

int main() {
	cout << "Выберите действие:\n1. Кодировать\n2. Декодировать\n";
	int choice;
	cin >> choice;

	if (choice == 1) {
		string inputFilename = "text.txt";
		string outputFilename = "encoded.bin";
		string rangesFilename = "ranges.dat";

		double compression_ratio = encode(inputFilename, outputFilename, rangesFilename);
		cout << "Коэффициент сжатия: " << compression_ratio << endl;
	}
	else if (choice == 2) {
		string inputFilename = "encoded.bin";
		string outputFilename = "decoded.txt";
		string rangesFilename = "ranges.dat";

		if (decode(inputFilename, outputFilename, rangesFilename)) {
			cout << "Декодирование успешно" << endl;
		}
		else {
			cout << "Ошибка декодирования" << endl;
		}
	}
	else {
		cout << "Неверный выбор" << endl;
	}

	return 0;
}
