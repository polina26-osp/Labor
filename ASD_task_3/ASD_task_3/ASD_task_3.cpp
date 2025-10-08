#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// Просеивание вниз 
void siftDown(vector<int>& x, int start, int end) {
    int root = start;
    while (2 * root + 1 <= end) {  // Пока есть хотя бы левый потомок
        int leftChild = 2 * root + 1;      
        int rightChild = 2 * root + 2;    
        int swapIndex = root;              // начинаем обменивать с корня

        // Сравниваем с левым потомком
        if (x[swapIndex] < x[leftChild])
            swapIndex = leftChild;

        // Сравниваем с правым потомком (если он существует)
        if (rightChild <= end && x[swapIndex] < x[rightChild])
            swapIndex = rightChild;

        if (swapIndex == root)
            return;

        swap(x[root], x[swapIndex]);
        root = swapIndex;
    }
}

// Этап 1: построение пирамиды
void buildHeap(vector<int>& x) {
    int n = x.size();
      // просеивание половины массива
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(x, i, n - 1);
    }
}

// Этап 2: сортировка 
void heapSort(vector<int>& x) {
    int n = x.size();
    buildHeap(x);
    for (int k = n - 1; k > 0; k--) {        // k - индекс последнего элемента в еще не отсортированной части массива 
        swap(x[0], x[k]);
        siftDown(x, 0, k - 1);
    }
}

// Проверка на упорядоченность 
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    cout << "Выберите способ заполнения массива: 1 - рандомный массив, 2 - ввод с консоли : ";
    cin >> choice; 

    vector<int> x;

    if (choice == 1) {
        // Случайные числа
        int rangeStart, rangeEnd, numValues;
        cout << "Введите диапазон случайных чисел (начало и конец): ";
        cin >> rangeStart >> rangeEnd;
        cout << "Введите количество элементов массива: ";
        cin >> numValues;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(rangeStart, rangeEnd);

        x.resize(numValues);
        for (int i = 0; i < numValues; i++) {
            x[i] = dist(gen);
        }

    }
 else if (choice == 2) {
     // Ввод с консоли
     int numValues;
     cout << "Введите количество элементов массива: ";
     cin >> numValues;

     x.resize(numValues);
     cout << "Введите элементы массива: ";
     for (int i = 0; i < numValues; i++) {
         cin >> x[i];
     }
   }

 else {
     cout << "Ошибка: введено что-то кроме 1 или 2 \n";
     return 1;
    }

#if 0
    // Вывод исходного массива
    cout << "\nСгенерированный массив:\n";
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << "\n";
#endif

    // Замер времени и сортировка
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    heapSort(x);

    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << "\nВремя сортировки: " << duration.count() << " секунд";

#if 0
    // Вывод отсортированного массива
    cout << "\nОтсортированный массив:\n";
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << "\n";
    cout << "\n";
#endif

    cout << "Отсортирован ли массив? ";
    if (isSorted(x))
        cout << "Да";
    else
        cout << "Нет";
    cout << endl;

    return 0;
}