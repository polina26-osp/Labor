#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// --- Просеивание вниз ---
void siftDown(vector<int>& x, int start, int end) {
    int root = start;
    while (2 * root + 1 <= end) {
        int child = 2 * root + 1;
        int swapIndex = root;

        if (x[swapIndex] < x[child])
            swapIndex = child;
        if (child + 1 <= end && x[swapIndex] < x[child + 1])
            swapIndex = child + 1;

        if (swapIndex == root)
            return;

        swap(x[root], x[swapIndex]);
        root = swapIndex;
    }
}

// --- Этап 1: построение пирамиды ---
void buildHeap(vector<int>& x) {
    int n = x.size();
#if 0
     cout << "\nЭтап 1. Построение пирамиды:\n";
      cout << "Исходный массив: ";
      for (int i = 0; i < x.size(); i++) cout << x[i] << " ";
      cout << "\n";

      cout << "Правая часть (готовая пирамида): ";
      for (int i = n / 2; i < n; i++) cout << x[i] << " ";
      cout << "\nЛевая часть (просеивается): ";
      for (int i = 0; i < n / 2; i++) cout << x[i] << " ";
      cout << "\n\n";
      
#endif
      // просеивание левой половины
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(x, i, n - 1);
#if 0
         cout << "После просеивания элемента x[" << i << "] = " << x[i] << ": ";
         for (int j = 0; j < x.size(); j++) cout << x[j] << " ";
         cout << "\n"; 
#endif
    }
#if 0
    cout << "\nПостроенная пирамида: ";
    for (int i = 0; i < x.size(); i++) cout << x[i] << " ";
    cout << "\n\n"; */
#endif
}

// --- Этап 2: сортировка ---
void heapSort(vector<int>& x) {
    int n = x.size();
    buildHeap(x);
    /* cout << "Этап 2. Основные итерации сортировки:\n\n"; */

    for (int k = n - 1; k > 0; k--) {
        //cout << "Обмен x[0] = " << x[0] << " и x[" << k << "] = " << x[k] << endl;
        swap(x[0], x[k]);

        // cout << "Просеивание новой вершины x[0] = " << x[0] << " через элементы до индекса " << k - 1 << endl;

        siftDown(x, 0, k - 1);

        /*cout << "После шага " << (n - k) << ": ";
        for (int j = 0; j < x.size(); j++) cout << x[j] << " ";
        cout << "\n\n"; */
    }

    /*cout << "Результат сортировки: ";
    for (int i = 0; i < x.size(); i++) cout << x[i] << " ";
    cout << "\n";*/
}

// --- Проверка на упорядоченность ---
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

// --- Главная программа ---
int main() {
    setlocale(LC_ALL, "Russian");

    int rangeStart, rangeEnd, numValues;
    cout << "Введите диапазон случайных чисел (начало и конец): ";
    cin >> rangeStart >> rangeEnd;
    cout << "Введите количество элементов массива: ";
    cin >> numValues;

    // Генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(rangeStart, rangeEnd);

    vector<int> x(numValues);
    for (int i = 0; i < numValues; i++) {
        x[i] = dist(gen);
    }

    cout << "\nСгенерированный массив:\n";
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << "\n";

    // Замер времени
    auto start = chrono::high_resolution_clock::now();
    heapSort(x);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << "\nВремя сортировки: " << duration.count() << " секунд ("
        << chrono::duration_cast<chrono::milliseconds>(duration).count()
        << " мс)\n";

    cout << "Отсортирован ли массив? ";
    if (isSorted(x))
        cout << "Да";
    else
        cout << "Нет";
    cout << endl;

    return 0;
}
