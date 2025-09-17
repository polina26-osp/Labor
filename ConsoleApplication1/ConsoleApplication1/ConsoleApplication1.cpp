#include <iostream>
#include <windows.h>
#include <random>
#include <chrono>
using namespace std;

const int MAXN = 20;
int n;   // количество городов
int cost[MAXN][MAXN];
int startCity;
int bestCost;
int bestPut[MAXN];
int tekushPut[MAXN];
bool posetil[MAXN];

void Perebor(int nomerShaga, int tekushCity, int tekushCost) {
    if (nomerShaga == n) {
        tekushCost += cost[tekushCity][startCity];                        //закрыли цикл

        // выводим маршрут
        /*
        cout << "Маршрут: ";
        for (int i = 0; i < n; i++) cout << tekushPut[i] << " ";
        cout << startCity << "  | Стоимость = " << tekushCost << "\n";
        */

        // обновляем лучший маршрут
        if (tekushCost < bestCost) {
            bestCost = tekushCost;
            for (int i = 0; i < n; i++) bestPut[i] = tekushPut[i];
        }
        return;
    }

    //перебор всех городов, которые не посетили
    for (int next = 0; next < n; next++) {
        if (!posetil[next]) {
            posetil[next] = true;
            tekushPut[nomerShaga] = next;
            Perebor(nomerShaga + 1, next, tekushCost + cost[tekushCity][next]);
            posetil[next] = false;
        }
    }
}

// функция генерации случайной матрицы стоимости
void RandomMatr(int minCost, int maxCost) {
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_int_distribution<int> distribution(minCost, maxCost);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) cost[i][j] = 0;
            else cost[i][j] = distribution(generator);
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "Введите количество городов: ";
    cin >> n;

    char vybor;
    cout << "Заполнить матрицу случайными значениями? (y/n): ";
    cin >> vybor;

    if (vybor == 'y') {
        int minCost, maxCost;
        cout << "Введите минимальную и максимальную стоимость: ";
        cin >> minCost >> maxCost;

        RandomMatr(minCost, maxCost);

        cout << "Сгенерированная матрица стоимостей:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << cost[i][j] << " ";
            }
            cout << "\n";
        }
    }
    else {
        cout << "Введите матрицу стоимостей (" << n << "x" << n << "):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> cost[i][j];
            }
        }
    }
    // поиск наибольшего перехода между городами
    int max = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (cost[i][j] > max) max = cost[i][j];
    bestCost = max * n;

    cout << "Введите начальный город (от 0 до " << n - 1 << "): ";
    cin >> startCity;

    for (int i = 0; i < n; i++) posetil[i] = false;      // все города считаем непосещенными
    posetil[startCity] = true;                        
    tekushPut[0] = startCity;

    // замер времени
    chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    Perebor(1, startCity, 0);
    chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();

    cout << "\nМинимальная стоимость: " << bestCost << "\n";
    cout << "Маршрут: ";
    for (int i = 0; i < n; i++) cout << bestPut[i] << " ";
    cout << startCity << "\n";

    chrono::duration<double> duration = timeEnd - timeStart;
    cout << "Время выполнения: " << duration.count() << " сек.\n";

    return 0;
}
