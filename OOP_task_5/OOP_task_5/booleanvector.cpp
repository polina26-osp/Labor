#include <cstring>
#include <string>
#include "booleanvector.h"

// Расчет количества байтов для хранения заданного количества битов
uint32_t BooleanVector::calculateNumBytes(const uint32_t numBits) const
{
    return (numBits + 7) / 8;
}


// Очистка неиспользуемых битов в последнем байте
void BooleanVector::clearUnusedBits()
{
    if (numBits_ % 8 != 0 && numBytes_ > 0)
    {
        uint8_t mask = (1 << (numBits_ % 8)) - 1;
        vectorData_[numBytes_ - 1] &= mask;
    }
}

// Конструктор с параметрами (заданным размером и начальным значением)
BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
    : numBits_(numBits)
{
    if (numBits == 0) return;

    numBytes_ = calculateNumBytes(numBits_);
    vectorData_ = new uint8_t[numBytes_];

    uint8_t value = initialValue ? 0xFF : 0x00;
    for (uint32_t byteIndex = 0; byteIndex < numBytes_; byteIndex++)
    {
        vectorData_[byteIndex] = value;
    }

    clearUnusedBits();
}

// Конструктор из массива const char *
BooleanVector::BooleanVector(const char* str)
{
    if (str == nullptr) {
        numBits_ = 0;
        vectorData_ = nullptr;
        numBytes_ = 0;
        return;
    }
    // Определяем длину строки
    uint32_t length = 0;
    while (str[length] != '\0') length++;
    numBits_ = length;
    numBytes_ = (numBits_ + 7) / 8;

    if (numBytes_ > 0) {
        vectorData_ = new uint8_t[numBytes_];
        // Инициализируем нулями
        for (uint32_t i = 0; i < numBytes_; i++) {
            vectorData_[i] = 0;
        }
        // Заполняем вектор из строки
        for (uint32_t i = 0; i < numBits_; i++) {
            if (str[i] == '1') {
                uint32_t byteIndex = i / 8;
                uint32_t bitIndex = i % 8;
                vectorData_[byteIndex] |= (1 << bitIndex);
            }
        }
    }
    else {
        vectorData_ = nullptr;
    }
}

// Конструктор копирования
BooleanVector::BooleanVector(const BooleanVector& other)
{
    if (other.numBits_ == 0) {
        vectorData_ = nullptr;
        numBits_ = 0;
        numBytes_ = 0;
        return;
    }

    numBits_ = other.numBits_;
    numBytes_ = other.numBytes_;
    vectorData_ = new uint8_t[numBytes_];
    std::memcpy(vectorData_, other.vectorData_, numBytes_);
}

// Деструктор
BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
    vectorData_ = nullptr;
}

// Обмен содержимым с другим вектором
void BooleanVector::swap(BooleanVector& other)
{
    std::swap(vectorData_, other.vectorData_);
    std::swap(numBits_, other.numBits_);
    std::swap(numBytes_, other.numBytes_);
}

// Вывод вектора (потоковый)
std::ostream& operator<<(std::ostream& os, const BooleanVector& vec)
{
    for (uint32_t i = 0; i < vec.getLength(); i++)
    {
        os << (vec[i] ? '1' : '0');
    }
    return os;
}

// Ввод вектора (потоковый)
std::istream& operator>>(std::istream& is, BooleanVector& vec)
{
    std::string input;
    is >> input;

    BooleanVector temp(input.c_str());
    vec = temp;
    return is;
}

// Инверсия всех компонент вектора
void BooleanVector::invert()
{
    for (uint32_t i = 0; i < numBytes_; i++)
    {
        vectorData_[i] = ~vectorData_[i];
    }
    clearUnusedBits();
}

// Инверсия i-ой компоненты
void BooleanVector::invertBit(uint32_t index)
{
    if (index >= numBits_) return;

    uint32_t byteIndex = index / 8;
    uint32_t bitIndex = index % 8;
    vectorData_[byteIndex] ^= (1 << bitIndex);
}

// Установка в 0/1 i-ой компоненты
void BooleanVector::setBit(const uint32_t index, const bool value)
{
    (*this)[index] = value;
}

