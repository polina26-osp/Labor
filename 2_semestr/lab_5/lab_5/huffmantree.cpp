#include "huffmantree.h"
#include <fstream>
#include <algorithm>

using namespace std;

// Конструктор узла по умолчанию
HuffmanTree::TreeNode::TreeNode()
    : symbol_('\0'), frequency_(0), leftChild_(nullptr), rightChild_(nullptr)
{
}

// Конструктор узла-листа
HuffmanTree::TreeNode::TreeNode(uint frequency, char symbol)
    : symbol_(symbol), frequency_(frequency), leftChild_(nullptr), rightChild_(nullptr)
{
    characterSet_[static_cast<uint>(symbol)] = true;
}

// Конструктор внутреннего узла
HuffmanTree::TreeNode::TreeNode(TreeNode* left, TreeNode* right)
    : symbol_('\0'), frequency_(left->frequency_ + right->frequency_),
    leftChild_(left), rightChild_(right)
{
    characterSet_ = left->characterSet_ | right->characterSet_;
}

// Конструктор копирования
HuffmanTree::HuffmanTree(const HuffmanTree& other)
    : root_(nullptr)
{
    if (other.root_)
    {
        root_ = copyNode(other.root_);
    }
    for (uint i = 0; i < NUM_CHARS; i++)
    {
        codes_[i] = other.codes_[i];
    }
}

// Конструктор перемещения
HuffmanTree::HuffmanTree(HuffmanTree&& other) noexcept
    : root_(other.root_)
{
    for (uint i = 0; i < NUM_CHARS; i++)
    {
        codes_[i] = move(other.codes_[i]);
    }
    other.root_ = nullptr;
}

// Деструктор
HuffmanTree::~HuffmanTree()
{
    clear();
}

// Оператор присваивания копированием
HuffmanTree& HuffmanTree::operator=(const HuffmanTree& other)
{
    if (this != &other)
    {
        clear();
        if (other.root_)
        {
            root_ = copyNode(other.root_);
        }
        for (uint i = 0; i < NUM_CHARS; i++)
        {
            codes_[i] = other.codes_[i];
        }
    }
    return *this;
}

// Оператор присваивания перемещением
HuffmanTree& HuffmanTree::operator=(HuffmanTree&& other) noexcept
{
    if (this != &other)
    {
        clear();
        root_ = other.root_;
        for (uint i = 0; i < NUM_CHARS; i++)
        {
            codes_[i] = move(other.codes_[i]);
        }
        other.root_ = nullptr;
    }
    return *this;
}

// Очистка дерева
void HuffmanTree::clear()
{
    if (root_)
    {
        destroyNode(root_);
        root_ = nullptr;
    }
    for (uint i = 0; i < NUM_CHARS; i++)
    {
        codes_[i] = BooleanVector();
    }
}

// Рекурсивное удаление узлов
void HuffmanTree::destroyNode(TreeNode* node)
{
    if (!node) return;
    destroyNode(node->getLeftChild());
    destroyNode(node->getRightChild());
    delete node;
}

// Рекурсивное копирование узлов
HuffmanTree::TreeNode* HuffmanTree::copyNode(TreeNode* node)
{
    if (!node) return nullptr;

    if (node->isLeafNode())
    {
        return new TreeNode(node->getFrequency(), node->getSymbol());
    }
    else
    {
        TreeNode* leftCopy = copyNode(node->getLeftChild());
        TreeNode* rightCopy = copyNode(node->getRightChild());
        return new TreeNode(leftCopy, rightCopy);
    }
}

// build: построение дерева на основе текста
void HuffmanTree::build(const string& text)
{
    clear();

    if (text.empty()) return;

    // Подсчёт частот символов
    uint charFrequencies[NUM_CHARS] = { 0 };

    for (char c : text)
    {
        charFrequencies[static_cast<uint>(c)]++;
    }

    // Создание листовых узлов
    vector<TreeNode*> treeNodes;

    for (uint i = 0; i < NUM_CHARS; i++)
    {
        if (charFrequencies[i] > 0)
        {
            TreeNode* leafNode = new TreeNode(charFrequencies[i], static_cast<char>(i));
            treeNodes.push_back(leafNode);
        }
    }

    // Сортировка по частоте
    sort(treeNodes.begin(), treeNodes.end(), [](const TreeNode* a, const TreeNode* b) {
        return a->getFrequency() < b->getFrequency();
        });

    // Построение дерева
    while (treeNodes.size() > 1)
    {
        TreeNode* leftChild = treeNodes[0];
        TreeNode* rightChild = treeNodes[1];

        TreeNode* newNode = new TreeNode(leftChild, rightChild);

        treeNodes.erase(treeNodes.begin());
        treeNodes.erase(treeNodes.begin());

        // Вставка с сохранением сортировки
        auto iterator = treeNodes.begin();
        auto endIterator = treeNodes.end();

        while (iterator != endIterator)
        {
            if ((*iterator)->getFrequency() <= newNode->getFrequency())
            {
                iterator++;
            }
            else
            {
                break;
            }
        }

        treeNodes.insert(iterator, newNode);
    }

    root_ = treeNodes[0];

    // Генерация кодов
    if (root_)
    {
        BooleanVector currentCode;
        generateCodes(root_, currentCode);
    }
}

