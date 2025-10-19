#include "dynamicarray.h"
#include <iostream>

// ����������� �� ��������� ( ������ ������ ������ (������� �����, ��� ���������� ������ ) )
DynamicArray::DynamicArray() : arrayData_(nullptr), arrayLength_(0) {}

// ����������� �����������
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

// ����������: ����������� ������, ���������� ��� ������
DynamicArray::~DynamicArray()
{
    delete[] arrayData_;
}

// �������� ������������ ������������ 
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

//  ������� �������� �� �������. ���� ������ ������������, ������� false
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

// ����� ����������� � ������ �������� (swap)
void DynamicArray::swap(DynamicArray& other)
{
    int* tempData = arrayData_;
    arrayData_ = other.arrayData_;
    other.arrayData_ = tempData;

    int tempLength = arrayLength_;
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = tempLength;
}

// ����� ��������(���������� ������ ������� ���������� ��������, ���� - 1, ���� ���������� ���)
int DynamicArray::find(const int value) const
{
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] == value)
            return i;
    return -1;
}

// �������� �������� �� �������. ���� ������ ������������, ������� false
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

// �������� �������� �� �������� (������ ���������). ���� ������� ����������� � �������, ������� false
bool DynamicArray::removeValue(const int value)
{
    int index = find(value);
    if (index == -1)
        return false;
    return removeAt(index);
}

// ���������� ��������� ������� �� ����������� ( ��������� )
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

// ��������� �����
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

// ��������� ���� 
std::istream& operator>>(std::istream& is, DynamicArray& arr)
{
    for (int i = 0; i < arr.arrayLength_; ++i)
        is >> arr.arrayData_[i];
    return is;
}

// ���������� �������� � ����� �������
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

// �������� ���� ��������� � �������� ���������
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

// ����� ������������� ��������
int DynamicArray::getMax() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    int maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] > maxVal)
            maxVal = arrayData_[i];
    return maxVal;
}

// ����� ������������ ��������
int DynamicArray::getMin() const
{
    assert(arrayLength_ > 0 && "Array is empty.");
    int minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] < minVal)
            minVal = arrayData_[i];
    return minVal;
}

// ���������� �������� (������������) � ������ �������� (+)
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

// ���������� �������� (������������) � ������ �������� (+=)
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

//  ���������� ��������� (==)
bool DynamicArray::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != other.arrayData_[i])
            return false;
    return true;
}

// ���������� ��������� (!=)
bool DynamicArray::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}