// Установка в 0/1 k компонент, начиная с i-ой;
void BooleanVector::setBits(uint32_t index, uint32_t k, bool value)
{
    if (index >= numBits_) {
        throw std::runtime_error("Индекс за пределами диапазона битового вектора");
    }

    uint32_t endIndex = index + k;
    if (endIndex > numBits_) endIndex = numBits_;

    for (uint32_t i = index; i < endIndex; i++)
    {
        setBit(i, value);
    }
}

// Установка в 0/1 всех компонент вектора
void BooleanVector::setAll(bool value)
{
    uint8_t fillValue = value ? 0xFF : 0x00;
    for (uint32_t i = 0; i < numBytes_; i++)
    {
        vectorData_[i] = fillValue;
    }
    clearUnusedBits();
}

// Вес вектора (количество единичных компонент)
uint32_t BooleanVector::getWeight() const
{
    uint32_t weight = 0;
    for (uint32_t bit = 0; bit < numBits_; bit++)
    {
        uint32_t byteIndex = bit / (8 * sizeof(uint8_t));
        uint32_t bitIndex = bit % (8 * sizeof(uint8_t));
        if (vectorData_[byteIndex] & (1 << bitIndex))
            weight++;
    }
    return weight;
}

// Перегрузки 

// Неконстантное получение компоненты ([ ])
BooleanVector::BitReference BooleanVector::operator[](const uint32_t index)
{
    if (index >= numBits_) {
        throw std::runtime_error("Индекс за пределами диапазона вектора");
    }
    uint32_t byteIndex = index / 8;
    uint32_t bitIndex = index % 8;
    return BooleanVector::BitReference(&vectorData_[byteIndex], bitIndex);
}

// Константное получение компоненты ([ ])
bool BooleanVector::operator[](const uint32_t index) const
{
    if (index >= numBits_) {
        throw std::runtime_error("Индекс за пределами диапазона вектора");
    }
    uint32_t byteIndex = index / 8;
    uint32_t bitIndex = index % 8;
    return (vectorData_[byteIndex] >> bitIndex) & 1;
}

// Побитовое умножение(И) (&)
BooleanVector operator&(const BooleanVector& lhs, const BooleanVector& rhs)
{
    BooleanVector result(lhs);
    result &= rhs;
    return result;
}

// Побитовое умножение с присваиванием (И) (&=)
BooleanVector& BooleanVector::operator&=(const BooleanVector& other)
{
    uint32_t minBytes = (numBytes_ < other.numBytes_) ? numBytes_ : other.numBytes_;
    for (uint32_t i = 0; i < minBytes; i++)
    {
        vectorData_[i] &= other.vectorData_[i];
    }
    return *this;
}

// Побитовое сложение (|)
BooleanVector operator|(const BooleanVector& lhs, const BooleanVector& rhs)
{
    BooleanVector result(lhs);
    result |= rhs;
    return result;
}

// Побитовое сложение с присваиванием (|=)
BooleanVector& BooleanVector::operator|=(const BooleanVector& other)
{
    uint32_t minBytes = (numBytes_ < other.numBytes_) ? numBytes_ : other.numBytes_;
    for (uint32_t i = 0; i < minBytes; i++)
    {
        vectorData_[i] |= other.vectorData_[i];
    }
    return *this;
}

// Побитовое исключающее ИЛИ (^)
BooleanVector operator^(const BooleanVector& lhs, const BooleanVector& rhs)
{
    BooleanVector result(lhs);
    result ^= rhs;
    return result;
}

// Побитовое исключающее ИЛИ с присваиванием (^=)
BooleanVector& BooleanVector::operator^=(const BooleanVector& other)
{
    uint32_t minBytes = (numBytes_ < other.numBytes_) ? numBytes_ : other.numBytes_;
    for (uint32_t i = 0; i < minBytes; i++)
    {
        vectorData_[i] ^= other.vectorData_[i];
    }
    return *this;
}

// Сдвиг влево (<<)
BooleanVector operator<<(const BooleanVector& vec, uint32_t shift)
{
    BooleanVector result(vec);
    result <<= shift;
    return result;
}

// Сдвиг вправо (>>)
BooleanVector operator>>(const BooleanVector& vec, uint32_t shift)
{
    BooleanVector result(vec);
    result >>= shift;
    return result;
}

