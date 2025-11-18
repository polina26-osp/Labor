#include <iostream>
#include <sstream>
#include "booleanmatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // 1. Тестирование конструкторов
    cout << "\n1. Тестирование конструкторов:" << endl;

    // Конструктор по умолчанию
    BooleanMatrix matrix0;
    cout << "\nMatrix0 (по умолчанию):" << endl;
    cout << matrix0;
    cout << "\nРазмер: " << matrix0.numRows() << "x" << matrix0.numColumns() << endl;

    // Конструктор с параметрами
    BooleanMatrix matrix1(3, 4, true);
    cout << "\nMatrix1 (3x4, все true):" << endl;
    cout << matrix1;

    // Конструктор из char матрицы
    const char* charMatrix[] = {
        "1010",
        "0101",
        "1100"
    };
    BooleanMatrix matrix2(charMatrix, 3, 4);
    cout << "\nMatrix2 (из char матрицы):" << endl;
    cout << matrix2;

    // Конструктор копирования
    BooleanMatrix matrix3(matrix2);
    cout << "\nMatrix3 (копия Matrix2):" << endl;
    cout << matrix3;

    // 2. Тестирование размера
    cout << "\n2. Тестирование размера:" << endl;
    cout << "Размеры matrix2: " << matrix2.numRows() << "x" << matrix2.numColumns() << endl;

    // 3. Тестирование веса
    cout << "\n3. Тестирование веса:" << endl;
    cout << "Вес матрицы matrix2: " << matrix2.getWeight() << endl;
    cout << "Вес строки 0 matrix2: " << matrix2.getRowWeight(0) << endl;

    // 4. Тестирование конъюнкции и дизъюнкции
    cout << "\n4. Тестирование конъюнкции и дизъюнкции:" << endl;
    BooleanVector conj = matrix2.conjunctionAllRows();
    BooleanVector disj = matrix2.disjunctionAllRows();
    cout << "Конъюнкция всех строк: " << conj << endl;
    cout << "Дизъюнкция всех строк: " << disj << endl;

    // 5. Тестирование изменения битов
    cout << "\n5. Тестирование изменения битов:" << endl;

    cout << "Исходная matrix2:" << endl;
    cout << matrix2;

    matrix2.invertBit(0, 0);
    cout << "\nПосле инверсии бита [0][0]:" << endl;
    cout << matrix2;

    matrix2.setBit(0, 1, true);
    cout << "\nПосле установки бита [0][1] в true:" << endl;
    cout << matrix2;

    matrix2.invertBits(2, 1, 2);
    cout << "\nПосле инверсии 2 битов в строке 2, начиная с позиции 1:" << endl;
    cout << matrix2;

    matrix2.setBits(0, 2, 2, false);
    cout << "\nПосле установки 2 битов в строке 0 в false, начиная с позиции 2:" << endl;
    cout << matrix2;

    // 6. Тестирование swap
    cout << "\n6. Тестирование swap:" << endl;
    BooleanMatrix matrixA(2, 2, true);
    BooleanMatrix matrixB(2, 2, false);

    cout << "До swap:" << endl;
    cout << "\nmatrixA:" << endl << matrixA;
    cout << "\nmatrixB:" << endl << matrixB;

    matrixA.swap(matrixB);

    cout << "После swap:" << endl;
    cout << "\nmatrixA:" << endl << matrixA;
    cout << "\nmatrixB:" << endl << matrixB;

    // 7. Тестирование оператора присваивания
    cout << "\n7. Тестирование оператора присваивания:" << endl;
    BooleanMatrix matrix4;
    matrix4 = matrix2;
    cout << "\nmatrix4 (присвоено matrix2):" << endl;
    cout << matrix4;

    // 8. Тестирование побитовых операторов
    cout << "\n8. Тестирование побитовых операторов:" << endl;

    const char* charMatrix5[] = { "1100", "1010", "0110" };
    const char* charMatrix6[] = { "1010", "0101", "1100" };

    BooleanMatrix matrix5(charMatrix5, 3, 4);
    BooleanMatrix matrix6(charMatrix6, 3, 4);

    cout << "\nmatrix5:" << endl << matrix5;
    cout << "\nmatrix6:" << endl << matrix6;

    BooleanMatrix resultAnd = matrix5 & matrix6;
    cout << "\nmatrix5 & matrix6:" << endl << resultAnd;

    BooleanMatrix resultOr = matrix5 | matrix6;
    cout << "\nmatrix5 | matrix6:" << endl << resultOr;

    BooleanMatrix resultXor = matrix5 ^ matrix6;
    cout << "\nmatrix5 ^ matrix6:" << endl << resultXor;

    BooleanMatrix resultNot = ~matrix5;
    cout << "\n~matrix5:" << endl << resultNot;

    // 9. Тестирование составных присваиваний
    cout << "\n9. Тестирование присваиваний:" << endl;

    BooleanMatrix matrix7(charMatrix5, 3, 4);
    BooleanMatrix matrix8(charMatrix6, 3, 4);

    cout << "matrix7 исходный:" << endl << matrix7;
    matrix7 &= matrix8;
    cout << "\nmatrix7 &= matrix8:" << endl << matrix7;

    matrix7 = BooleanMatrix(charMatrix5, 3, 4);
    matrix7 |= matrix8;
    cout << "\nmatrix7 |= matrix8:" << endl << matrix7;

    matrix7 = BooleanMatrix(charMatrix5, 3, 4);
    matrix7 ^= matrix8;
    cout << "\nmatrix7 ^= matrix8:" << endl << matrix7;

    // 10. Тестирование оператора индексации
    cout << "\n10. Тестирование оператора индексации:" << endl;
    cout << "matrix2[0]: " << matrix2[0] << endl;

    matrix2[0][0] = true;
    cout << "\nПосле matrix2[0][0] = true:" << endl;
    cout << matrix2;

    // 11. Тестирование потокового ввода и вывода
    cout << "\n11. Тестирование потокового ввода и вывода:" << endl;
    BooleanMatrix matrixIn;
    cout << "Введите матрицу:" << endl;
    cin >> matrixIn;

    cout << "Вы ввели матрицу:" << endl;
    cout << matrixIn;
}
