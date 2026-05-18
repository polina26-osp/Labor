#include <iostream>
#include <fstream>
#include <algorithm>
#include "huffmantree.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // Пример 1: Кодирование и декодирование строки
    cout << "Пример 1: " << endl;
    string text = "the quick brown fox jumps over the lazy dog";

    HuffmanTree huffman;

    string encoded;
    double ratio = huffman.encode(text, encoded);

    cout << "Исходный текст: " << text << endl;
    cout << "Исходный размер: " << text.size() * 8 << " бит" << endl;
    cout << "Размер после сжатия: " << encoded.size() << " бит" << endl;
    cout << "Коэффициент сжатия: " << ratio << endl;
    cout << "Закодированная строка: " << encoded << endl;

    string decoded;
    bool success = huffman.decode(encoded, decoded);

    if (success)
    {
        cout << "Декодированная строка: " << decoded << endl;
        cout << "Декодирование успешно: " << (text == decoded ? "Да" : "Нет") << endl;
    }

    cout << endl;

    // Пример 2: Работа с файлами текста
    cout << "Пример 2:  " << endl;
    HuffmanTree huffman2;

    ofstream testFile("test_input.txt");
    testFile << text;
    testFile.close();

    cout << "Файл test_input.txt создан" << endl;

    string inputFile = "test_input.txt";
    string encodedFile = "test_encoded.bin";
    double fileRatio = huffman2.encodeFile(inputFile, encodedFile);
    cout << "Коэффициент сжатия файла: " << fileRatio << endl;

    string decodedFile = "test_output.txt";
    bool decodeSuccess = huffman2.decodeFile(encodedFile, decodedFile);
    cout << "Декодирование файла успешно: " << (decodeSuccess ? "Да" : "Нет") << endl;

    ifstream outputFile("test_output.txt");
    string decodedText((istreambuf_iterator<char>(outputFile)),
        istreambuf_iterator<char>());
    outputFile.close();

    cout << "Декодированный текст совпадает с исходным: " << (decodedText == text ? "Да" : "Нет") << endl;
    cout << endl;

    // Пример 3: Работа с файлами из 0 и 1
    cout << "Пример 3: " << endl;

    // Создание дерева Хаффмана на основе исходного текста
    HuffmanTree huffman3;
    huffman3.build(text); 

    // Чтение файла с цифрами 
    ifstream binaryFile("binary.txt");
    if (!binaryFile.is_open())
    {
        cout << "Ошибка: файл binary.txt не найден!" << endl;
        return 1;
    }

    string bitsFromFile;
    getline(binaryFile, bitsFromFile);
    binaryFile.close();

    cout << "Прочитано из файла binary.txt: " << bitsFromFile << endl;
    cout << "Длина прочитанной строки: " << bitsFromFile.size() << " бит" << endl;

    // Декодирование
    string decodedFromBits;
    bool decodeBitsSuccess = huffman3.decode(bitsFromFile, decodedFromBits);

    if (decodeBitsSuccess)
    {
        cout << "Декодированный текст: " << decodedFromBits << endl;
        cout << "Декодирование успешно " << endl;
    }
    else
    {
        cout << "Ошибка декодирования " << endl;
    }

    return 0;
}