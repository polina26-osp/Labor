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

// Очистка дерева (удаление всех узлов)
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

// Получение количества узлов дерева
size_t BinaryTree::getNodeCount() const
{
    return getNodeCountInternal(root_);
}

// Добавление узла в дерево (методом случайного выбора поддерева)
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

// Удаление узла из дерева по ключу
bool BinaryTree::removeNode(const int key)
{
    return removeNodeInternal(root_, key);
}

// Поиск узла дерева по ключу
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

// Вывод в консоль дерева в горизонтальном виде
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

// Получение всех узлов дерева
std::vector<BinaryTree::TreeNode*> BinaryTree::getAllNodes() const
{
    std::vector<BinaryTree::TreeNode*> nodesArray;
    if (root_)
    {
        getAllNodesInternal(nodesArray, root_);
    }
    return nodesArray;
}

// Получение минимального ключа в дереве
int BinaryTree::getMiminalKey() const
{
    if (!root_)
    {
        return std::numeric_limits<int>::max();
    }
    return getMinimalKeyInternal(root_);
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
int BinaryTree::getMinimalKeyInternal(TreeNode* treeNode) const
{
    int value = treeNode->getKey();
    if (treeNode->getLeftChild()) value = std::min(value, getMinimalKeyInternal(treeNode->getLeftChild()));
    if (treeNode->getRightChild()) value = std::min(value, getMinimalKeyInternal(treeNode->getRightChild()));
    return value;
}

// Рекурсивное удаление узла и всех его потомков
void BinaryTree::destroyNode(BinaryTree::TreeNode* treeNode)
{
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

// Рекурсивное копирование узла и всех его потомков
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
    if (!node)
    {
        return false;
    }

    if (key < node->getKey())
    {
        TreeNode* left = node->getLeftChild();
        bool result = removeNodeInternal(left, key);
        node->setLeftChild(left);
        return result;
    }
    else if (key > node->getKey())
    {
        TreeNode* right = node->getRightChild();
        bool result = removeNodeInternal(right, key);
        node->setRightChild(right);
        return result;
    }
    else
    {
        TreeNode* nodeToDelete = node;

        // Случай 1: нет потомков (лист)
        if (!node->getLeftChild() && !node->getRightChild())
        {
            node = nullptr;
        }
        // Случай 2: есть только правый потомок
        else if (!node->getLeftChild())
        {
            node = node->getRightChild();
        }
        // Случай 3: есть только левый потомок
        else if (!node->getRightChild())
        {
            node = node->getLeftChild();
        }
        // Случай 4: есть оба потомка
        else
        {
            TreeNode* minRight = findMinNode(node->getRightChild());
            int minKey = minRight->getKey();
            node->setKey(minKey);
            TreeNode* right = node->getRightChild();
            removeNodeInternal(right, minKey);
            node->setRightChild(right);
        }

        delete nodeToDelete;
        return true;
    }
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

// Получение степени узла (количество потомков)
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

// Перегрузка оператора вывода для узла
std::ostream& operator<<(std::ostream& outputStream, BinaryTree::TreeNode& treeNode)
{
    outputStream << treeNode.getKey();
    return outputStream;
}