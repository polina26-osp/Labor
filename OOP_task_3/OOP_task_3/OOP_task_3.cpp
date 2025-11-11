#include <iostream>
#include "booleanvector.h"

using namespace std;

void test_all_functions() {
    // Конструкторы
    BooleanVector empty;
    cout << "Конструктор по умолчанию: длина = " << empty.getLength() << "\n";

    BooleanVector allTrue(8, true);
    cout << "Конструктор(8, true): " << allTrue << ", вес = " << allTrue.getWeight() << "\n";

    BooleanVector allFalse(12, false);
    cout << "Конструктор(12, false): " << allFalse << ", вес = " << allFalse.getWeight() << "\n";

    BooleanVector fromString("11001010");
    cout << "Конструктор из массива const char * \"11001010\": " << fromString << ", вес = " << fromString.getWeight() << "\n";

    BooleanVector manual(8, false);
    manual.setBit(0, true);
    manual.setBit(4, true);
    cout << "Ручная установка битов (11001010): " << manual << ", вес = " << manual.getWeight() << "\n";

    BooleanVector copy(manual);
    cout << "Конструктор копирования: " << copy << "\n";

    cout << "\n";

    // Операторы присваивания
    BooleanVector assigned;
    assigned = manual;
    cout << "Копирующее присваивание: " << assigned << "\n";

    cout << "\n";

    // Методы доступа
    cout << "Вектор: " << manual << "\n";
    cout << "Длина: " << manual.getLength() << ", Вес: " << manual.getWeight() << "\n";

    // Установка битов через operator[]
    BooleanVector modifiable("00000000");
    cout << "До модификации: " << modifiable << "\n";

    modifiable[0] = true;
    modifiable[2] = true;
    modifiable[4] = true;
    modifiable[7] = true;

    cout << "После установки битов 0,2,4,7: " << modifiable << "\n";
    cout << "Вес после установки: " << modifiable.getWeight() << "\n";

    // setBit
    modifiable.setBit(1, true);
    modifiable.setBit(3, true);
    cout << "После setBit(1,true) и setBit(3,true): " << modifiable << "\n";

    cout << "\n";

    // Методы установки битов
    BooleanVector testSetBits("0000000000");
    cout << "Исходный вектор: " << testSetBits << "\n";

    testSetBits.setBits(2, 4, true);
    cout << "После setBits(2, 4, true): " << testSetBits << "\n";

    testSetBits.setBits(0, 3, false);
    cout << "После setBits(0, 3, false): " << testSetBits << "\n";

    testSetBits.setAll(true);
    cout << "После setAll(true): " << testSetBits << "\n";

    testSetBits.setAll(false);
    cout << "После setAll(false): " << testSetBits << "\n";

    // Инверсия
    BooleanVector testInvert("10100000");
    cout << "До инверсии: " << testInvert << "\n";
    testInvert.invert();
    cout << "После инверсии всех битов: " << testInvert << "\n";

    // Инверсия отдельных битов
    BooleanVector testInvertBit("01010101");
    cout << "Исходный вектор: " << testInvertBit << "\n";

    testInvertBit.invertBit(0);
    cout << "После invertBit(0): " << testInvertBit << "\n";

    testInvertBit.invertBit(2);
    cout << "После invertBit(2): " << testInvertBit << "\n";

    testInvertBit.invertBit(4);
    cout << "После invertBit(4): " << testInvertBit << "\n";

    cout << "\n";

    // Побитовые операции
    BooleanVector a("11001100");
    BooleanVector b("10101010");

    cout << "a = " << a << ", b = " << b << "\n";

    BooleanVector result = a & b;
    cout << "a & b = " << result << "\n";

    result = a;
    result &= b;
    cout << "a &= b = " << result << "\n";

    result = a | b;
    cout << "a | b = " << result << "\n";

    result = a;
    result |= b;
    cout << "a |= b = " << result << "\n";

    result = a ^ b;
    cout << "a ^ b = " << result << "\n";

    result = a;
    result ^= b;
    cout << "a ^= b = " << result << "\n";

    result = ~a;
    cout << "~a = " << result << "\n";

    cout << "\n";

    // Операторы сдвига
    BooleanVector testShift("11001100");
    cout << "Исходный вектор: " << testShift << "\n";

    BooleanVector leftShift1 = testShift << 2;
    cout << "testShift << 2: " << leftShift1 << "\n";

    BooleanVector leftShift2 = testShift << 4;
    cout << "testShift << 4: " << leftShift2 << "\n";

    BooleanVector rightShift1 = testShift >> 2;
    cout << "testShift >> 2: " << rightShift1 << "\n";

    BooleanVector rightShift2 = testShift >> 4;
    cout << "testShift >> 4: " << rightShift2 << "\n";

    BooleanVector shiftAssign = testShift;
    shiftAssign <<= 1;
    cout << "testShift <<= 1: " << shiftAssign << "\n";

    shiftAssign = testShift;
    shiftAssign >>= 1;
    cout << "testShift >>= 1: " << shiftAssign << "\n";

    cout << "\n";

    // Сравнение
    BooleanVector x("1100");
    BooleanVector y("1100");
    BooleanVector z("1010");

    cout << "x = " << x << ", y = " << y << ", z = " << z << "\n";
    cout << "x == y: " << (x == y) << " (ожидается: 1)\n";
    cout << "x == z: " << (x == z) << " (ожидается: 0)\n";

    cout << "\n";

    // Проверка потокового ввода >>
    BooleanVector inputVec;
    cout << "Введите битовую строку (например, 10101): ";
    cin >> inputVec;
    cout << "Вы ввели: " << inputVec << "\n";

    // Оператор []
    cout << "Бит №2 через оператор [] у modifiable = " << (bool)modifiable[2] << "\n";

    // Метод swap
    BooleanVector vec1("11110000");
    BooleanVector vec2("00001111");

    cout << "До swap: vec1 = " << vec1 << ", vec2 = " << vec2 << "\n";
    vec1.swap(vec2);
    cout << "После swap: vec1 = " << vec1 << ", vec2 = " << vec2 << "\n";

    cout << "\n";

    // Граничные случаи
    BooleanVector zeroLength(0, true);
    cout << "Вектор нулевой длины: длина = " << zeroLength.getLength() << "\n";

    BooleanVector singleTrue(1, true);
    cout << "Однобитный вектор(true): " << singleTrue << ", вес = " << singleTrue.getWeight() << "\n";

    BooleanVector singleFalse(1, false);
    cout << "Однобитный вектор(false): " << singleFalse << ", вес = " << singleFalse.getWeight() << "\n";

    BooleanVector sevenBits(7, true);
    cout << "7-битный вектор: " << sevenBits << ", вес = " << sevenBits.getWeight() << "\n";

    BooleanVector fifteenBits(15, false);
    cout << "15-битный вектор: " << fifteenBits << ", вес = " << fifteenBits.getWeight() << "\n";

    cout << "\n";

    // Комбинации операций
    BooleanVector v1("10101010");
    BooleanVector v2("11001100");

    cout << "v1 = " << v1 << ", v2 = " << v2 << "\n";

    result = (v1 & v2) | (~v1);
    cout << "(v1 & v2) | (~v1) = " << result << "\n";

    result = v1;
    result ^= v2;
    result.invert();
    cout << "v1 ^= v2 затем инверсия = " << result << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    test_all_functions();
    return 0;
}