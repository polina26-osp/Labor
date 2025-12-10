#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "booleanmatrix.h"

using namespace std;

// Структура для хранения дуги графа
struct Edge {
    int from;
    int to;
};

// Функция для чтения дуг из файла
BooleanMatrix readEdgesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        exit(1);
    }

    vector<Edge> edges;
    int maxVertex = 0;
    int from, to;

    while (file >> from >> to) {
        if (from == 0 && to == 0) break;
        if (from < 1 || to < 1) {
            cout << "Ошибка: номера вершин не положительны" << endl;
            exit(1);
        }
        edges.push_back(Edge{ from, to });
        // Максимальный номер вершины (для размера матрицы)
        if (from > maxVertex) maxVertex = from;
        if (to > maxVertex) maxVertex = to;
    }

    file.close();

    if (edges.empty()) {
        cout << "Ошибка: файл не содержит дуг" << endl;
        exit(1);
    }

    // Создание матрицы смежности
    BooleanMatrix matrix(maxVertex, maxVertex, false);

    for (const Edge& edge : edges) {
        matrix[edge.from - 1].setBit(edge.to - 1, true);
    }

    cout << "Прочитано " << edges.size() << " дуг, граф имеет " << maxVertex << " вершин" << endl;

    // Список дуг
    cout << "Список дуг: ";
    for (size_t i = 0; i < edges.size(); i++) {
        if (i > 0) cout << ", ";
        cout << "(" << edges[i].from << "," << edges[i].to << ")";
    }
    cout << endl;

    return matrix;
}

// Функция для вывода матрицы
void printMatrix(const BooleanMatrix& matrix) {
    int n = matrix.numRows();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (matrix[i][j] == true ? "1 " : "0 ");
        }
        cout << "\n";
    }
}

// Топологическая сортировка 
vector<int> topologicalSort(const BooleanMatrix& matrix) {
    int n = matrix.numRows();

    vector<bool> v0(n, false); // обработанные вершины
    vector<int> result;

    int step = 1;

    while (result.size() < n) {
        cout << "\nШаг " << step << "\n";

        // v1 - дизъюнкция строк необработанных вершин
        vector<bool> v1(n, false);

        // дизъюнкция строк
        for (int i = 0; i < n; i++) {
            if (!v0[i]) { // если вершина i не обработана
                for (int j = 0; j < n; j++) {
                    v1[j] = v1[j] || (matrix[i][j] == true);
                }
            }
        }

        // Текущие векторы
        cout << "v0 (обработанные):";
        for (int i = 0; i < n; i++) {
            cout << (v0[i] ? "1" : "0");
        }
        cout << "\n";

        cout << "v1 (дизъюнкция строк):";
        for (int i = 0; i < n; i++) {
            cout << (v1[i] ? "1" : "0");
        }
        cout << "\n";

        cout << "~v1 (вершины без входящих дуг):";
        for (int i = 0; i < n; i++) {
            cout << (!v1[i] ? "1" : "0");
        }
        cout << "\n";

        // v2 = ~v1 & ~v0
        vector<int> candidates;
        for (int i = 0; i < n; i++) {
            if (!v1[i] && !v0[i]) {
                candidates.push_back(i);
            }
        }

        if (candidates.empty()) {
            cout << "\nОшибка: граф содержит цикл!" << endl;
            return vector<int>();
        }

        cout << "v2 (новые кандидаты):";
        for (int i = 0; i < n; i++) {
            bool isCandidate = false;
            for (int cand : candidates) {
                if (cand == i) isCandidate = true;
            }
            cout << (isCandidate ? "1" : "0");
        }
        cout << "\n";

        // Добавление кандидатов в результат
        cout << "Добавляем вершины:";
        for (int vertex : candidates) {
            cout << (vertex + 1) << " ";
            result.push_back(vertex + 1);
            v0[vertex] = true;  // Помечаем вершну как обработанную 
        }
        cout << "\n";

        cout << "Текущий результат:";
        for (int v : result) {
            cout << v << " ";
        }
        cout << "\n";

        step++;
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    cout << "1. Загрузить дуги из файла или 2. Ввести граф вручную: \n";
    cin >> choice;

    BooleanMatrix matrix(1, 1, false);

    if (choice == 1) {
        // Загрузка из файла
        matrix = readEdgesFromFile("graph1.txt");
        cout << "\nМатрица смежности графа:\n";
        printMatrix(matrix);
    }
    else if (choice == 2) {
        // Ручной ввод дуг
        vector<Edge> edges;
        int maxVertex = 0;

        cout << "\nВведите дуги в формате 'из_ в_', для завершения '0 0\n";

        int from, to;
        while (true) {
            cin >> from >> to;
            if (from == 0 && to == 0) break;

            if (from < 1 || to < 1) {
                cout << "Ошибка: номера вершин не положительные\n";
                continue;
            }

            edges.push_back(Edge{ from, to });
            if (from > maxVertex) maxVertex = from;
            if (to > maxVertex) maxVertex = to;
        }

        if (edges.empty()) {
            cout << "Ошибка: не введены дуги\n";
            return 1;
        }

        // Создаём матрицу смежности
        matrix = BooleanMatrix(maxVertex, maxVertex, false);
        for (const auto& edge : edges) {
            matrix[edge.from - 1].setBit(edge.to - 1, true);
        }

        cout << "\nВведено " << edges.size() << " дуг, " << maxVertex << " вершин" << endl;
        cout << "Список дуг: ";
        for (size_t i = 0; i < edges.size(); i++) {
            if (i > 0) cout << ", ";
            cout << "(" << edges[i].from << "," << edges[i].to << ")";
        }
        cout << "\n\nМатрица смежности:\n";
        printMatrix(matrix);
    }
    else {
        cout << "Неверный выбор\n";
        return 1;
    }

    // Выполняем топологическую сортировку
    vector<int> result = topologicalSort(matrix);

    if (!result.empty()) {
        cout << "Топологический сортировка выполнена: ";
        for (int v : result) {
            cout << v << " ";
        }
        cout << "\n";
    }
    else {
        cout << "\nСортировка не выполнена (граф содержит циклы)\n";
    }

    return 0;
}