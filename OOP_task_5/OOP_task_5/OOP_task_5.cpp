#include "linkedlist.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Конструктор по умолчанию:" << endl;
    LinkedList<int> emptyList;
    cout << "Создан пустой список. Размер: " << emptyList.getSize()
        << ", isEmpty: " << (emptyList.isEmpty() ? "true" : "false") << endl << endl;

    cout << "Конструктор из массива:" << endl;
    int arr[] = { 10, 20, 30, 40, 50 };
    LinkedList<int> listFromArray(arr, 5);
    cout << "Список из массива: " << listFromArray << endl << endl;

    cout << "Конструктор копирования:" << endl;
    LinkedList<int> copiedList(listFromArray);
    cout << "Скопированный список: " << copiedList << endl << endl;

    cout << "Получение размера списка:" << endl;
    cout << "Размер списка: " << listFromArray.getSize() << endl << endl;

    cout << "Обмен содержимого (swap):" << endl;
    LinkedList<int> listA;
    listA.addToTail(1);
    listA.addToTail(2);
    listA.addToTail(3);

    LinkedList<int> listB;
    listB.addToTail(10);
    listB.addToTail(20);

    cout << "До swap - listA: " << listA << ", listB: " << listB << endl;
    listA.swap(listB);
    cout << "После swap - listA: " << listA << ", listB: " << listB << endl << endl;

    cout << "Ввод/вывод в консоль:" << endl;
    cout << "Вывод списка listA: " << listA << endl;
    cout << "Вывод списка listB: " << listB << endl << endl;

    cout << "Поиск элемента по ключу:" << endl;
    LinkedList<int> searchList;
    searchList.addToTail(10);
    searchList.addToTail(20);
    searchList.addToTail(30);

    int* found = searchList.find(20);
    if (found) {
        cout << "Найден элемент 20: " << *found << endl;
    }
    else {
        cout << "Элемент 20 не найден" << endl;
    }

    found = searchList.find(7);
    if (found) {
        cout << "Найден элемент 7: " << *found << endl;
    }
    else {
        cout << "Элемент 7 не найден" << endl;
    }
    cout << endl;

    cout << "Добавление элемента в голову:" << endl;
    LinkedList<int> headList;
    headList.addToHead(30);
    headList.addToHead(20);
    headList.addToHead(10);
    cout << "После addToHead(30,20,10): " << headList << endl << endl;

    cout << "Добавление элемента в хвост:" << endl;
    LinkedList<int> tailList;
    tailList.addToTail(1);
    tailList.addToTail(2);
    tailList.addToTail(3);
    cout << "После addToTail(1,2,3): " << tailList << endl << endl;

    cout << " Добавление элемента на позицию:" << endl;
    LinkedList<int> indexList;
    indexList.addToTail(10);
    indexList.addToTail(30);
    indexList.addToTail(40);
    cout << "Исходный список: " << indexList << endl;
    indexList.addAtIndex(1, 20);
    cout << "После addAtIndex(1, 20): " << indexList << endl << endl;

    cout << "Добавление элемента после ключа:" << endl;
    LinkedList<int> afterKeyList;
    afterKeyList.addToTail(1);
    afterKeyList.addToTail(3);
    afterKeyList.addToTail(5);
    cout << "Исходный список: " << afterKeyList << endl;
    afterKeyList.addAfterKey(3, 4);
    cout << "После addAfterKey(3, 4): " << afterKeyList << endl << endl;

    cout << "Удаление элемента из головы:" << endl;
    LinkedList<int> removeHeadList;
    removeHeadList.addToTail(10);
    removeHeadList.addToTail(20);
    removeHeadList.addToTail(30);
    cout << "Исходный список: " << removeHeadList << endl;
    removeHeadList.removeFromHead();
    cout << "После removeFromHead(): " << removeHeadList << endl << endl;

    cout << "Удаление элемента из хвоста:" << endl;
    LinkedList<int> removeTailList;
    removeTailList.addToTail(10);
    removeTailList.addToTail(20);
    removeTailList.addToTail(30);
    cout << "Исходный список: " << removeTailList << endl;
    removeTailList.removeFromTail();
    cout << "После removeFromTail(): " << removeTailList << endl << endl;

    cout << "Удаление элемента из позиции:" << endl;
    LinkedList<int> removeAtIndexList;
    removeAtIndexList.addToTail(10);
    removeAtIndexList.addToTail(20);
    removeAtIndexList.addToTail(30);
    cout << "Исходный список: " << removeAtIndexList << endl;
    removeAtIndexList.removeAtIndex(1);
    cout << "После removeAtIndex(1): " << removeAtIndexList << endl << endl;

    cout << "Удаление элемента по ключу:" << endl;
    LinkedList<int> removeByKeyList;
    removeByKeyList.addToTail(10);
    removeByKeyList.addToTail(20);
    removeByKeyList.addToTail(30);
    cout << "Исходный список: " << removeByKeyList << endl;
    removeByKeyList.removeByKey(200);
    cout << "После removeByKey(200): " << removeByKeyList << endl << endl;

    cout << "Поиск максимального элемента:" << endl;
    LinkedList<int> maxList;
    maxList.addToTail(10);
    maxList.addToTail(90);
    maxList.addToTail(20);
    cout << "Список: " << maxList << endl;
    cout << "Максимальный элемент: " << maxList.getMax() << endl << endl;

    cout << "Поиск минимального элемента:" << endl;
    LinkedList<int> minList;
    minList.addToTail(10);
    minList.addToTail(90);
    minList.addToTail(20);
    cout << "Список: " << minList << endl;
    cout << "Минимальный элемент: " << minList.getMin() << endl << endl;

    cout << "isEmpty():" << endl;
    LinkedList<int> testEmptyList;
    cout << "Пустой список: isEmpty = " << (testEmptyList.isEmpty() ? "true" : "false") << endl;
    testEmptyList.addToTail(1);
    cout << "После добавления элемента: isEmpty = " << (testEmptyList.isEmpty() ? "true" : "false") << endl << endl;

    cout << "Очистка списка:" << endl;
    LinkedList<int> clearList;
    clearList.addToTail(1);
    clearList.addToTail(2);
    clearList.addToTail(3);
    cout << "До clear: " << clearList << ", size = " << clearList.getSize() << endl;
    clearList.clear();
    cout << "После clear: " << clearList << ", size = " << clearList.getSize()
        << ", isEmpty = " << (clearList.isEmpty() ? "true" : "false") << endl << endl;

    cout << "Присваивание (=):" << endl;
    LinkedList<int> assignList1;
    assignList1.addToTail(1);
    assignList1.addToTail(2);
    assignList1.addToTail(3);

    LinkedList<int> assignList2;
    assignList2 = assignList1;
    cout << "assignList1: " << assignList1 << endl;
    cout << "assignList2 (после присваивания): " << assignList2 << endl << endl;

    cout << "Получение ссылки на элемент по индексу ([ ]):" << endl;
    LinkedList<int> indexAccessList;
    indexAccessList.addToTail(10);
    indexAccessList.addToTail(20);
    indexAccessList.addToTail(30);
    cout << "Список: " << indexAccessList << endl;
    cout << "indexAccessList[0] = " << indexAccessList[0] << endl;
    cout << "indexAccessList[1] = " << indexAccessList[1] << endl;
    cout << "indexAccessList[2] = " << indexAccessList[2] << endl << endl;

    cout << "Сравнение (==, !=):" << endl;
    LinkedList<int> compareList1;
    compareList1.addToTail(1);
    compareList1.addToTail(2);
    compareList1.addToTail(3);

    LinkedList<int> compareList2;
    compareList2.addToTail(1);
    compareList2.addToTail(2);
    compareList2.addToTail(3);

    LinkedList<int> compareList3;
    compareList3.addToTail(1);
    compareList3.addToTail(2);

    cout << "compareList1: " << compareList1 << endl;
    cout << "compareList2: " << compareList2 << endl;
    cout << "compareList3: " << compareList3 << endl;
    cout << "compareList1 == compareList2: " << (compareList1 == compareList2 ? "true" : "false") << endl;
    cout << "compareList1 == compareList3: " << (compareList1 == compareList3 ? "true" : "false") << endl;
    cout << "compareList1 != compareList2: " << (compareList1 != compareList2 ? "true" : "false") << endl;
    cout << "compareList1 != compareList3: " << (compareList1 != compareList3 ? "true" : "false") << endl << endl;

    cout << "Сложение (конкатенация) списков (+, +=):" << endl;
    LinkedList<int> concatList1;
    concatList1.addToTail(1);
    concatList1.addToTail(2);
    concatList1.addToTail(3);

    LinkedList<int> concatList2;
    concatList2.addToTail(4);
    concatList2.addToTail(5);
    concatList2.addToTail(6);

    cout << "concatList1: " << concatList1 << endl;
    cout << "concatList2: " << concatList2 << endl;

    LinkedList<int> concatResult = concatList1 + concatList2;
    cout << "concatList1 + concatList2: " << concatResult << endl;

    concatList1 += concatList2;
    cout << "concatList1 += concatList2: " << concatList1 << endl << endl;

    cout << "Введите числа для списка для проверки ввода:" << endl;

    LinkedList<int> userList;
    cin >> userList;

    cout << "Введен список: " << userList << endl;
    cout << "Размер списка: " << userList.getSize() << endl;

    return 0;
}