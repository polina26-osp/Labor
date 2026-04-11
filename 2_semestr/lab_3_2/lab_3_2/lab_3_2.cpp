#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <clocale>
#include "binarysearchtree.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    cout << "1. Конструктор по умолчанию" << endl;
    BinarySearchTree tree1;
    cout << "   isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << endl << endl;

    cout << "2. Добавление узлов (BST алгоритм)" << endl;
    vector<int> addedKeys;
    for (int i = 0; i < 15; i++)
    {
        int key = rand() % 100;
        tree1.addNode(key);
        addedKeys.push_back(key);
        cout << " Добавлен ключ: " << key << endl;
    }
    cout << endl;

    cout << "3. Корень дерева: ";
    if (tree1.getRoot())
    {
        cout << tree1.getRoot()->getKey() << endl << endl;
    }
    else
    {
        cout << "Дерево пустое" << endl << endl;
    }

    cout << "4. Количество узлов: " << tree1.getNodeCount() << endl << endl;

    cout << "5. Высота дерева: " << tree1.getHeight() << endl << endl;

    cout << "6. Минимальный ключ: " << tree1.getMiminalKey() << endl << endl;

    cout << "7. Максимальный ключ: " << tree1.getMaxKey() << endl << endl;

    cout << "8. Ключи по возрастанию: ";
    vector<int> keys = tree1.getKeysAscending();
    for (int k : keys)
    {
        cout << k << " ";
    }
    cout << endl << endl;

    cout << "9. Горизонтальный вывод ДО удаления:" << endl;
    tree1.printHorizontal();
    cout << endl;

    cout << "10. Поиск узла (BST алгоритм)" << endl;
    int searchKey = addedKeys[addedKeys.size() / 2];
    BinaryTree::TreeNode* found = tree1.findNode(searchKey);
    if (found)
    {
        cout << " Узел " << searchKey << " найден" << endl;
    }
    else
    {
        cout << " Узел " << searchKey << " не найден" << endl;
    }
    cout << endl;

    cout << "11. Удаление узла " << addedKeys[10] << " (BST алгоритм)" << endl;
    bool removed = tree1.removeNode(addedKeys[10]);
    if (removed)
    {
        cout << " Узел удалён" << endl;
    }
    cout << " Узлов после удаления: " << tree1.getNodeCount() << endl << endl;

    cout << "12. Горизонтальный вывод ПОСЛЕ удаления:" << endl;
    tree1.printHorizontal();
    cout << endl;

    cout << "13. Конструктор копирования" << endl;
    BinarySearchTree tree2(tree1);
    cout << " Узлов в копии: " << tree2.getNodeCount() << endl << endl;

    cout << "14. Оператор присваивания" << endl;
    BinarySearchTree tree3;
    tree3 = tree1;
    cout << " Узлов: " << tree3.getNodeCount() << endl << endl;

    cout << "15. Очистка дерева" << endl;
    tree1.clear();
    cout << " isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << endl;

    return 0;
}