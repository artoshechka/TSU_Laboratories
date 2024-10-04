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
    int lowerBound;
    int upperBound;
};

// Cортировка по убыванию частоты
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
        if (inputFile.eof()) break;
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
    ranges.begin()->upperBound = ranges.begin()->frequency;
    ranges.begin()->lowerBound = 0;
    auto it = ranges.begin();
    auto prev_it = it;
    it++;

    for (; it != ranges.end(); it++) {
        it->lowerBound = prev_it->upperBound;
        it->upperBound = it->lowerBound + it->frequency;
        prev_it++;
    }
}

// Функция для записи диапазонов символов в файл
void saveRanges(ofstream& rangesFile, const list<Range>& ranges) {
    for (const auto& range : ranges) {
        rangesFile.write(reinterpret_cast<const char*>(&range.symbol), sizeof(range.symbol));
        rangesFile.write(reinterpret_cast<const char*>(&range.frequency), sizeof(range.frequency));
        rangesFile.write(reinterpret_cast<const char*>(&range.lowerBound), sizeof(range.lowerBound));
        rangesFile.write(reinterpret_cast<const char*>(&range.upperBound), sizeof(range.upperBound));
    }
}

// Функция для чтения диапазонов символов из файла
list<Range> loadRanges(ifstream& rangesFile) {
    list<Range> ranges;
    while (!rangesFile.eof()) {
        Range range;
        rangesFile.read(reinterpret_cast<char*>(&range.symbol), sizeof(range.symbol));
        rangesFile.read(reinterpret_cast<char*>(&range.frequency), sizeof(range.frequency));
        rangesFile.read(reinterpret_cast<char*>(&range.lowerBound), sizeof(range.lowerBound));
        rangesFile.read(reinterpret_cast<char*>(&range.upperBound), sizeof(range.upperBound));
        if (rangesFile.eof()) break;  // Проверка на конец файла
        ranges.push_back(range);
    }
    return ranges;
}

// Функция кодирования
double encode(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);

    if (!inputFile || !outputFile) {
        cerr << "Error opening input or output file." << endl;
        return 0;
    }

    int totalCount = 0;
    auto frequencyMap = countFrequencies(inputFilename, totalCount);
    auto ranges = createAndSortRanges(frequencyMap);
    setRangeBounds(ranges);

    // Сохраняем диапазоны в выходной файл
    outputFile.write(reinterpret_cast<const char*>(&totalCount), sizeof(totalCount));
    int rangesSize = ranges.size();
    outputFile.write(reinterpret_cast<const char*>(&rangesSize), sizeof(rangesSize));
    saveRanges(outputFile, ranges);

    // Сброс указателей на начало файла
    inputFile.clear();
    inputFile.seekg(0);

    // Начальные параметры для кодирования
    int low = 0, high = 65535;
    int divider = ranges.back().upperBound;
    int firstQuarter = (high + 1) / 4;
    int half = firstQuarter * 2;
    int thirdQuarter = firstQuarter * 3;
    int bitsToFollow = 0;
    char buffer = 0;
    int bitCount = 0;

    // Основной цикл кодирования
    while (!inputFile.eof()) {
        char c = inputFile.get();
        if (inputFile.eof()) break;

        auto it = ranges.begin();
        for (; it != ranges.end(); it++) {
            if (c == it->symbol) break;
        }

        int range = high - low + 1;
        high = low + (it->upperBound * range) / divider - 1;
        low = low + (it->lowerBound * range) / divider;

        while (true) {
            if (high < half) {
                buffer <<= 1;
                bitCount++;
                if (bitCount == 8) {
                    outputFile.put(buffer);
                    buffer = 0;
                    bitCount = 0;
                }
                for (; bitsToFollow > 0; bitsToFollow--) {
                    buffer = (buffer << 1) | 1;
                    bitCount++;
                    if (bitCount == 8) {
                        outputFile.put(buffer);
                        buffer = 0;
                        bitCount = 0;
                    }
                }
            }
            else if (low >= half) {
                buffer = (buffer << 1) | 1;
                bitCount++;
                if (bitCount == 8) {
                    outputFile.put(buffer);
                    buffer = 0;
                    bitCount = 0;
                }
                for (; bitsToFollow > 0; bitsToFollow--) {
                    buffer <<= 1;
                    bitCount++;
                    if (bitCount == 8) {
                        outputFile.put(buffer);
                        buffer = 0;
                        bitCount = 0;
                    }
                }
                low -= half;
                high -= half;
            }
            else if (low >= firstQuarter && high < thirdQuarter) {
                bitsToFollow++;
                low -= firstQuarter;
                high -= firstQuarter;
            }
            else {
                break;
            }
            low <<= 1;
            high = (high << 1) + 1;
        }
    }

    // Записываем остаток буфера
    buffer <<= (8 - bitCount);
    outputFile.put(buffer);

    inputFile.close();
    outputFile.close();
    return static_cast<double>(outputFile.tellp()) / totalCount;
}

// Функция декодирования
bool decode(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);

    if (!inputFile || !outputFile) {
        cerr << "Error opening input or output file." << endl;
        return false;
    }

    int totalCount;
    inputFile.read(reinterpret_cast<char*>(&totalCount), sizeof(totalCount));
    int rangesSize;
    inputFile.read(reinterpret_cast<char*>(&rangesSize), sizeof(rangesSize));

    // Загружаем диапазоны
    list<Range> ranges;
    for (int i = 0; i < rangesSize; i++) {
        Range range;
        inputFile.read(reinterpret_cast<char*>(&range.symbol), sizeof(range.symbol));
        inputFile.read(reinterpret_cast<char*>(&range.frequency), sizeof(range.frequency));
        inputFile.read(reinterpret_cast<char*>(&range.lowerBound), sizeof(range.lowerBound));
        inputFile.read(reinterpret_cast<char*>(&range.upperBound), sizeof(range.upperBound));
        ranges.push_back(range);
    }
    // Проверяем, что мы считали правильное количество диапазонов
    if (ranges.size() != rangesSize) {
        cerr << "Error loading ranges from file." << endl;
        return false;
    }

    // Остальная часть функции остается без изменений
    int low = 0, high = 65535, divider = ranges.back().upperBound;
    int firstQuarter = (high + 1) / 4;
    int half = firstQuarter * 2;
    int thirdQuarter = firstQuarter * 3;
    int value = (inputFile.get() << 8) | inputFile.get();
    char buffer = inputFile.get();
    int bitCount = 0;

    for (int i = 0; i < totalCount; i++) {
        int range = high - low + 1;
        int freq = ((value - low + 1) * divider - 1) / range;

        auto it = ranges.begin();
        for (; it != ranges.end(); it++) {
            if (it->upperBound > freq) break;
        }

        high = low + (it->upperBound * range) / divider - 1;
        low = low + (it->lowerBound * range) / divider;

        while (true) {
            if (high < half) {
                // Ничего не делаем
            }
            else if (low >= half) {
                low -= half;
                high -= half;
                value -= half;
            }
            else if (low >= firstQuarter && high < thirdQuarter) {
                low -= firstQuarter;
                high -= firstQuarter;
                value -= firstQuarter;
            }
            else {
                break;
            }
            low <<= 1;
            high = (high << 1) + 1;
            value = (value << 1) + (((short)buffer >> (7 - bitCount)) & 1);
            bitCount++;
            if (bitCount == 8) {
                buffer = inputFile.get();
                bitCount = 0;
            }
        }

        outputFile.put(it->symbol);
    }

    inputFile.close();
    outputFile.close();
    return true;
}
