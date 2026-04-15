#include <limits>
#include "binarysearchtree.h"

// Деструктор
BinarySearchTree::~BinarySearchTree()
{
    clear();
}

// Добавление узла в дерево 
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

// Удаление узла из дерева по ключу 
bool BinarySearchTree::removeNode(const int key)
{
    return removeNodeInternal(root_, key);
}

// Поиск узла дерева по ключу 
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

// Получение минимального ключа (самый левый узел) 
int BinarySearchTree::getMinimalKey() const
{
    if (!root_)
    {
        return std::numeric_limits<int>::max();
    }

    TreeNode* currentNode = root_;
    while (currentNode->getLeftChild())
    {
        currentNode = currentNode->getLeftChild();
    }
    return currentNode->getKey();
}

// Получение максимального ключа (самый правый узел)
int BinarySearchTree::getMaxKey() const
{
    if (!root_)
    {
        return std::numeric_limits<int>::min();
    }

    TreeNode* currentNode = root_;
    while (currentNode->getRightChild())
    {
        currentNode = currentNode->getRightChild();
    }
    return currentNode->getKey();
}

// Получение всех ключей по возрастанию (рекурсивный обход ЛКП)
std::vector<int> BinarySearchTree::getKeysAscending() const
{
    std::vector<int> keys;
    getKeysAscendingInternal(root_, keys);
    return keys;
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

        // У узла нет детей
        if (!node->getLeftChild() && !node->getRightChild())
        {
            node = nullptr;
        }
        // У узла есть только правый потомок
        else if (!node->getLeftChild())
        {
            node = node->getRightChild();
        }
        // У узла есть только левый потомок
        else if (!node->getRightChild())
        {
            node = node->getLeftChild();
        }
        // У узла есть два потомка
        else
        {
            TreeNode* minNode = findMinNode(node->getRightChild());
            node->setKey(minNode->getKey());
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

// Рекурсивный обход ЛКП для получения отсортированных ключей
void BinarySearchTree::getKeysAscendingInternal(TreeNode* node, std::vector<int>& keys) const
{
    if (!node) return;

    getKeysAscendingInternal(node->getLeftChild(), keys);
    keys.push_back(node->getKey());
    getKeysAscendingInternal(node->getRightChild(), keys);
}