// Рекурсивная генерация кодов Хаффмана
void HuffmanTree::generateCodes(TreeNode* node, BooleanVector currentCode)
{
    if (!node) return;

    if (node->isLeafNode())
    {
        codes_[static_cast<uint>(node->getSymbol())] = currentCode;
        return;
    }

    // Добавляем 0 для левого поддерева
    BooleanVector leftCode(currentCode.getLength() + 1);
    for (uint i = 0; i < currentCode.getLength(); i++)
    {
        leftCode.setBit(i, currentCode[i]);
    }
    leftCode.setBit(currentCode.getLength(), false);
    generateCodes(node->getLeftChild(), leftCode);

    // Добавляем 1 для правого поддерева
    BooleanVector rightCode(currentCode.getLength() + 1);
    for (uint i = 0; i < currentCode.getLength(); i++)
    {
        rightCode.setBit(i, currentCode[i]);
    }
    rightCode.setBit(currentCode.getLength(), true);
    generateCodes(node->getRightChild(), rightCode);
}

// Сбор частот из дерева
void HuffmanTree::collectFrequencies(TreeNode* node, uint frequencies[NUM_CHARS]) const
{
    if (!node) return;
    if (node->isLeafNode())
    {
        frequencies[static_cast<uint>(node->getSymbol())] = node->getFrequency();
    }
    else
    {
        collectFrequencies(node->getLeftChild(), frequencies);
        collectFrequencies(node->getRightChild(), frequencies);
    }
}

// Построение дерева из частот
void HuffmanTree::buildFromFrequencies(const vector<pair<char, uint>>& frequencies)
{
    if (frequencies.empty()) return;

    vector<TreeNode*> treeNodes;

    for (const auto& pair : frequencies)
    {
        TreeNode* leafNode = new TreeNode(pair.second, pair.first);
        treeNodes.push_back(leafNode);
    }

    sort(treeNodes.begin(), treeNodes.end(), [](const TreeNode* a, const TreeNode* b) {
        return a->getFrequency() < b->getFrequency();
        });

    while (treeNodes.size() > 1)
    {
        TreeNode* leftChild = treeNodes[0];
        TreeNode* rightChild = treeNodes[1];

        TreeNode* newNode = new TreeNode(leftChild, rightChild);

        treeNodes.erase(treeNodes.begin());
        treeNodes.erase(treeNodes.begin());

        auto iterator = treeNodes.begin();
        auto endIterator = treeNodes.end();

        while (iterator != endIterator)
        {
            if ((*iterator)->getFrequency() <= newNode->getFrequency())
            {
                iterator++;
            }
            else
            {
                break;
            }
        }

        treeNodes.insert(iterator, newNode);
    }

    root_ = treeNodes[0];

    if (root_)
    {
        BooleanVector currentCode;
        generateCodes(root_, currentCode);
    }
}

// encode: из строки в строку
double HuffmanTree::encode(const string& input, string& output)
{
    output.clear();

    if (!root_)
    {
        build(input);
    }

    if (!root_)
    {
        return -1.0;
    }

    BooleanVector result;
    uint bitPos = 0;

    for (char c : input)
    {
        BooleanVector code = codes_[static_cast<uint>(c)];
        if (code.getLength() == 0)
        {
            return -1.0;
        }

        for (uint i = 0; i < code.getLength(); i++)
        {
            result.setBit(bitPos++, code[i]);
        }
    }

    output.resize(result.getLength());
    for (uint i = 0; i < result.getLength(); i++)
    {
        output[i] = result[i] ? '1' : '0';
    }

    double originalBits = input.size() * 8;
    double compressedBits = output.size();
    return compressedBits < originalBits ? compressedBits / originalBits : -1.0;
}


// decode: из строки в строку
bool HuffmanTree::decode(const string& input, string& output)
{
    output.clear();

    if (!root_ || input.empty())
    {
        return false;
    }

    TreeNode* currentNode = root_;

    for (char bit : input)
    {
        if (bit == '0')
        {
            currentNode = currentNode->getLeftChild();
        }
        else if (bit == '1')
        {
            currentNode = currentNode->getRightChild();
        }
        else
        {
            return false;
        }

        if (!currentNode)
        {
            return false;
        }

        if (currentNode->isLeafNode())
        {
            output += currentNode->getSymbol();
            currentNode = root_;
        }
    }

    return currentNode == root_;
}

// encodeFile: из файла в файл
double HuffmanTree::encodeFile(const string& inputFileName, string& outputFileName)
{
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        return -1.0;
    }

    string input((istreambuf_iterator<char>(inputFile)),
        istreambuf_iterator<char>());
    inputFile.close();

    if (input.empty())
    {
        return -1.0;
    }

    if (!root_)
    {
        build(input);
    }

    string encoded;
    double result = encode(input, encoded);

    if (result < 0)
    {
        return -1.0;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        return -1.0;
    }

    outputFile << encoded;
    outputFile.close();

    return result;
}

// decodeFile: из файла в файл
bool HuffmanTree::decodeFile(const string& inputFileName, string& outputFileName)
{
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        return false;
    }

    string encoded((istreambuf_iterator<char>(inputFile)),
        istreambuf_iterator<char>());
    inputFile.close();

    if (encoded.empty())
    {
        return false;
    }

    string decoded;
    if (!decode(encoded, decoded))
    {
        return false;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << decoded;
    outputFile.close();

    return true;
}