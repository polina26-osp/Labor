#pragma once

#include <string>
#include <vector>
#include <bitset>
#include "booleanvector.h"

using uint = unsigned int;

const uint NUM_CHARS = 256;

class HuffmanTree
{
public:
    class TreeNode;

    // Конструкторы
    HuffmanTree() = default;
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree(HuffmanTree&& other) noexcept;
    ~HuffmanTree();

    // Операторы присваивания
    HuffmanTree& operator=(const HuffmanTree& other);
    HuffmanTree& operator=(HuffmanTree&& other) noexcept;

    // build: построение дерева на основе текста
    void build(const std::string& text);

    // encode: из строки
    double encode(const std::string& input, std::string& output);

    // encodeFile: из файла (другое имя, чтобы не было конфликта)
    double encodeFile(const std::string& inputFileName, std::string& outputFileName);

    // decode: из строки
    bool decode(const std::string& input, std::string& output);

    // decodeFile: из файла (другое имя, чтобы не было конфликта)
    bool decodeFile(const std::string& inputFileName, std::string& outputFileName);

    // Очистка дерева
    void clear();

private:
    TreeNode* root_ = nullptr;
    BooleanVector codes_[NUM_CHARS];

    // Вспомогательные методы

    // Рекурсивное удаление узлов
    void destroyNode(TreeNode* node);

    // Рекурсивное копирование узлов
    TreeNode* copyNode(TreeNode* node);

    // Рекурсивная генерация кодов Хаффмана
    void generateCodes(TreeNode* node, BooleanVector currentCode);

    // Сбор частот из дерева
    void collectFrequencies(TreeNode* node, uint frequencies[NUM_CHARS]) const;

    // Построение дерева из частот
    void buildFromFrequencies(const std::vector<std::pair<char, uint>>& frequencies);
};

class HuffmanTree::TreeNode
{
public:
    TreeNode();
    TreeNode(uint frequency, char symbol);
    TreeNode(TreeNode* left, TreeNode* right);
    ~TreeNode() = default;

    // Проверка, является ли узел листом 
    bool isLeafNode() const { return leftChild_ == nullptr && rightChild_ == nullptr; }

    // Возвращает символ, который хранится в узле
    char getSymbol() const { return symbol_; }

    // Возвращает частоту встречаемости символа(для листа) или сумму частот потомков(для внутреннего узла)
    uint getFrequency() const { return frequency_; }

    // Возвращает указатель на левого и парвого потомка
    TreeNode* getLeftChild() const { return leftChild_; }
    TreeNode* getRightChild() const { return rightChild_; }

    // Возвращает битовое множество символов, которые есть в поддереве данного узла
    const std::bitset<NUM_CHARS>& getCharacterSet() const { return characterSet_; }

private:
    char symbol_ = '\0';        // символ
    uint frequency_ = 0;        // частота встречаемости
    TreeNode* leftChild_ = nullptr;     // указатель на левого потомка
    TreeNode* rightChild_ = nullptr;    // указатель на правого потомка
    std::bitset<NUM_CHARS> characterSet_;       // множество всех символов в поддереве
};