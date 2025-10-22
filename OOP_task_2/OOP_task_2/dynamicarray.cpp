#include "dynamicarray.h"
#include <iostream>

// Конструктор по умолчанию ( создаёт пустой массив (нулевой длины, без выделенной памяти ) )
DynamicArray::DynamicArray() : arrayData_(nullptr), arrayLength_(0) {}

// Конструктор из обычного массива
DynamicArray::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    std::cout << "DynamicArray::DynamicArray(int)" << std::endl;

    arrayData_ = new int[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i]=0;
    }
}

// Конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& otherArray)
{
    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;

        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new int[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

// Деструктор: освобождает память, выделенную под массив
DynamicArray::~DynamicArray()
{
    delete[] arrayData_;
}

// Оператор присваивания копированием 
DynamicArray& DynamicArray::operator=(const DynamicArray& otherArray)
{
    if (this != &otherArray)
    {
        delete[] arrayData_;

        if (otherArray.arrayLength_ == 0)
        {
            arrayData_ = nullptr;
            arrayLength_ = 0;
        }
        else
        {
            arrayLength_ = otherArray.arrayLength_;
            arrayData_ = new int[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }
    return *this;
}

//  Вставка элемента по индексу. Если индекс некорректный, вернуть false
bool DynamicArray::insertAt(const int index, const int value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new int[1];
        arrayData_[0] = value;
        ++arrayLength_;
        return true;
    }

    if (index < 0 || index > arrayLength_) return false;

    int* tempArrayData = new int[arrayLength_ + 1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
        tempArrayData[curIdx] = arrayData_[curIdx];

    tempArrayData[index] = value;

    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
        tempArrayData[curIdx + 1] = arrayData_[curIdx];

    ++arrayLength_;
    delete[] arrayData_;
    arrayData_ = tempArrayData;
    return true;
}

// Обмен содержимого с другим массивом (swap)
void DynamicArray::swap(DynamicArray& other)
{
    int* tempData = arrayData_;
    arrayData_ = other.arrayData_;
    other.arrayData_ = tempData;

    int tempLength = arrayLength_;
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = tempLength;
}

// Поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, если совпадений нет)
int DynamicArray::find(const int value) const
{
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] == value)
            return i;
    return -1;
}

// Удаление элемента по индексу. Если индекс некорректный, вернуть false
bool DynamicArray::removeAt(const int index)
{
    if (index < 0 || index >= arrayLength_) return false;

    int* tempArrayData = (arrayLength_ > 1) ? new int[arrayLength_ - 1] : nullptr;

    for (int i = 0, j = 0; i < arrayLength_; ++i)
    {
        if (i != index)
            tempArrayData[j++] = arrayData_[i];
    }

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    --arrayLength_;
    return true;
}

// Удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
bool DynamicArray::removeValue(const int value)
{
    int index = find(value);
    if (index == -1)
        return false;
    return removeAt(index);
}

// Сортировка элементов массива по возрастанию ( Пузырьком )
void DynamicArray::sort()
{
    for (int i = 0; i < arrayLength_ - 1; ++i)
    {
        for (int j = 0; j < arrayLength_ - i - 1; ++j)
        {
            if (arrayData_[j] > arrayData_[j + 1])
            {
                int temp = arrayData_[j];
                arrayData_[j] = arrayData_[j + 1];
                arrayData_[j + 1] = temp;
            }
        }
    }
}

// Потоковый вывод
std::ostream& operator<<(std::ostream& os, const DynamicArray& arr)
{
    os << "[ ";
    for (int i = 0; i < arr.arrayLength_; ++i)
    {
        os << arr.arrayData_[i];
        if (i < arr.arrayLength_ - 1)
            os << ", ";
    }
    os << " ]";
    return os;
}

// Потоковый ввод 
std::istream& operator>>(std::istream& is, DynamicArray& arr)
{
    int newLength;
    std::cout << "Введите количество элементов: ";
    is >> newLength;

    delete[] arr.arrayData_;

    arr.arrayLength_ = newLength;
    arr.arrayData_ = new int[newLength];

    std::cout << "Введите элементы через пробел: ";
    for (int i = 0; i < newLength; ++i)
        is >> arr.arrayData_[i];

    return is;
}

// Добавление элемента в конец массива
void DynamicArray::add(const int value)
{
    int* tempArrayData = new int[arrayLength_ + 1];

    for (int index = 0; index < arrayLength_; ++index)
    {
        tempArrayData[index] = arrayData_[index];
    }

    tempArrayData[arrayLength_] = value;

    ++arrayLength_;

    delete[] arrayData_;
    arrayData_ = tempArrayData;
}

// Удаление всех элементов с заданным значением
void DynamicArray::removeAll(const int value)
{
    if (arrayLength_ == 0) return;

    int countToKeep = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            ++countToKeep;

    if (countToKeep == arrayLength_) return;

    int* tempArrayData = (countToKeep > 0) ? new int[countToKeep] : nullptr;

    int j = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            tempArrayData[j++] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ = countToKeep;
}

// Поиск максимального элемента
int DynamicArray::getMax() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    int maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] > maxVal)
            maxVal = arrayData_[i];
    return maxVal;
}

// Поиск минимального элемента
int DynamicArray::getMin() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    int minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] < minVal)
            minVal = arrayData_[i];
    return minVal;
}

// Перегрузка сложение (конкатенация) с другим массивом (+)
DynamicArray DynamicArray::operator+(const DynamicArray& other) const
{
    DynamicArray result;
    result.arrayLength_ = arrayLength_ + other.arrayLength_;
    result.arrayData_ = new int[result.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        result.arrayData_[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        result.arrayData_[arrayLength_ + j] = other.arrayData_[j];

    return result;
}

// Перегрузка сложение (конкатенация) с другим массивом (+=)
DynamicArray& DynamicArray::operator+=(const DynamicArray& other)
{
    int* tempArrayData = new int[arrayLength_ + other.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        tempArrayData[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        tempArrayData[arrayLength_ + j] = other.arrayData_[j];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ += other.arrayLength_;

    return *this;
}

//  Перегрузка сравнение (==)
bool DynamicArray::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != other.arrayData_[i])
            return false;
    return true;
}

// Перегрузка сравнение (!=)
bool DynamicArray::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}