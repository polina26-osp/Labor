#pragma once

#include <vector>
#include <iostream>

class BinaryTree
{
public:

    class TreeNode;

    // Конструктор по умолчанию
    BinaryTree() = default;

    // Конструктор копирования
    BinaryTree(const BinaryTree& other);

    // Деструктор
    ~BinaryTree();

    // Получение корня дерева
    TreeNode* getRoot() const;

    // Очистка дерева (удаление всех узлов)
    void clear();

    // Проверка, пусто ли дерево
    bool isEmpty() const;

    // Получение высоты дерева
    int getHeight() const;

    // Получение количества узлов дерева
    size_t getNodeCount() const;

    // Получение минимального ключа дерева
    int getMiminalKey() const;

    // Получение максимального ключа дерева
    int getMaxKey() const;

    // Добавление узла в дерево (методом случайного выбора поддерева)
    TreeNode* addNode(const int key);

    // Удаление узла из дерева по ключу (возвращает true, если узел был удалён)
    bool removeNode(const int key);

    // Поиск узла дерева по ключу
    TreeNode* findNode(const int key) const;

    // получение вектора (std::vector<int>), содержащего все ключи дерева по возрастанию 
    std::vector<int> getKeysAscending() const;

    // Вывод в консоль дерева в горизонтальном виде  (самый правый потомок находится на первой строке, самый левый - на нижней)
    void printHorizontal() const;

    // Получение всех узлов дерева
    std::vector<TreeNode*> getAllNodes() const;

    // Вывод дерева в консоль (обход в ширину)
    void printToConsole() const;

    // Оператор присваивания
    BinaryTree& operator=(const BinaryTree& other);

private:

    TreeNode* root_ = nullptr;

    // Рекурсивное получение всех узлов
    void getAllNodesInternal(std::vector<TreeNode*>&, TreeNode*) const;

    // Рекурсивный поиск минимального ключа
    int getMiminalKeyInternal(TreeNode*) const;

    // Рекурсивный поиск максимального ключа
    int getMaxKeyInternal(TreeNode*) const;

    // Рекурсивное удаление узла и всех его потомков
    void destroyNode(TreeNode*);

    // Рекурсивный горизонтальный вывод
    void printHorizontalInternal(TreeNode*, int marginLeft, int levelSpacing) const;

    // Рекурсивное копирование узла и всех его потомков
    TreeNode* copyNode(TreeNode* node);

    // Рекурсивный подсчёт количества узлов
    size_t getNodeCountInternal(TreeNode*) const;

    // Рекурсивное получение высоты дерева
    int getHeightInternal(TreeNode*) const;

    // Рекурсивное удаление узла по ключу
    bool removeNodeInternal(TreeNode*& node, const int key);

    // Поиск минимального узла в поддереве
    TreeNode* findMinNode(TreeNode* node) const;

    // Рекурсивное получение ключей по возрастанию
    void getKeysAscendingInternal(std::vector<int>&, TreeNode*) const;
};

class BinaryTree::TreeNode
{
public:

    // Конструктор по умолчанию
    TreeNode();

    // Конструктор с параметрами
    TreeNode(const int key, TreeNode* leftChild = nullptr, TreeNode* rightChild = nullptr);

    ~TreeNode() = default;

    // Получение ключа узла
    int getKey() const;

    // Изменение ключа узла
    void setKey(const int);

    // Получение левого потомка
    TreeNode* getLeftChild() const;

    // Изменение левого потомка
    void setLeftChild(TreeNode* const);

    // Получение правого потомка
    TreeNode* getRightChild() const;

    // Изменение правого потомка
    void setRightChild(TreeNode* const);

    // Получение степени узла (количество потомков)
    int getNodeDegree() const;

    // Проверка, является ли узел листом
    bool isLeafNode() const;

private:

    int key_;
    TreeNode* leftChild_, * rightChild_;
};

// Перегрузка оператора вывода для узла
std::ostream& operator<<(std::ostream&, BinaryTree::TreeNode&);