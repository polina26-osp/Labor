#pragma once

#include <stdint.h>
#include <iostream>

class BooleanVector
{
private:
    class BitReference;

public:
    // Конструкторы
    BooleanVector() = default;
    BooleanVector(const uint32_t numBits, const bool initialValue = false);
    ~BooleanVector();
    // Конструктор из массива const char *
    BooleanVector(const char* charArray);

    // Конструктор копирования
    BooleanVector(const BooleanVector& other);
    BooleanVector& operator=(const BooleanVector& other);

    // Методы доступа
    uint32_t getLength() const { return numBits_; }
    uint32_t getWeight() const;

    // Операторы сравнения
    bool operator==(const BooleanVector& other) const;
    bool operator!=(const BooleanVector& other) const { return !(*this == other); }

    BitReference operator[](const uint32_t index); // Оператор индексации для неконстантных объектов
    bool operator[](const uint32_t index) const;   // Оператор индексации для константных объектов

    void swap(BooleanVector& other);
    void invert(); // инверсия всех компонент вектора
    void invertBit(uint32_t index); // инверсия i-ой компоненты
    void setBit(const uint32_t index, const bool value); // установка в 0/1 i-ой компоненты
    void setBits(uint32_t startIndex, uint32_t k, bool value); // установка k компонент, начиная с i-ой
    void setAll(bool value); // установка в 0/1 всех компонент вектора

    // Побитовые операции с присваиванием
    BooleanVector& operator&=(const BooleanVector& other);
    BooleanVector& operator|=(const BooleanVector& other);
    BooleanVector& operator^=(const BooleanVector& other);
    BooleanVector& operator<<=(uint32_t shift);
    BooleanVector& operator>>=(uint32_t shift);

    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const BooleanVector& vec);
    friend std::istream& operator>>(std::istream& is, BooleanVector& vec);

private:
    uint8_t* vectorData_ = nullptr;
    uint32_t numBits_ = 0;
    uint32_t numBytes_ = 0;

    // Вспомогательные методы
    uint32_t calculateNumBytes(const uint32_t numBits) const;
    void clearUnusedBits(); // очистка неиспользуемых битов в последнем байте
};

class BooleanVector::BitReference
{
public:
    BitReference(uint8_t* bytePtr, uint8_t bitIndex);

    // Основные операции
    BitReference& operator=(const BitReference& other);
    BitReference& operator=(bool value);

    // Бинарные операции с присваиванием
    BitReference& operator&=(bool value);

    // Бинарные операции между BitReference
    bool operator&(const BitReference& other) const;
    bool operator^(const BitReference& other) const;

    // Унарные операции
    bool operator~() const;

    // Операции сравнения
    bool operator==(const BitReference& other) const;
    bool operator!=(const BitReference& other) const;
    bool operator==(bool value) const;
    bool operator!=(bool value) const;

    // Преобразования типов
    operator bool() const;
    operator int() const;

private:
    uint8_t* bytePtr_;
    uint8_t bitIndex_;
};

// Свободные операторы
BooleanVector operator&(const BooleanVector& lhs, const BooleanVector& rhs);
BooleanVector operator|(const BooleanVector& lhs, const BooleanVector& rhs);
BooleanVector operator^(const BooleanVector& lhs, const BooleanVector& rhs);
BooleanVector operator~(const BooleanVector& vec);
BooleanVector operator<<(const BooleanVector& vec, uint32_t shift);
BooleanVector operator>>(const BooleanVector& vec, uint32_t shift);