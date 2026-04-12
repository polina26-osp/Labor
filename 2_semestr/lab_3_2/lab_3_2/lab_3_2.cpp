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

    cout << "2. Добавление узлов " << endl;
    vector<int> addedKeys;
    for (int i = 0; i < 15; i++)
    {
        int key = rand() % 100;
        tree1.addNode(key);
        addedKeys.push_back(key);
        cout << " Добавлен ключ: " << key << endl;
    }
    cout << endl;

    cout << "3. Получение минимального ключа (самый левый узел): " << tree1.getMinimalKey() << endl << endl;

    cout << "4. Получение максимального ключа (самый правый узел): " << tree1.getMaxKey() << endl << endl;

    cout << "5. Получение всех ключей по возрастанию (обход ЛКП): ";
    vector<int> keys = tree1.getKeysAscending();
    for (int k : keys)
    {
        cout << k << " ";
    }
    cout << endl << endl;

    cout << "6. Поиск узла " << endl;
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

    cout << "7. Удаление узла " << endl;
    int removeKey = addedKeys[10];
    cout << " Удаление узла " << removeKey << endl;
    bool removed = tree1.removeNode(removeKey);
    if (removed)
    {
        cout << " Узел удалён" << endl;
    }
    cout << " Узлов после удаления: " << tree1.getNodeCount() << endl << endl;

    cout << "8. Конструктор копирования " << endl;
    BinarySearchTree tree2(tree1);
    cout << " Узлов в копии: " << tree2.getNodeCount() << endl << endl;

    cout << "9. Оператор присваивания " << endl;
    BinarySearchTree tree3;
    tree3 = tree1;
    cout << " Узлов: " << tree3.getNodeCount() << endl << endl;

    cout << "10. Очистка дерева" << endl;
    tree1.clear();
    cout << " isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << endl;

    return 0;
}