#include "booleanmatrix.h"
#include <stdexcept>

// Конструктор с параметрами (количество строк/столбцов и значения разрядов)
BooleanMatrix::BooleanMatrix(const uint32_t numRows, const uint32_t numColumns, const bool initialValue)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        matrixData_.add(BooleanVector(numColumns, initialValue));
    }
}

// Конструктор из матрицы char
BooleanMatrix::BooleanMatrix(const char** charMatrix, const uint32_t numRows)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        matrixData_.add(BooleanVector(charMatrix[rowIndex]));
    }
}

// Получение числа строк матрицы
uint32_t BooleanMatrix::numRows() const
{
    return matrixData_.getLength();
}

// Получение числа столбцов матрицы
uint32_t BooleanMatrix::numColumns() const
{
    return matrixData_.getLength() > 0 ? matrixData_[0].getLength() : 0;
}

// Обмен содержимого с другой матрицей (swap)
void BooleanMatrix::swap(BooleanMatrix& other)
{
    matrixData_.swap(other.matrixData_);
}

// Вес матрицы (количество единичных компонент)
uint32_t BooleanMatrix::getWeight() const
{
    uint32_t totalWeight = 0;
    for (int i = 0; i < matrixData_.getLength(); ++i)
    {
        totalWeight += matrixData_[i].getWeight();
    }
    return totalWeight;
}

// Конъюнкция всех строк (возвращает булев вектор)
BooleanVector BooleanMatrix::conjunctionAllRows() const
{
    if (matrixData_.getLength() == 0)
        return BooleanVector();

    BooleanVector result = matrixData_[0];
    for (int i = 1; i < matrixData_.getLength(); ++i)
    {
        result &= matrixData_[i];
    }
    return result;
}

// Дизъюнкция всех строк (возвращает булев вектор)
BooleanVector BooleanMatrix::disjunctionAllRows() const
{
    if (matrixData_.getLength() == 0)
        return BooleanVector();

    BooleanVector result = matrixData_[0];
    for (int i = 1; i < matrixData_.getLength(); ++i)
    {
        result |= matrixData_[i];
    }
    return result;
}

// Вес j-ой строки
uint32_t BooleanMatrix::getRowWeight(const uint32_t rowIndex) const
{
    if (rowIndex >= matrixData_.getLength())
    {
        throw std::runtime_error("Индекс строки за пределами матрицы");
    }
    return matrixData_[rowIndex].getWeight();
}

// Инверсия в i-ой компоненты j-ой строки
void BooleanMatrix::invertBit(const uint32_t rowIndex, const uint32_t bitIndex)
{
    if (rowIndex >= matrixData_.getLength())
    {
        throw std::runtime_error("Индекс строки за пределами матрицы");
    }
    matrixData_[rowIndex].invertBit(bitIndex);
}

// Инверсия k компонент j-ой строки, начиная с i-ой компоненты
void BooleanMatrix::invertBits(const uint32_t rowIndex, const uint32_t startBitIndex, const uint32_t k)
{
    if (rowIndex >= matrixData_.getLength())
    {
        throw std::runtime_error("Индекс строки за пределами матрицы");
    }
    for (uint32_t i = startBitIndex; i < startBitIndex + k && i < matrixData_[rowIndex].getLength(); ++i)
    {
        matrixData_[rowIndex].invertBit(i);
    }
}

// Установка в 0/1 i-ой компоненты j-ой строки
void BooleanMatrix::setBit(const uint32_t rowIndex, const uint32_t bitIndex, const bool value)
{
    if (rowIndex >= matrixData_.getLength())
    {
        throw std::runtime_error("Индекс строки за пределами матрицы");
    }
    matrixData_[rowIndex].setBit(bitIndex, value);
}