// Сдвиг влево с присваиванием (<<=)
BooleanVector& BooleanVector::operator<<=(uint32_t shift)
{
    if (shift == 0) return *this;

    if (shift >= numBits_) {
        setAll(false);
        return *this;
    }

    for (uint32_t i = 0; i < numBits_ - shift; i++) {
        (*this)[i] = (*this)[i + shift];
    }

    for (uint32_t i = numBits_ - shift; i < numBits_; i++) {
        setBit(i, false);
    }

    return *this;
}

// Сдвиг вправо с присваиванием  (>>=)
BooleanVector& BooleanVector::operator>>=(uint32_t shift)
{
    if (shift == 0) return *this;

    if (shift >= numBits_) {
        setAll(false);
        return *this;
    }

    for (uint32_t i = numBits_ - 1; i >= shift; i--) {
        (*this)[i] = (*this)[i - shift];
    }

    for (uint32_t i = 0; i < shift; i++) {
        setBit(i, false);
    }

    return *this;
}


// Побитовое НЕ (инверсия) (~)
BooleanVector operator~(const BooleanVector& vec)
{
    BooleanVector result(vec);
    result.invert();
    return result;
}

// Присваивание (=)
BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
    if (this != &other) {
        delete[] vectorData_;
        if (other.numBits_ == 0) {
            vectorData_ = nullptr;
            numBits_ = numBytes_ = 0;
        }
        else {
            numBits_ = other.numBits_;
            numBytes_ = other.numBytes_;
            vectorData_ = new uint8_t[numBytes_];
            std::memcpy(vectorData_, other.vectorData_, numBytes_);
        }
    }
    return *this;
}

// Реализация конструктора BitReference
BooleanVector::BitReference::BitReference(uint8_t* bytePtr, uint8_t bitIndex)
    : bytePtr_(bytePtr), bitIndex_(bitIndex)
{
}

// Присваивание bool
BooleanVector::BitReference& BooleanVector::BitReference::operator=(bool newValue)
{
    uint8_t mask = 1 << bitIndex_;
    if (newValue)
    {
        *bytePtr_ |= mask;
    }
    else
    {
        *bytePtr_ &= ~mask;
    }
    return *this;
}

// Присваивание от другого BitReference
BooleanVector::BitReference& BooleanVector::BitReference::operator=(const BitReference& other)
{
    bool value = static_cast<bool>(other);
    uint8_t mask = 1 << bitIndex_;
    if (value)
    {
        *bytePtr_ |= mask;
    }
    else
    {
        *bytePtr_ &= ~mask;
    }
    return *this;
}

// Побитовое И с присваиванием
BooleanVector::BitReference& BooleanVector::BitReference::operator&=(bool value)
{
    bool current = static_cast<bool>(*this);
    *this = current & value;
    return *this;
}

// Побитовое И между BitReference
bool BooleanVector::BitReference::operator&(const BitReference& other) const {
    return bool(*this) & bool(other);
}

// Побитовое исключающее ИЛИ между BitReference
bool BooleanVector::BitReference::operator^(const BitReference& other) const {
    return bool(*this) ^ bool(other);
}

// Инверсия (унарное НЕ)
bool BooleanVector::BitReference::operator~() const {
    return !bool(*this);
}

// Сравнение на равенство с другим BitReference
bool BooleanVector::BitReference::operator==(const BitReference& other) const {
    return bool(*this) == bool(other);
}

// Сравнение на неравенство с другим BitReference
bool BooleanVector::BitReference::operator!=(const BitReference& other) const {
    return bool(*this) != bool(other);
}

// Сравнение на равенство с bool
bool BooleanVector::BitReference::operator==(bool value) const {
    return bool(*this) == value;
}

// Сравнение на неравенство с bool
bool BooleanVector::BitReference::operator!=(bool value) const {
    return bool(*this) != value;
}

// Преобразование в bool (чтение значения бита) 
BooleanVector::BitReference::operator bool() const
{
    return (*bytePtr_ >> bitIndex_) & 1;
}

// Преобразование в int
BooleanVector::BitReference::operator int() const
{
    return static_cast<int>(static_cast<bool>(*this));
}

//Оператор сравнения
bool BooleanVector::operator==(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) return false;
    for (uint32_t i = 0; i < numBytes_; i++)
    {
        if (vectorData_[i] != other.vectorData_[i])
            return false;
    }
    return true;
}







