#pragma once

#include "binarytree.h"

class BinarySearchTree : public BinaryTree
{
public:

    // Конструктор по умолчанию
    BinarySearchTree() = default;

    // Конструктор копирования
    BinarySearchTree(const BinarySearchTree& other);

    // Конструктор перемещения
    BinarySearchTree(BinarySearchTree&& other) noexcept;

    // Деструктор
    ~BinarySearchTree() override;

    // Оператор присваивания
    BinarySearchTree& operator=(const BinarySearchTree& other);

    // Оператор перемещения
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    // Добавление узла в дерево 
    virtual TreeNode* addNode(const int key) override;

    // Удаление узла из дерева по ключу 
    virtual bool removeNode(const int key) override;

    // Поиск узла дерева по ключу 
    virtual TreeNode* findNode(const int key) const override;

    // Получение минимального ключа (самый левый узел)
    virtual int getMinimalKey() const override;

    // Получение максимального ключа (самый правый узел) 
    virtual int getMaxKey() const override;

    // Получение всех ключей по возрастанию (рекурсивный обход ЛКП) 
    virtual std::vector<int> getKeysAscending() const override;

    // Построение оптимального дерева поиска (статический метод)
    static BinarySearchTree createOptimalSearchTree(
        const std::vector<int>& keys,
        const std::vector<unsigned int>& keysFreq,
        const std::vector<unsigned int>& trapFreq
    );

    // Копирование поддерева узла (возвращает новый объект класса)
    BinarySearchTree copySubtree(TreeNode* node) const;

    // Добавление узла в дерево (рекурсивный алгоритм)
    virtual TreeNode* addNodeRecursive(const int key);

    // Удаление узла из дерева по ключу (возвращает true, если узел был удалён) (через максимальный узел левого поддерева)
    virtual bool removeNodeAlt(const int key);

private:

    // Поиск минимального узла в поддереве (вспомогательный метод для удаления)
    TreeNode* findMinNode(TreeNode* node) const;

    // Рекурсивное удаление узла по ключу (вспомогательный метод)
    bool removeNodeInternal(TreeNode*& node, const int key);

    // Рекурсивный обход ЛКП для получения отсортированных ключей
    void getKeysAscendingInternal(TreeNode* node, std::vector<int>& keys) const;

    // Рекурсивное построение поддерева по матрице корней (вспомогательный метод)
    static TreeNode* buildSubtree(
        const std::vector<int>& keys,
        const std::vector<std::vector<unsigned int>>& rootIndicesMatrix,
        int i, int j
    );

    // Поиск максимального узла в поддереве (для удаления)
    TreeNode* findMaxNode(TreeNode* node) const;

    // Рекурсивное удаление через максимальный узел левого поддерева
    bool removeNodeAltInternal(TreeNode*& node, const int key);

    // Рекурсивное добавление узла (вспомогательный метод)
    TreeNode* addNodeRecursiveInternal(TreeNode* node, const int key);

    // Вспомогательный метод для копирования поддерева
    TreeNode* copyNodeHelper(TreeNode* node) const;
};