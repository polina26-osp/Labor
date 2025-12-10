#pragma once

#include <stdint.h>
#include <iostream>
#include "dynamicarray.h"
#include "booleanvector.h"

class BooleanMatrix
{
public:
    // Конструкторы
    BooleanMatrix() = default;  // Конструктор по умолчанию
    BooleanMatrix(const uint32_t numRows, const uint32_t numColumns, const bool initialValue = false);
    BooleanMatrix(const char** charMatrix, const uint32_t numRows);
    BooleanMatrix(const BooleanMatrix&) = default;   // Конструктор копирования
    ~BooleanMatrix() = default;  // Деструктор

    // Методы доступа
    uint32_t numRows() const;
    uint32_t numColumns() const;
    void swap(BooleanMatrix& other);

    // Операции с матрицей
    uint32_t getWeight() const;
    BooleanVector conjunctionAllRows() const;
    BooleanVector disjunctionAllRows() const;

    // Операции со строками
    uint32_t getRowWeight(const uint32_t rowIndex) const;
    void invertBit(const uint32_t rowIndex, const uint32_t bitIndex);
    void invertBits(const uint32_t rowIndex, const uint32_t startBitIndex, const uint32_t k);
    void setBit(const uint32_t rowIndex, const uint32_t bitIndex, const bool value);
    void setBits(const uint32_t rowIndex, const uint32_t startBitIndex, const uint32_t k, const bool value);

    // Перегрузки операторов
    BooleanMatrix& operator=(const BooleanMatrix&) = default;     // Оператор присваивания 
    BooleanVector& operator[](const uint32_t rowIndex);
    const BooleanVector& operator[](const uint32_t rowIndex) const;

    BooleanMatrix& operator&=(const BooleanMatrix& other);
    BooleanMatrix& operator|=(const BooleanMatrix& other);
    BooleanMatrix& operator^=(const BooleanMatrix& other);

    BooleanMatrix operator~() const;

    void addRow(const BooleanVector& row);   // Публичный метод для добавления строк

private:
    DynamicArray<BooleanVector> matrixData_;
};

// Свободные операторы
BooleanMatrix operator&(const BooleanMatrix& lhs, const BooleanMatrix& rhs);
BooleanMatrix operator|(const BooleanMatrix& lhs, const BooleanMatrix& rhs);
BooleanMatrix operator^(const BooleanMatrix& lhs, const BooleanMatrix& rhs);

std::ostream& operator<<(std::ostream& os, const BooleanMatrix& matrix);
std::istream& operator>>(std::istream& is, BooleanMatrix& matrix);
