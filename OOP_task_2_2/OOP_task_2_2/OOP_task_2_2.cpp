#include <iostream>
#include <string>
#include "dynamicarray.h"
#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int n, m, s;

    // Ввод первого массива
    cout << "Введите количество элементов для первого массива (int): ";
    cin >> n;
    DynamicArray<int> arr1(n);
    cout << "Введите элементы через пробел:\n";
    
    int count = 0;
    
    for (int i = 0; i < n && cin; i++)
    {
        if (!(cin >> arr1[i]))
        {
            cout << "Ошибка: введено не число\n";
            return 1;
        }
        count++;
    }
    
    // Ввод второго массива
    cout << "\nВведите количество элементов для второго массива (int): ";
    cin >> m;
    DynamicArray<int> arr2(m);
    cout << "Введите элементы через пробел:\n";

    count = 0;
    for (int i = 0; i < m && cin; i++)
    {
        if (!(cin >> arr2[i]))
        {
            cout << "Ошибка: введено не число\n";
            return 1;
        }
        count++;
    }

    // Ввод третьего массива
    cout << "\nВведите количество элементов для третьего массива (unsigned int): ";
    cin >> s;
    DynamicArray<unsigned int> arr4(s);
    cout << "Введите элементы через пробел:\n";

    count = 0;
    for (int i = 0; i < s && cin; i++)
    {
        if (!(cin >> arr4[i]))
        {
            cout << "Ошибка: введено не число\n";
            return 1;
        }
        count++;
    }

    // Вывод массивов
    cout << "\nПервый массив: [ ";
    for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
    cout << "]\n";

    cout << "Второй массив: [ ";
    for (int i = 0; i < arr2.getLength(); i++) cout << arr2[i] << (i < arr2.getLength() - 1 ? ", " : " ");
    cout << "]\n";

    cout << "Третий массив: [ ";
    for (int i = 0; i < arr4.getLength(); i++) cout << arr4[i] << (i < arr4.getLength() - 1 ? ", " : " ");
    cout << "]\n";

    // Вставка
    int index, value;
    cout << "\nВведите индекс и значение для вставки в первый массив: ";
    cin >> index >> value;
    if (arr1.insertAt(index, value))
    {
        cout << "После вставки: [ ";
        for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
        cout << "]\n";
    }
    else cout << "Неверный индекс!\n";

    // Удаление по индексу
    cout << "\nВведите индекс для удаления из первого массива: ";
    cin >> index;
    if (arr1.removeAt(index))
    {
        cout << "После удаления: [ ";
        for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
        cout << "]\n";
    }
    else cout << "Неверный индекс!\n";

    // Удаление по значению (первое вхождение)
    cout << "\nВведите значение для удаления (первое вхождение) из первого массива: ";
    cin >> value;
    if (arr1.removeValue(value))
    {
        cout << "После удаления: [ ";
        for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
        cout << "]\n";
    }
    else cout << "Элемент не найден!\n";

    // Удаление всех вхождений
    cout << "\nВведите значение для удаления всех вхождений из первого массива: ";
    cin >> value;
    arr1.removeAll(value);
    cout << "После удаления всех: [ ";
    for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
    cout << "]\n";

    // Сортировка и поиск min/max
    arr1.sort();
    cout << "\nПосле сортировки: [ ";
    for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
    cout << "]\n";
    cout << "Максимум: " << arr1.getMax() << ", Минимум: " << arr1.getMin() << "\n";

    // Конкатенация массивов
    DynamicArray<int> arr3 = arr1 + arr2;
    cout << "\nРезультат arr1 + arr2: [ ";
    for (int i = 0; i < arr3.getLength(); i++) cout << arr3[i] << (i < arr3.getLength() - 1 ? ", " : " ");
    cout << "]\n";

    arr1 += arr2;
    cout << "После arr1 += arr2: [ ";
    for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
    cout << "]\n";

    // Сравнение массивов
    cout << "\nСравнение arr1 и arr3:\n";
    cout << "arr1 == arr3? " << (arr1 == arr3 ? "Да" : "Нет") << "\n";
    cout << "arr1 != arr2? " << (arr1 != arr2 ? "Да" : "Нет") << "\n";

    // Изменение элемента
    cout << "\nВведите индекс и новое значение для изменения элемента первого массива: ";
    cin >> index >> value;
    if (index >= 0 && index < arr1.getLength())
    {
        arr1[index] = value;
        cout << "После изменения: [ ";
        for (int i = 0; i < arr1.getLength(); i++) cout << arr1[i] << (i < arr1.getLength() - 1 ? ", " : " ");
        cout << "]\n";
    }
    else cout << "Неверный индекс!\n";

    return 0;
}

