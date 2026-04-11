#include <limits>
#include "binarysearchtree.h"

// Деструктор
BinarySearchTree::~BinarySearchTree()
{
    clear();
}

// Добавление узла в дерево (алгоритм бинарного дерева поиска)
BinaryTree::TreeNode* BinarySearchTree::addNode(const int key)
{
    if (!root_)
    {
        root_ = new TreeNode(key);
        return root_;
    }

    TreeNode* currentNode = root_;

    while (true)
    {
        if (key < currentNode->getKey())
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

// Удаление узла из дерева по ключу (алгоритм бинарного дерева поиска)
bool BinarySearchTree::removeNode(const int key)
{
    return removeNodeInternal(root_, key);
}

// Поиск узла дерева по ключу (алгоритм бинарного дерева поиска)
BinaryTree::TreeNode* BinarySearchTree::findNode(const int key) const
{
    TreeNode* currentNode = root_;

    while (currentNode)
    {
        if (key == currentNode->getKey())
            return currentNode;
        else if (key < currentNode->getKey())
            currentNode = currentNode->getLeftChild();
        else
            currentNode = currentNode->getRightChild();
    }

    return nullptr;
}

// Поиск минимального узла в поддереве (вспомогательный метод для удаления)
BinaryTree::TreeNode* BinarySearchTree::findMinNode(TreeNode* node) const
{
    TreeNode* current = node;
    while (current && current->getLeftChild())
    {
        current = current->getLeftChild();
    }
    return current;
}

// Рекурсивное удаление узла по ключу (вспомогательный метод)
bool BinarySearchTree::removeNodeInternal(TreeNode*& node, const int key)
{
    if (!node) return false;

    if (key < node->getKey())
    {
        TreeNode* leftChild = node->getLeftChild();
        if (removeNodeInternal(leftChild, key))
        {
            node->setLeftChild(leftChild);
            return true;
        }
        return false;
    }
    else if (key > node->getKey())
    {
        TreeNode* rightChild = node->getRightChild();
        if (removeNodeInternal(rightChild, key))
        {
            node->setRightChild(rightChild);
            return true;
        }
        return false;
    }
    else
    {
        // Узел найден
        TreeNode* nodeToDelete = node;

        // Случай 1: у узла нет детей
        if (!node->getLeftChild() && !node->getRightChild())
        {
            node = nullptr;
        }
        // Случай 2: у узла есть только правый ребёнок
        else if (!node->getLeftChild())
        {
            node = node->getRightChild();
        }
        // Случай 3: у узла есть только левый ребёнок
        else if (!node->getRightChild())
        {
            node = node->getLeftChild();
        }
        // Случай 4: у узла есть два ребёнка
        else
        {
            // Находим минимальный узел в правом поддереве
            TreeNode* minNode = findMinNode(node->getRightChild());
            // Копируем его ключ в текущий узел
            node->setKey(minNode->getKey());
            // Удаляем минимальный узел из правого поддерева
            TreeNode* rightChild = node->getRightChild();
            if (removeNodeInternal(rightChild, minNode->getKey()))
            {
                node->setRightChild(rightChild);
            }
            nodeToDelete = nullptr;
        }

        if (nodeToDelete) delete nodeToDelete;
        return true;
    }
}