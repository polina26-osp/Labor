#include <string.h>
#include <iostream>
#include "characterset.h"

// Конструктор по умолчанию
CharacterSet::CharacterSet() : BooleanVector(256, false)
{

}

// Конструктор из массива char
CharacterSet::CharacterSet(const char* str) : BooleanVector(256, false)
{
    if (str == nullptr) return;

    size_t strLength = strlen(str);
    for (size_t idx = 0; idx < strLength; ++idx)
    {
        setElement(str[idx], true);
    }
}

// Конструктор копирования
CharacterSet::CharacterSet(const CharacterSet& other) : BooleanVector(other)
{

}

// Деструктор
CharacterSet::~CharacterSet()
{

}

// Получение мощности множества
uint32_t CharacterSet::getCardinality()
{
    return getWeight(); 
}

// Проверка наличия элемента в множестве
bool CharacterSet::contains(char element) const
{
    return getElement(element);
}

// Установка значения элемента
void CharacterSet::setElement(char element, bool value)
{
    setBit(static_cast<unsigned char>(element), value);
}

// Получение значения элемента
bool CharacterSet::getElement(char element) const
{
    return BooleanVector::operator[](static_cast<unsigned char>(element));
}

// Перегрузка оператора добавления элемента к множеству (+)
CharacterSet CharacterSet::operator+(char element)
{
    CharacterSet result(*this);
    result.setElement(element, true);
    return result;
}

// Перегрузка оператора удаления элемента из множества (-)
CharacterSet CharacterSet::operator-(char element)
{
    CharacterSet result(*this);
    result.setElement(element, false);
    return result;
}

// Перегрузка оператора объединения множеств (|)
CharacterSet CharacterSet::operator|(const CharacterSet& other) const
{
    CharacterSet result(*this);
    result |= other; 
    return result;
}

// Перегрузка оператора пересечения множеств (&)
CharacterSet CharacterSet::operator&(const CharacterSet& other) const
{
    CharacterSet result(*this);
    result &= other; 
    return result;
}

// Перегрузка оператора разности множеств (/)
CharacterSet CharacterSet::operator/(const CharacterSet& other) const
{
    // Разность A / B = A & ~B
    CharacterSet result(*this);
    CharacterSet notB = ~other;
    result &= notB;
    return result;
}

// Перегрузка оператора дополнения (~)
CharacterSet CharacterSet::operator~() const
{
    CharacterSet result(*this);
    result.invert(); 
    return result;
}

// Перегрузка оператора присваивания (=)
CharacterSet& CharacterSet::operator=(const CharacterSet& other)
{
    if (this != &other)
    {
        BooleanVector::operator=(other); 
    }
    return *this;
}

// Перегрузка оператора сравнения (==)
bool CharacterSet::operator==(const CharacterSet& other) const
{
    return BooleanVector::operator==(other); 
}

// Перегрузка оператора сравнения (!=)
bool CharacterSet::operator!=(const CharacterSet& other) const
{
    return !(*this == other);
}

// Перегрузка оператора вывода в консоль
std::ostream& operator<<(std::ostream& outputStream, const CharacterSet& characterSet)
{
    outputStream << "{";
    bool first = true;

    for (uint32_t idx = 0; idx < 256; ++idx)
    {
        if (characterSet.getElement(static_cast<char>(idx)))
        {
            if (!first)
            {
                outputStream << ", ";
            }

            char ch = static_cast<char>(idx);
            if (ch >= 32 && ch <= 126) 
            {
                outputStream << "'" << ch << "'";
            }
            else \
            {
                outputStream << "0x" << std::hex << idx << std::dec;
            }

            first = false;
        }
    }

    outputStream << "}";
    return outputStream;
}

// Перегрузка оператора ввода из консоли
std::istream& operator>>(std::istream& inputStream, CharacterSet& characterSet)
{
    std::string input;
    inputStream >> input; 

    characterSet = CharacterSet();

    for (char ch : input)
    {
        characterSet.setElement(ch, true);
    }

    return inputStream;
}