#pragma once

#include <iostream>
#include "booleanvector.h"

class CharacterSet : protected BooleanVector
{
public:
    // Конструктор по умолчанию
    CharacterSet();

    // Конструктор из массива char
    CharacterSet(const char*);

    // Конструктор копирования
    CharacterSet(const CharacterSet& other);

    // Деструктор
    ~CharacterSet();

    // Проверка наличия элемента в множестве
    bool contains(char element) const;

    // Получение мощности множества
    uint32_t getCardinality();

    // Операторы доступа к элементам
    void setElement(char element, bool value);
    bool getElement(char element) const;

    // Присваивание (=)
    CharacterSet& operator=(const CharacterSet& other);

    // Сравнение (==, !=);
    bool operator==(const CharacterSet& other) const;
    bool operator!=(const CharacterSet& other) const;

    // Объединение множеств (|)
    CharacterSet operator|(const CharacterSet& other) const;

    // Пересечение множеств (&)
    CharacterSet operator&(const CharacterSet& other) const;

    // Разность множеств (/)
    CharacterSet operator/(const CharacterSet& other) const;

    // Получение дополнения (~, множество, состоящее из элементов, которые не входят в исходное множество)
    CharacterSet operator~() const;

    // Добавление элемента к множеству (+)
    CharacterSet operator+(char element);

    // Удаление элемента из множества (-)
    CharacterSet operator-(char element);

};

// Перегрузка оператора вывода/ввода в консоль
std::ostream& operator<<(std::ostream&, const CharacterSet&);
std::istream& operator>>(std::istream&, CharacterSet&);