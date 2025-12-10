#pragma once

#include <assert.h>
#include <iostream>

// Шаблонный класс динамического массива
template<typename ItemType>
class DynamicArray
{
public:

    DynamicArray();
    DynamicArray(const ItemType* arr, int initialLength);
    DynamicArray(const DynamicArray&);
    DynamicArray(DynamicArray&&);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray&);
    DynamicArray& operator=(DynamicArray&&);

    // Две версии индексирования
    ItemType& operator[](const int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    const ItemType& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    bool insertAt(const int, const ItemType&);

    void add(const ItemType&);

    int getLength() const { return arrayLength_; }

    ItemType* getData() const { return arrayData_; }

    // Удаление элемента по индексу. Если индекс некорректный, вернуть false
    bool removeAt(const int index);

    // Поиск элемента(возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет)
    int find(const ItemType value) const;

    // Удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
    bool removeValue(const ItemType value);

    // Удаление всех элементов с заданным значением
    void removeAll(const ItemType value);

    // Сортировка элементов массива по возрастанию (Пузырьком)
    void sort();

    // Поиск максимального элемента
    ItemType getMax() const;

    // Поиск минимального элемента
    ItemType getMin() const;

    // Перегрузка сложение (конкатенация) с другим массивом (+)
    DynamicArray operator+(const DynamicArray& other) const;

    // Перегрузка сложение (конкатенация) с другим массивом (+=)
    DynamicArray& operator+=(const DynamicArray& other);

    // Перегрузка сравнение (==)
    bool operator==(const DynamicArray& other) const;

    // Перегрузка сравнение (!=)
    bool operator!=(const DynamicArray& other) const;

    // Обмен содержимого с другим массивом (swap)
    void swap(DynamicArray& other);

    // Потоковый вывод
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<ItemType>& arr) {
        os << "[ ";
        for (int i = 0; i < arr.arrayLength_; ++i) {
            os << arr.arrayData_[i];
            if (i < arr.arrayLength_ - 1)
                os << ", ";
        }
        os << " ]";
        return os;
    }
    // Потоковый ввод 
    friend std::istream& operator>>(std::istream& is, DynamicArray<ItemType>& arr) {
        int newLength;
        std::cout << "\nВведите количество элементов: ";
        is >> newLength;

        // Проверка на корректность длины
        if (newLength < 0) {
            newLength = 0;
        }

        // Освобождаем старую память
        delete[] arr.arrayData_;

        if (newLength > 0) {
            arr.arrayLength_ = newLength;
            arr.arrayData_ = new ItemType[newLength];

            std::cout << "Введите " << newLength << " элементов через пробел: ";
            for (int i = 0; i < newLength; ++i) {
                is >> arr.arrayData_[i];
            }
        }
        else {
            // Создаем пустой массив
            arr.arrayData_ = nullptr;
            arr.arrayLength_ = 0;
        }

        return is;
    }

private:

    ItemType* arrayData_;
    int arrayLength_;
};

// Конструктор из обычного массива 
template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const ItemType* arr, int initialLength)
{
    std::cout << "DynamicArray::DynamicArray(const ItemType*, int) " << std::endl;

    if (!arr || initialLength <= 0) {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        std::cout << "Создан пустой массив" << std::endl;
        return;
    }

    arrayLength_ = initialLength;
    arrayData_ = new ItemType[arrayLength_];

    // Копируем данные из переданного массива
    for (int i = 0; i < arrayLength_; ++i) {
        arrayData_[i] = arr[i];
    }
}


