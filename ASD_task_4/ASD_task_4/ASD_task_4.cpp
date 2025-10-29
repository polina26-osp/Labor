#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>

// Функция для ввода массива с консоли
std::vector<int> inputArrayFromConsole() {
    std::vector<int> arr;
    int numValues;

    std::cout << "Введите количество элементов массива: ";
    std::cin >> numValues;

    if (numValues <= 0) {
        std::cout << "Некорректный размер массива!" << std::endl;
        return arr;
    }

    arr.resize(numValues);
    std::cout << "Введите " << numValues << " элементов массива через пробел: ";

    for (int i = 0; i < numValues; i++) {
        std::cin >> arr[i];
    }

    return arr;
}

// Функция для чтения массива из файла
std::vector<int> readArrayFromFile(const std::string& filename) {
    std::vector<int> arr;
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename.c_str(), "r");

    if (file == NULL) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return arr;
    }

    int value;
    while (fscanf_s(file, "%d", &value) == 1) {
        arr.push_back(value);
    }

    fclose(file);
    return arr;
}

// Функция для чтения всех массивов из списка файлов
std::vector<std::vector<int>> readArraysFromFiles(const std::vector<std::string>& filenames) {
    std::vector<std::vector<int>> arrays;

    for (size_t i = 0; i < filenames.size(); ++i) {
        std::vector<int> arr = readArrayFromFile(filenames[i]);
        if (!arr.empty()) {
            arrays.push_back(arr);
            std::cout << "Прочитан массив из " << filenames[i] << " (размер: " << arr.size() << ")" << std::endl;
        }
    }

    return arrays;
}

// Функция проверки отсортированности массива
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Алгоритм сортировки Шелла с заданной последовательностью шагов
void shellSort(std::vector<int>& arr, const std::vector<int>& gaps) {
    for (size_t i = 0; i < gaps.size(); ++i) {
        int s = gaps[i];
        for (int b = 0; b < s; ++b) {
            // Сортировка вставками для подпоследовательности
            for (int j = b + s; j < arr.size(); j = j + s) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
            }
        }
    }
}

// Генерация последовательности шагов по методу Шелла
std::vector<int> gaps1(int n) {
    std::vector<int> gaps;
    for (int h = n / 2; h > 0; h = h / 2) {
        gaps.push_back(h);
    }
    return gaps;
}

// Генерация последовательности шагов по второму методу
std::vector<int> gaps2(int n) {
    std::vector<int> gaps;
    int m = 1;
    while (1) {
        int gap = pow(2, m) - 1;
        if (gap > n) break;
        gaps.push_back(gap);
        m++;
    }
    // Разворот последовательности для убывания 
    std::vector<int> reversed_gaps;
    for (int i = (int)gaps.size() - 1; i >= 0; i--) {
        reversed_gaps.push_back(gaps[i]);
    }
    return reversed_gaps;
}
    

// Генерация последовательности шагов по методу Кнута
std::vector<int> gaps3(int n) {
    std::vector<int> gaps;
    int h = 1;
    while (h <= n) {
        gaps.push_back(h);
        h = 3 * h + 1;
    }
    // Разворот последовательности для убывания 
    std::vector<int> reversed_gaps;
    for (int i = (int)gaps.size() - 1; i >= 0; i--) {
        reversed_gaps.push_back(gaps[i]);
    }
    return reversed_gaps;
}
   

// Тестирование алгоритма на заданном массиве
void testSort(const std::vector<int>& testArray, const std::string& gapType) {
    std::vector<int> gaps;
    if (gapType == "Gaps1") {
        gaps = gaps1(testArray.size());
    }
    else if (gapType == "Gaps2") {
        gaps = gaps2(testArray.size());
    }
    else if (gapType == "Gaps3") {
        gaps = gaps3(testArray.size());
    }

    double totalTime = 0;
    const int runs = 3;

    for (int i = 0; i < runs; ++i) {
        std::vector<int> arr = testArray;
        std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
        shellSort(arr, gaps);
        std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = timeEnd - timeStart;
        totalTime += duration.count();

        if (!isSorted(arr)) {
            std::cout << "Ошибка: массив не отсортирован!" << std::endl;
            return;
        }
    }

    std::cout << gapType << " среднее время = "
        << totalTime / runs << " секунд" << std::endl;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int choice;
    std::vector<std::vector<int>> testArrays;

    std::cout << "Выберите способ ввода данных: 1 - файлы с массивами, 2 - вручную :" << std::endl;
    std::cin >> choice;

    if (choice == 1) {
        std::vector<std::string> filenames = {
            "array_10000_-10_10.txt",
            "array_10000_-1000_1000.txt",
            "array_10000_-100000_100000.txt",
            "array_100000_-10_10.txt",
            "array_100000_-1000_1000.txt",
            "array_100000_-100000_100000.txt",
            "array_1000000_-10_10.txt",
            "array_1000000_-1000_1000.txt",
            "array_1000000_-100000_100000.txt",
        };

        testArrays = readArraysFromFiles(filenames);

        if (testArrays.empty()) {
            std::cout << "Ошибка: не удалось прочитать ни одного массива из файлов" << std::endl;
            return 1;
        }
    }
    else if (choice == 2) {
        std::vector<int> manualArray = inputArrayFromConsole();
        if (!manualArray.empty()) {
            testArrays.push_back(manualArray);
        }
        else {
            std::cout << "Ошибка: не удалось создать массив" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "Не 1 или 2 " << std::endl;
        return 1;
    }

    for (size_t i = 0; i < testArrays.size(); ++i) {
        std::cout << "Тестовый массив " << i + 1 << " (размер: " << testArrays[i].size() << "):\n";
        testSort(testArrays[i], "Gaps1");
        testSort(testArrays[i], "Gaps2");
        testSort(testArrays[i], "Gaps3");
        std::cout << std::endl;
    }

    return 0;
}