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

// эвристический метод
void Everystic() {
    for (int i = 0; i < n; i++) posetil[i] = false;

    int totalCost = 0;

    int current = startCity;
    posetil[current] = true;
    tekushPut[0] = current;

    // находим максимально возможное ребро (для minCost)
    int maxEdge = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (cost[i][j] > maxEdge) maxEdge = cost[i][j];

    for (int step = 1; step < n; step++) {
        int nextCity = -1;
        int minCost = maxEdge + 1; // гарантированно больше любого ребра

        for (int j = 0; j < n; j++) {
            if (!posetil[j] && cost[current][j] < minCost) {
                minCost = cost[current][j];
                nextCity = j;
            }
        }

        tekushPut[step] = nextCity;
        posetil[nextCity] = true;
        totalCost += minCost;
        current = nextCity;
    }

    totalCost += cost[current][startCity];

    cout << "\n Стоимость маршрута: " << totalCost << "\n";
    cout << " Маршрут: ";
    for (int i = 0; i < n; i++) cout << tekushPut[i] << " ";
    cout << startCity << "\n";
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

    int method;
    cout << "Выберите метод:\n1 -  полный перебор\n2 - эвристика \n";
    cin >> method;

    auto timeStart = chrono::high_resolution_clock::now();

    if (method == 1) {
        int max = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (cost[i][j] > max) max = cost[i][j];
        bestCost = max * n;


    for (int i = 0; i < n; i++) posetil[i] = false;      // все города считаем непосещенными
    posetil[startCity] = true;                        
    tekushPut[0] = startCity;

    Perebor(1, startCity, 0);

    cout << "\nМинимальная стоимость: " << bestCost << "\n";
    cout << "Маршрут: ";
    for (int i = 0; i < n; i++) cout << bestPut[i] << " ";
    cout << startCity << "\n";
    }
    else if (method == 2) {
       Everystic();
    }
     else {
     cout << "Неверный выбор!\n";
     return 0;
    }
    auto timeEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = timeEnd - timeStart;
    cout << "Время выполнения: " << duration.count() << " сек.\n";

    return 0;
}