// Установка в 0/1 k компонент j-ой строки, начиная с i-ой компоненты
void BooleanMatrix::setBits(const uint32_t rowIndex, const uint32_t startBitIndex, const uint32_t k, const bool value)
{
    if (rowIndex >= matrixData_.getLength())
    {
        throw std::runtime_error("Индекс строки за пределами матрицы");
    }
    matrixData_[rowIndex].setBits(startBitIndex, k, value);
}

// Получение строки ([ ]) - неконстантная версия
BooleanVector& BooleanMatrix::operator[](const uint32_t rowIndex)
{
    return matrixData_[rowIndex];
}

// Получение строки ([ ]) - константная версия
const BooleanVector& BooleanMatrix::operator[](const uint32_t rowIndex) const
{
    return matrixData_[rowIndex];
}

// Построчное побитовое умножение с присваиванием (&=)
BooleanMatrix& BooleanMatrix::operator&=(const BooleanMatrix& other)
{
    const uint32_t minRows = (numRows() < other.numRows()) ? numRows() : other.numRows();

    for (uint32_t i = 0; i < minRows; ++i)
    {
        (*this)[i] &= other[i];
    }
    return *this;
}

// Построчное побитовое сложение с присваиванием (|=)
BooleanMatrix& BooleanMatrix::operator|=(const BooleanMatrix& other)
{
    const uint32_t minRows = (numRows() < other.numRows()) ? numRows() : other.numRows();

    for (uint32_t i = 0; i < minRows; ++i)
    {
        (*this)[i] |= other[i];
    }
    return *this;
}

// Построчное побитовое исключающее ИЛИ с присваиванием (^=)
BooleanMatrix& BooleanMatrix::operator^=(const BooleanMatrix& other)
{
    const uint32_t minRows = (numRows() < other.numRows()) ? numRows() : other.numRows();
    for (uint32_t i = 0; i < minRows; ++i)
    {
        (*this)[i] ^= other[i];
    }
    return *this;
}

// Построчное побитовое умножение (&)
BooleanMatrix operator&(const BooleanMatrix& lhs, const BooleanMatrix& rhs)
{
    BooleanMatrix result(lhs);
    result &= rhs;
    return result;
}

// Построчное побитовое сложение (|)
BooleanMatrix operator|(const BooleanMatrix& lhs, const BooleanMatrix& rhs)
{
    BooleanMatrix result(lhs);
    result |= rhs;
    return result;
}

// Построчное побитовое исключающее ИЛИ (^)
BooleanMatrix operator^(const BooleanMatrix& lhs, const BooleanMatrix& rhs)
{
    BooleanMatrix result(lhs);
    result ^= rhs;
    return result;
}

// Построчная побитовая инверсия (~)
BooleanMatrix BooleanMatrix::operator~() const
{
    BooleanMatrix result;
    for (uint32_t i = 0; i < numRows(); ++i)
    {
        result.matrixData_.add(~matrixData_[i]);
    }
    return result;
}

//
void BooleanMatrix::addRow(const BooleanVector& row)
{
    matrixData_.add(row);
}

// Потоковый вывод
std::ostream& operator<<(std::ostream& os, const BooleanMatrix& matrix)
{
    for (int i = 0; i < matrix.numRows(); ++i)
    {
        os << matrix[i] << std::endl;
    }
    return os;
}

// Потоковый ввод
std::istream& operator>>(std::istream& is, BooleanMatrix& matrix)
{
    uint32_t numRows, numColumns;
    std::cout << "Введите количество строк: ";
    is >> numRows;
    std::cout << "Введите количество столбцов: ";
    is >> numColumns;

    BooleanMatrix temp(numRows, numColumns, false);

    std::cout << "Введите матрицу построчно: " << std::endl;
    for (uint32_t i = 0; i < numRows; ++i)
    {
        std::string rowString;
        is >> rowString;

        if (rowString.length() > numColumns)
        {
            rowString = rowString.substr(0, numColumns);
        }

        BooleanVector rowVector(rowString.c_str());
        temp[i] = rowVector;
    }

    matrix = temp;
    return is;
}