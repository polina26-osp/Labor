#pragma once

#include <assert.h>
#include <iostream>

class DynamicArray
{
public:
    // ����������� �� ��������� ( ������ ������ ������ (������� �����, ��� ���������� ������ ) )
    DynamicArray();

    // ����������� �� �������� �������
    DynamicArray(int);

    // ����������� ����������� ( ������ ����� ������ ��� ����� ��� ������������� ������� )
    DynamicArray(const DynamicArray&);

    // ���������� ( ����������� ����������� ���������� ������ ��� ����������� ������� )
    ~DynamicArray();

    // ��������� ������� (���������� �������� ��������� � ��������� ������)
    int getLength() const { return arrayLength_; }

    // ����� ����������� � ������ �������� (swap)
    void swap(DynamicArray& other);

    // ����� ��������(���������� ������ ������� ���������� ��������, ���� - 1, ���� ���������� ���)
    int find(const int value) const;

    // ����/����� � ������� (���������)
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
    friend std::istream& operator>>(std::istream& is, DynamicArray& arr);

    // ���������� ��������� (���������)
    void sort();

    //  ������� �������� �� �������. ���� ������ ������������, ������� false
    bool insertAt(const int, const int);

    // �������� �������� �� �������. ���� ������ ������������, ������� false
    bool removeAt(const int index);

    // �������� �������� �� �������� (������ ���������). ���� ������� ����������� � �������, ������� false
    bool removeValue(const int value);
    
    // �������� ��������� ������ �� ������� �� ������� []
    int& operator[](const int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    // ����������� ������ ��������� [] ( ��� ������� � ��������� ������ �� ������ )
    const int& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    // �������� ������������ ������������ (=)
    DynamicArray& operator=(const DynamicArray&);

    // ���������� �������� � ����� �������
    void add(const int value);

    // �������� ���� ��������� � �������� ���������
    void removeAll(const int value);

    // ����� ������������� ��������
    int getMax() const;

    // ����� ������������ ��������
    int getMin() const;

    // ���������� �������� (������������) � ������ �������� (+ � +=)
    DynamicArray operator+(const DynamicArray& other) const;
    DynamicArray& operator+=(const DynamicArray& other);

    // ���������� ��������� (== � !=)
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

private:
    int* arrayData_;
    int arrayLength_;
};
