
#include <stdlib.h>
#include <limits>
#include <iostream>
#include <list>
#include <algorithm>
#include "binarytree.h"

// Конструктор копирования
BinaryTree::BinaryTree(const BinaryTree& other) : root_(nullptr)
{
    if (other.root_)
    {
        root_ = copyNode(other.root_);
    }
}

// Деструктор
BinaryTree::~BinaryTree()
{
    clear();
}

// Оператор присваивания
BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
    if (this != &other)
    {
        clear();
        if (other.root_)
        {
            root_ = copyNode(other.root_);
        }
    }
    return *this;
}

// Получение корня дерева
BinaryTree::TreeNode* BinaryTree::getRoot() const { return root_; }

// Очистка дерева
void BinaryTree::clear()
{
    if (root_)
    {
        destroyNode(root_);
        root_ = nullptr;
    }
}

// Проверка, пусто ли дерево
bool BinaryTree::isEmpty() const
{
    return !root_;
}

// Получение количества узлов
size_t BinaryTree::getNodeCount() const
{
    return getNodeCountInternal(root_);
}

// Получение высоты дерева
int BinaryTree::getHeight() const
{
    return getHeightInternal(root_);
}

// Получение минимального ключа дерева
int BinaryTree::getMiminalKey() const
{
    if (!root_)
    {
        return std::numeric_limits<int>::max();
    }
    return getMiminalKeyInternal(root_);
}

// Получение максимального ключа дерева
int BinaryTree::getMaxKey() const
{
    if (!root_)
    {
        return std::numeric_limits<int>::min();
    }
    return getMaxKeyInternal(root_);
}

// Добавление узла (случайный выбор поддерева)
BinaryTree::TreeNode* BinaryTree::addNode(const int key)
{
    if (!root_)
    {
        root_ = new TreeNode(key);
        return root_;
    }

    TreeNode* currentNode = root_;

    while (true)
    {
        int randomValue = rand() % 2;

        if (randomValue == 0)
        {
            if (!currentNode->getLeftChild())
            {
                currentNode->setLeftChild(new TreeNode(key));
                return currentNode->getLeftChild();
            }
            else
            {
                currentNode = currentNode->getLeftChild();
            }
        }
        else
        {
            if (!currentNode->getRightChild())
            {
                currentNode->setRightChild(new TreeNode(key));
                return currentNode->getRightChild();
            }
            else
            {
                currentNode = currentNode->getRightChild();
            }
        }
    }
}

// Удаление узла по ключу
bool BinaryTree::removeNode(const int key)
{
    return removeNodeInternal(root_, key);
}

// Поиск узла по ключу
BinaryTree::TreeNode* BinaryTree::findNode(const int key) const
{
    if (!root_) return nullptr;

    std::vector<TreeNode*> allNodes = getAllNodes();
    for (TreeNode* node : allNodes)
    {
        if (node->getKey() == key)
            return node;
    }
    return nullptr;
}

// Получение всех ключей по возрастанию
std::vector<int> BinaryTree::getKeysAscending() const
{
    std::vector<int> keys;
    if (root_)
    {
        getAllKeysInternal(keys, root_);
        std::sort(keys.begin(), keys.end());
    }
    return keys;
}

// Горизонтальный вывод
void BinaryTree::printHorizontal() const
{
    if (root_)
    {
        printHorizontalInternal(root_, 0, 4);
    }
    else
    {
        std::cout << "Tree is empty" << std::endl;
    }
}

// Получение всех узлов
std::vector<BinaryTree::TreeNode*> BinaryTree::getAllNodes() const
{
    std::vector<BinaryTree::TreeNode*> nodesArray;
    if (root_)
    {
        getAllNodesInternal(nodesArray, root_);
    }
    return nodesArray;
}

// Вывод дерева в консоль (обход в ширину)
void BinaryTree::printToConsole() const
{
    if (!root_) return;

    std::list<BinaryTree::TreeNode*> unprocessedNodes(1, root_);

    while (!unprocessedNodes.empty())
    {
        BinaryTree::TreeNode* treeNode = unprocessedNodes.front();
        std::cout << treeNode->getKey() << " ";
        if (treeNode->getLeftChild()) unprocessedNodes.push_back(treeNode->getLeftChild());
        if (treeNode->getRightChild()) unprocessedNodes.push_back(treeNode->getRightChild());
        unprocessedNodes.pop_front();
    }
}

// Рекурсивное получение всех узлов
void BinaryTree::getAllNodesInternal(std::vector<TreeNode*>& nodesArray, TreeNode* treeNode) const
{
    if (!treeNode) return;
    nodesArray.push_back(treeNode);
    if (treeNode->getLeftChild()) getAllNodesInternal(nodesArray, treeNode->getLeftChild());
    if (treeNode->getRightChild()) getAllNodesInternal(nodesArray, treeNode->getRightChild());
}

// Рекурсивный поиск минимального ключа
int BinaryTree::getMiminalKeyInternal(TreeNode* treeNode) const
{
    if (!treeNode) return std::numeric_limits<int>::max();

    int value = treeNode->getKey();
    if (treeNode->getLeftChild()) value = std::min(value, getMiminalKeyInternal(treeNode->getLeftChild()));
    if (treeNode->getRightChild()) value = std::min(value, getMiminalKeyInternal(treeNode->getRightChild()));
    return value;
}

