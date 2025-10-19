#include <iostream>
#include "dynamicarray.h"
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    DynamicArray arr1, arr2;

    int n, val, idx;

    cout << "Введите количество элементов для первого массива: ";
    cin >> n;
    cout << "Введите элементы через пробел:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> val;
        arr1.add(val);
    }

    cout << "Введите количество элементов для второго массива: ";
    cin >> n;
    cout << "Введите элементы через пробел:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> val;
        arr2.add(val);
    }

    cout << "\nПервый массив: " << arr1 << endl;
    cout << "Второй массив: " << arr2 << endl;

    // Вставка элемента
    cout << "\nВведите индекс и значение для вставки в первый массив: ";
    cin >> idx >> val;
    if (arr1.insertAt(idx, val))
        cout << "После вставки: " << arr1 << endl;
    else
        cout << "Неверный индекс!\n";

    // Удаление элемента по индексу
    cout << "\nВведите индекс для удаления из первого массива: ";
    cin >> idx;
    if (arr1.removeAt(idx))
        cout << "После удаления: " << arr1 << endl;
    else
        cout << "Неверный индекс!\n";

    // Удаление первого вхождения
    cout << "\nВведите значение для удаления (первое вхождение) из первого массива: ";
    cin >> val;
    if (arr1.removeValue(val))
        cout << "После удаления: " << arr1 << endl;
    else
        cout << "Элемент не найден!\n";

    // Удаление всех вхождений
    cout << "\nВведите значение для удаления всех вхождений из первого массива: ";
    cin >> val;
    arr1.removeAll(val);
    cout << "После удаления всех: " << arr1 << endl;

    // Сортировка
    arr1.sort();
    cout << "\nПосле сортировки: " << arr1 << endl;

    // Максимум и минимум
    if (arr1.getLength() > 0)
        cout << "Максимум: " << arr1.getMax() << ", Минимум: " << arr1.getMin() << endl;

    // Конкатенация массивов
    DynamicArray arr3 = arr1 + arr2;
    cout << "\nРезультат arr1 + arr2: " << arr3 << endl;

    arr1 += arr2;
    cout << "После arr1 += arr2: " << arr1 << endl;

    // Сравнение
    cout << "\nСравнение:\n";
    cout << "arr1 == arr3? " << (arr1 == arr3 ? "Да" : "Нет") << endl;
    cout << "arr1 == arr2? " << (arr1 == arr2 ? "Да" : "Нет") << endl;

    // Изменение элемента через []
    cout << "\nВведите индекс и новое значение для изменения элемента первого массива: ";
    cin >> idx >> val;
    if (idx >= 0 && idx < arr1.getLength())
    {
        arr1[idx] = val;
        cout << "После изменения: " << arr1 << endl;
    }
    else
    {
        cout << "Неверный индекс!\n";
    }

    return 0;
}



