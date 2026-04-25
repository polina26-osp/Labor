#include <iostream>
#include <vector>
#include "binarysearchtree.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    vector<int> keys = { 10, 20, 30, 40 };
    vector<unsigned int> keysFreq = { 10, 1, 1, 10 };
    vector<unsigned int> trapFreq = { 5, 2, 1, 1, 2 };

    cout << "входные данные:\n";
    cout << "ключи (d): ";
    for (int k : keys) cout << k << " ";
    cout << "\nчастоты успеха (p): ";
    for (unsigned int f : keysFreq) cout << f << " ";
    cout << "\nчастоты ловушек (q): ";
    for (unsigned int f : trapFreq) cout << f << " ";
    cout << "\n\n";

    // Построение оптимального дерева 
    cout << "построение оптимального дерева:\n";
    BinarySearchTree optimalTree = BinarySearchTree::createOptimalSearchTree(keys, keysFreq, trapFreq);

    cout << "\nрезультат:\n";
    cout << "узлов в дереве: " << optimalTree.getNodeCount() << endl;
    cout << "высота дерева: " << optimalTree.getHeight() << endl;
    cout << "ключи по возрастанию: ";
    vector<int> ascKeys = optimalTree.getKeysAscending();
    for (int k : ascKeys) cout << k << " ";
    cout << endl;

    // 1. Конструктор по умолчанию
    cout << "Конструктор по умолчанию:\n";
    BinarySearchTree tree1;
    cout << "дерево создано, узлов: " << tree1.getNodeCount() << endl << endl;

    // Добавление узлов в tree1
    tree1.addNode(50);
    tree1.addNode(30);
    tree1.addNode(70);
    tree1.addNode(20);
    tree1.addNode(40);
    cout << "В tree1 добавлены узлы 50, 30, 70, 20, 40\n";
    cout << "узлов в tree1: " << tree1.getNodeCount() << endl;
    cout << "ключи tree1 (по возрастанию): ";
    vector<int> keys1 = tree1.getKeysAscending();
    for (int k : keys1) cout << k << " ";
    cout << endl << endl;

    // 2. Конструктор копирования
    cout << "Конструктор копирования (tree2 = tree1):\n";
    BinarySearchTree tree2(tree1);
    cout << "узлов в tree2: " << tree2.getNodeCount() << endl;
    cout << "ключи tree2: ";
    vector<int> keys2 = tree2.getKeysAscending();
    for (int k : keys2) cout << k << " ";
    cout << endl << endl;

    // 3. Конструктор перемещения
    cout << "Конструктор перемещения (tree3 = move(tree1)):\n";
    BinarySearchTree tree3(std::move(tree1));
    cout << "узлов в tree3: " << tree3.getNodeCount() << endl;
    cout << "ключи tree3: ";
    vector<int> keys3 = tree3.getKeysAscending();
    for (int k : keys3) cout << k << " ";
    cout << endl;
    cout << "tree1 после перемещения, узлов: " << tree1.getNodeCount() << endl << endl;

    // 4. Оператор присваивания 
    cout << "Оператор присваивания (tree4 = tree2):\n";
    BinarySearchTree tree4;
    tree4 = tree2;
    cout << "узлов в tree4: " << tree4.getNodeCount() << endl;
    cout << "ключи tree4: ";
    vector<int> keys4 = tree4.getKeysAscending();
    for (int k : keys4) cout << k << " ";
    cout << endl << endl;

    // 5. Оператор перемещения
    cout << "Оператор перемещения (tree5 = move(tree2)):\n";
    BinarySearchTree tree5;
    tree5 = std::move(tree2);
    cout << "узлов в tree5: " << tree5.getNodeCount() << endl;
    cout << "ключи tree5: ";
    vector<int> keys5 = tree5.getKeysAscending();
    for (int k : keys5) cout << k << " ";
    cout << endl;
    cout << "tree2 после перемещения, узлов: " << tree2.getNodeCount() << endl << endl;

    return 0;
}