// Рекурсивный поиск максимального ключа
int BinaryTree::getMaxKeyInternal(TreeNode* treeNode) const
{
    if (!treeNode) return std::numeric_limits<int>::min();

    int value = treeNode->getKey();
    if (treeNode->getLeftChild()) value = std::max(value, getMaxKeyInternal(treeNode->getLeftChild()));
    if (treeNode->getRightChild()) value = std::max(value, getMaxKeyInternal(treeNode->getRightChild()));
    return value;
}

// Рекурсивное удаление узла и всех его потомков
void BinaryTree::destroyNode(BinaryTree::TreeNode* treeNode)
{
    if (!treeNode) return;
    if (treeNode->getLeftChild()) destroyNode(treeNode->getLeftChild());
    if (treeNode->getRightChild()) destroyNode(treeNode->getRightChild());
    delete treeNode;
}

// Рекурсивный горизонтальный вывод
void BinaryTree::printHorizontalInternal(TreeNode* treeNode, int marginLeft, int levelSpacing) const
{
    if (!treeNode) return;

    printHorizontalInternal(treeNode->getRightChild(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << treeNode->getKey() << std::endl;
    printHorizontalInternal(treeNode->getLeftChild(), marginLeft + levelSpacing, levelSpacing);
}

// Рекурсивное копирование
BinaryTree::TreeNode* BinaryTree::copyNode(TreeNode* node)
{
    if (!node) return nullptr;
    return new TreeNode(node->getKey(),
        copyNode(node->getLeftChild()),
        copyNode(node->getRightChild()));
}

// Рекурсивный подсчёт количества узлов
size_t BinaryTree::getNodeCountInternal(TreeNode* treeNode) const
{
    if (!treeNode) return 0;
    return 1 + getNodeCountInternal(treeNode->getLeftChild()) + getNodeCountInternal(treeNode->getRightChild());
}

// Рекурсивное получение высоты
int BinaryTree::getHeightInternal(TreeNode* treeNode) const
{
    if (!treeNode) return 0;
    return 1 + std::max(getHeightInternal(treeNode->getLeftChild()),
        getHeightInternal(treeNode->getRightChild()));
}

// Поиск минимального узла в поддереве
BinaryTree::TreeNode* BinaryTree::findMinNode(TreeNode* node) const
{
    TreeNode* current = node;
    while (current && current->getLeftChild())
    {
        current = current->getLeftChild();
    }
    return current;
}

// Рекурсивное удаление узла по ключу
bool BinaryTree::removeNodeInternal(TreeNode*& node, const int key)
{
    if (!node) return false;

    if (node->getKey() == key)
    {
        TreeNode* nodeToDelete = node;

        if (!node->getLeftChild() && !node->getRightChild())
        {
            node = nullptr;
        }
        else if (!node->getRightChild())
        {
            node = node->getLeftChild();
        }
        else if (!node->getLeftChild())
        {
            node = node->getRightChild();
        }
        else
        {
            TreeNode* rightmost = node->getLeftChild();
            while (rightmost->getRightChild())
            {
                rightmost = rightmost->getRightChild();
            }
            rightmost->setRightChild(node->getRightChild());
            node = node->getLeftChild();
        }

        delete nodeToDelete;
        return true;
    }

    TreeNode* leftChild = node->getLeftChild();
    if (removeNodeInternal(leftChild, key))
    {
        node->setLeftChild(leftChild);
        return true;
    }

    TreeNode* rightChild = node->getRightChild();
    if (removeNodeInternal(rightChild, key))
    {
        node->setRightChild(rightChild);
        return true;
    }

    return false;
}

// Рекурсивное получение ключей по возрастанию
void BinaryTree::getAllKeysInternal(std::vector<int>& keysArray, TreeNode* treeNode) const
{
    if (!treeNode) return;
    keysArray.push_back(treeNode->getKey());
    if (treeNode->getLeftChild()) getAllKeysInternal(keysArray, treeNode->getLeftChild());
    if (treeNode->getRightChild()) getAllKeysInternal(keysArray, treeNode->getRightChild());
}

// Конструктор по умолчанию узла
BinaryTree::TreeNode::TreeNode() : key_(0), leftChild_(nullptr), rightChild_(nullptr) {}

// Конструктор с параметрами узла
BinaryTree::TreeNode::TreeNode(const int key, TreeNode* leftChild, TreeNode* rightChild) :
    key_(key), leftChild_(leftChild), rightChild_(rightChild) {
}

// Получение ключа узла
int BinaryTree::TreeNode::getKey() const { return key_; }

// Изменение ключа узла
void BinaryTree::TreeNode::setKey(const int key) { key_ = key; }

// Получение левого потомка
BinaryTree::TreeNode* BinaryTree::TreeNode::getLeftChild() const { return leftChild_; }

// Изменение левого потомка
void BinaryTree::TreeNode::setLeftChild(BinaryTree::TreeNode* const leftChild) { leftChild_ = leftChild; }

// Получение правого потомка
BinaryTree::TreeNode* BinaryTree::TreeNode::getRightChild() const { return rightChild_; }

// Изменение правого потомка
void BinaryTree::TreeNode::setRightChild(BinaryTree::TreeNode* const rightChild) { rightChild_ = rightChild; }

// Получение степени узла
int BinaryTree::TreeNode::getNodeDegree() const
{
    int nodeDegree = 0;
    nodeDegree += leftChild_ ? 1 : 0;
    nodeDegree += rightChild_ ? 1 : 0;
    return nodeDegree;
}

// Проверка, является ли узел листом
bool BinaryTree::TreeNode::isLeafNode() const
{
    return !leftChild_ && !rightChild_;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& outputStream, BinaryTree::TreeNode& treeNode)
{
    outputStream << treeNode.getKey();
    return outputStream;
}


