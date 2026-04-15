#pragma once

#include "binarytree.h"

class BinarySearchTree : public BinaryTree
{
public:

    // Конструктор по умолчанию
    BinarySearchTree() = default;

    // Деструктор
    ~BinarySearchTree() override;

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

private:

    // Поиск минимального узла в поддереве (вспомогательный метод для удаления)
    TreeNode* findMinNode(TreeNode* node) const;

    // Рекурсивное удаление узла по ключу (вспомогательный метод)
    bool removeNodeInternal(TreeNode*& node, const int key);

    // Рекурсивный обход ЛКП для получения отсортированных ключей
    void getKeysAscendingInternal(TreeNode* node, std::vector<int>& keys) const;
};