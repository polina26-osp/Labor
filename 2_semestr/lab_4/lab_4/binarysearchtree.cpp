#include <limits>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "binarysearchtree.h"

using namespace std;

// Конструктор копирования
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
    : BinaryTree(other)
{
}

// Конструктор перемещения
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
    : BinaryTree(std::move(other))
{
    other.root_ = nullptr;
}

// Деструктор
BinarySearchTree::~BinarySearchTree()
{
    clear();
}

// Оператор присваивания
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
    if (this != &other)
    {
        BinaryTree::operator=(other);
    }
    return *this;
}

// Оператор перемещения
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept
{
    if (this != &other)
    {
        clear();
        BinaryTree::operator=(std::move(other));
        other.root_ = nullptr;
    }
    return *this;
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
        return numeric_limits<int>::max();
    }

    TreeNode* minNode = findMinNode(root_);
    return minNode->getKey();
}

// Получение максимального ключа (самый правый узел)
int BinarySearchTree::getMaxKey() const
{
    if (!root_)
    {
        return numeric_limits<int>::min();
    }

    TreeNode* currentNode = root_;
    while (currentNode->getRightChild())
    {
        currentNode = currentNode->getRightChild();
    }
    return currentNode->getKey();
}

// Получение всех ключей по возрастанию (рекурсивный обход ЛКП)
vector<int> BinarySearchTree::getKeysAscending() const
{
    vector<int> keys;
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

// Рекурсивный обход лкп для получения отсортированных ключей
void BinarySearchTree::getKeysAscendingInternal(TreeNode* node, vector<int>& keys) const
{
    if (!node) return;

    getKeysAscendingInternal(node->getLeftChild(), keys);
    keys.push_back(node->getKey());
    getKeysAscendingInternal(node->getRightChild(), keys);
}

using MatrixRow = vector<unsigned int>;
using Matrix = vector<MatrixRow>;

static Matrix createMatrix(size_t size)
{
    return Matrix(size, MatrixRow(size, 0));
}

static void printMatrix(ostream& outputStream, const Matrix& matrix, const string& preamble)
{
    outputStream << preamble << endl;

    for (auto& matrixRow : matrix)
    {
        for (auto& matrixElement : matrixRow)
        {
            outputStream << matrixElement << " ";
        }
        outputStream << endl;
    }
}

// Построение оптимального дерева поиска (статический метод)
BinarySearchTree BinarySearchTree::createOptimalSearchTree(
    const vector<int>& keys,
    const vector<unsigned int>& keysFreq,
    const vector<unsigned int>& trapFreq)
{
    assert(is_sorted(keys.begin(), keys.end()) && "Массив ключей не отсортирован ");
    assert(keys.size() > 0 && "Массив ключей не должен быть пустым ");
    assert(keys.size() == keysFreq.size() && "Массив частот ключей должен иметь тот же размер, что и массив ключей ");
    assert(keys.size() + 1 == trapFreq.size() && "Массив частот ловушек должен иметь размер, равный размеру массива ключей +1 ");

    cout << "d: ";
    for (auto& key : keys) cout << key << " ";
    cout << endl;

    cout << "p: ";
    for (auto& keyFreq : keysFreq) cout << keyFreq << " ";
    cout << endl;

    cout << "q: ";
    for (auto& trapFreqValue : trapFreq) cout << trapFreqValue << " ";
    cout << endl << endl;

    size_t n = keys.size();
    size_t matrixSize = n + 1;

    Matrix weightMatrix = createMatrix(matrixSize);
    Matrix costMatrix = createMatrix(matrixSize);
    Matrix rootIndicesMatrix = createMatrix(matrixSize);

    printMatrix(cout, weightMatrix, "W: ");
    printMatrix(cout, costMatrix, "C: ");
    printMatrix(cout, rootIndicesMatrix, "R: ");

    // Инициализация для деревьев с 0 вершин 
    for (size_t i = 0; i < matrixSize; i++)
    {
        weightMatrix[i][i] = trapFreq[i];
        costMatrix[i][i] = trapFreq[i];
    }

    printMatrix(cout, weightMatrix, "W: ");
    printMatrix(cout, costMatrix, "C: ");
    printMatrix(cout, rootIndicesMatrix, "R: ");

    // Для деревьев с 1 вершиной
    for (size_t i = 0; i < matrixSize - 1; i++)
    {
        weightMatrix[i][i + 1] = weightMatrix[i][i] + keysFreq[i] + trapFreq[i + 1];
        costMatrix[i][i + 1] = weightMatrix[i][i + 1] + costMatrix[i][i] + costMatrix[i + 1][i + 1];
        rootIndicesMatrix[i][i + 1] = static_cast<unsigned int>(i + 1);
    }

    printMatrix(cout, weightMatrix, "W: ");
    printMatrix(cout, costMatrix, "C: ");
    printMatrix(cout, rootIndicesMatrix, "R: ");

    // Для деревьев с h вершинами 
    for (size_t h = 2; h <= n; h++)
    {
        for (size_t i = 0; i <= n - h; i++)
        {
            size_t j = i + h;

            weightMatrix[i][j] = weightMatrix[i][j - 1] + keysFreq[j - 1] + trapFreq[j];

            unsigned int minCost = UINT_MAX;
            unsigned int bestK = i + 1;

            for (size_t k = i + 1; k <= j; k++)
            {
                unsigned int currentCost = costMatrix[i][k - 1] + costMatrix[k][j];

                if (currentCost < minCost)
                {
                    minCost = currentCost;
                    bestK = static_cast<unsigned int>(k);
                }
            }

            costMatrix[i][j] = weightMatrix[i][j] + minCost;
            rootIndicesMatrix[i][j] = bestK;
        }
    }

    printMatrix(cout, weightMatrix, "W: ");
    printMatrix(cout, costMatrix, "C: ");
    printMatrix(cout, rootIndicesMatrix, "R: ");

    // Построение дерева по таблице r
    BinarySearchTree optimalTree;
    optimalTree.root_ = buildSubtree(keys, rootIndicesMatrix, 0, static_cast<int>(n));
    return optimalTree;
}

// Рекурсивное построение поддерева (вспомогательный метод)
BinaryTree::TreeNode* BinarySearchTree::buildSubtree(
    const vector<int>& keys,
    const vector<vector<unsigned int>>& rootIndicesMatrix,
    int i, int j)
{
    if (i >= j)
    {
        return nullptr;
    }

    if (j - i == 1)
    {
        int keyIndex = static_cast<int>(j) - 1;
        if (keyIndex >= 0 && keyIndex < static_cast<int>(keys.size()))
        {
            return new TreeNode(keys[keyIndex]);
        }
        return nullptr;
    }

    unsigned int rootIdx = rootIndicesMatrix[i][j];

    if (rootIdx <= static_cast<unsigned int>(i) || rootIdx > static_cast<unsigned int>(j))
    {
        return nullptr;
    }

    int keyIndex = static_cast<int>(rootIdx) - 1;

    if (keyIndex < 0 || keyIndex >= static_cast<int>(keys.size()))
    {
        return nullptr;
    }

    TreeNode* node = new TreeNode(keys[keyIndex]);

    if (static_cast<int>(rootIdx - 1) > i)
    {
        node->setLeftChild(buildSubtree(keys, rootIndicesMatrix, i, static_cast<int>(rootIdx - 1)));
    }

    if (static_cast<int>(rootIdx) < j)
    {
        node->setRightChild(buildSubtree(keys, rootIndicesMatrix, static_cast<int>(rootIdx), j));
    }

    return node;
}
