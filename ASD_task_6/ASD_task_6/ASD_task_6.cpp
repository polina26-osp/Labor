#include <iostream>
#include <vector>  
#include <ctime>     
#include <Windows.h>
#include <chrono>

using namespace std;

// Функция для получения k-го бита числа
int getBit(int num, int k) {
    const int sign_bit = 31;

    if (k == sign_bit) {
        // Знаковый бит инвертируем для правильного порядка
        return (num >= 0) ? 1 : 0;
    }
    else {
        uint32_t value = (uint32_t)num;
        return (value >> k) & 1;
    }
}

// Побитовая сортировка
void bitsort(vector<int>& A, int l, int r, int k) { // k = номер старшего разряда
    if (l >= r || k < 0) return;

    int i = l, j = r;

    while (i <= j) {
  
        while (i <= j && getBit(A[i], k) == 0) i++;

        while (i <= j && getBit(A[j], k) == 1) j--;

        if (i < j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    }
    bitsort(A, l, j, k - 1);
    bitsort(A, i, r, k - 1);
}

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

// Функция для вывода массива
void printArray(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
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

// Тестирование побитовой сортировки
void testBitSort(const vector<int>& testArray, bool isManualInput = false) {
    vector<int> arr = testArray; // копия для тестирования

    chrono::high_resolution_clock::time_point timeStart = chrono::high_resolution_clock::now();

    // Вызов побитовой сортировки, проверка, что массив не пустой
    if (!arr.empty()) {
        bitsort(arr, 0, (int)arr.size() - 1, 31);
    }

    chrono::high_resolution_clock::time_point timeEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = timeEnd - timeStart;

    if (!isSorted(arr)) {
        cout << "Ошибка: массив не отсортирован!" << endl;
        return;
    }

    cout << "Время = " << duration.count() << " секунд" << endl;

    // Если ручной ввод, выводим отсортированный массив
    if (isManualInput) {
        cout << "Отсортированный массив: ";
        printArray(arr);
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    int choice;
    vector<vector<int>> testArrays;

    cout << "Выберите способ ввода данных: 1 - файлы с массивами, 2 - вручную :" << endl;
    cin >> choice;

    if (choice == 1) {
        vector<std::string> filenames = {
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
            cout << "Ошибка: не удалось прочитать массив из файлов" << endl;
            return 1;
        }

        // Тестирование побитовой сортировки на каждом массиве
        for (size_t i = 0; i < testArrays.size(); ++i) {
            cout << "Тестовый массив " << i + 1 << " (размер: " << testArrays[i].size() << "):" << endl;
            testBitSort(testArrays[i], false);
            cout << endl;
        }
    }
    else if (choice == 2) {
        vector<int> manualArray = inputArrayFromConsole();
        if (!manualArray.empty()) {
            cout << "Исходный массив: ";
            printArray(manualArray);

            testArrays.push_back(manualArray);

            // Тестирование побитовой сортировки на ручном массиве 
            testBitSort(manualArray, true);
        }
        else {
            cout << "Ошибка: не удалось создать массив" << endl;
            return 1;
        }
    }
    else {
        cout << "Не 1 или 2 " << endl;
        return 1;
    }

    return 0;
}