template<typename ItemType>
DynamicArray<ItemType>::DynamicArray() : arrayData_(nullptr), arrayLength_(0)
{
    std::cout << "DynamicArray::DynamicArray()" << std::endl;
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const DynamicArray<ItemType>& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(const DynamicArray&)" << std::endl;

    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new ItemType[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(DynamicArray<ItemType>&& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(DynamicArray&&)" << std::endl;

    arrayData_ = otherArray.arrayData_;
    arrayLength_ = otherArray.arrayLength_;
    otherArray.arrayData_ = nullptr;
    otherArray.arrayLength_ = 0;
}

template<typename ItemType>
DynamicArray<ItemType>::~DynamicArray()
{
    std::cout << "DynamicArray::~DynamicArray()" << std::endl;

    delete[] arrayData_;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray<ItemType>& otherArray)
{
    std::cout << "DynamicArray::operator=(const DynamicArray&)" << std::endl;

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
            arrayData_ = new ItemType[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    return *this;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(DynamicArray<ItemType>&& otherArray)
{
    std::cout << "DynamicArray::operator=(DynamicArray&&)" << std::endl;

    if (this != &otherArray)
    {
        delete[] arrayData_;

        arrayData_ = otherArray.arrayData_;
        arrayLength_ = otherArray.arrayLength_;
        otherArray.arrayData_ = nullptr;
        otherArray.arrayLength_ = 0;
    }

    return *this;
}

template<typename ItemType>
bool DynamicArray<ItemType>::insertAt(const int index, const ItemType& value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new ItemType[1];

        arrayData_[0] = value;

        ++arrayLength_;

        return true;
    }

    if (index < 0 || index > arrayLength_) return false;

    ItemType* tempArrayData = new ItemType[arrayLength_ + 1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }

    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
    {
        tempArrayData[curIdx + 1] = arrayData_[curIdx];
    }

    tempArrayData[index] = value;

    ++arrayLength_;

    delete[] arrayData_;

    arrayData_ = tempArrayData;

    return true;
}

template<typename ItemType>
void DynamicArray<ItemType>::add(const ItemType& value)
{
    ItemType* tempArrayData = new ItemType[arrayLength_ + 1];

    for (int index = 0; index < arrayLength_; ++index)
    {
        tempArrayData[index] = arrayData_[index];
    }

    tempArrayData[arrayLength_] = value;

    ++arrayLength_;

    delete[] arrayData_;
    arrayData_ = tempArrayData;
}

template<typename ItemType>
int DynamicArray<ItemType>::find(const ItemType value) const
{
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] == value)
            return i;
    return -1;
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeAt(const int index)
{
    if (index < 0 || index >= arrayLength_) return false;

    ItemType* tempArrayData = (arrayLength_ > 1) ? new ItemType[arrayLength_ - 1] : nullptr;

    for (int i = 0, j = 0; i < arrayLength_; ++i)
        if (i != index)
            tempArrayData[j++] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    --arrayLength_;
    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeValue(const ItemType value)
{
    int index = find(value);
    if (index == -1) return false;
    return removeAt(index);
}

template<typename ItemType>
void DynamicArray<ItemType>::removeAll(const ItemType value)
{
    if (arrayLength_ == 0) return;

    int countToKeep = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            ++countToKeep;

    if (countToKeep == arrayLength_) return;

    ItemType* tempArrayData = (countToKeep > 0) ? new ItemType[countToKeep] : nullptr;

    int j = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            tempArrayData[j++] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ = countToKeep;
}

template<typename ItemType>
void DynamicArray<ItemType>::sort()
{
    for (int i = 0; i < arrayLength_ - 1; ++i)
        for (int j = 0; j < arrayLength_ - i - 1; ++j)
            if (arrayData_[j] > arrayData_[j + 1])
            {
                ItemType temp = arrayData_[j];
                arrayData_[j] = arrayData_[j + 1];
                arrayData_[j + 1] = temp;
            }
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::getMax() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    ItemType maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] > maxVal)
            maxVal = arrayData_[i];
    return maxVal;
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::getMin() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    ItemType minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] < minVal)
            minVal = arrayData_[i];
    return minVal;
}

template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const DynamicArray& other) const
{
    DynamicArray result;
    result.arrayLength_ = arrayLength_ + other.arrayLength_;
    result.arrayData_ = new ItemType[result.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        result.arrayData_[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        result.arrayData_[arrayLength_ + j] = other.arrayData_[j];

    return result;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const DynamicArray& other)
{
    ItemType* tempArrayData = new ItemType[arrayLength_ + other.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        tempArrayData[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        tempArrayData[arrayLength_ + j] = other.arrayData_[j];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ += other.arrayLength_;

    return *this;
}

template<typename ItemType>
bool DynamicArray<ItemType>::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != other.arrayData_[i])
            return false;
    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}

template<typename ItemType>
void DynamicArray<ItemType>::swap(DynamicArray& other)
{
    ItemType* tempData = arrayData_;
    arrayData_ = other.arrayData_;
    other.arrayData_ = tempData;

    int tempLength = arrayLength_;
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = tempLength;
}