#include "characterset.h"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Конструктор по умолчанию:" << endl;
    CharacterSet emptySet;

    cout << "Результат: " << emptySet << endl;
    cout << "Мощность: " << emptySet.getCardinality() << endl;
    if (emptySet.getCardinality() != 0) {
        cout << "Ошибка: Мощность пустого множества должна быть 0" << endl;
    }

    cout << "\nКонструктор из строки:" << endl;
    CharacterSet set1("abcde");
    cout << "Строка: \"abcde\"" << endl;
    cout << "Результат: " << set1 << endl;
    cout << "Мощность: " << set1.getCardinality() << endl;
    if (set1.getCardinality() != 5) {
        cout << "Ошибка: Мощность множества должна быть 5" << endl;
    }

    cout << "\nКонструктор копирования:" << endl;
    CharacterSet copySet(set1);
    cout << "Оригинал: " << set1 << endl;
    cout << "Копия: " << copySet << endl;
    cout << "Равны? " << (copySet == set1 ? "Да" : "Нет") << endl;
    if (!(copySet == set1)) {
        cout << "Ошибка: Копия должна быть равна оригиналу" << endl;
    }

    cout << "\nДеструктор:" << endl;
    CharacterSet* dynamicSet = new CharacterSet("abcde");
    cout << "Создано множество: " << *dynamicSet << endl;
    delete dynamicSet;

    cout << "\nВывод в консоль (operator<<):" << endl;
    CharacterSet set2("Hello, world!");
    cout << "Множество: " << set2 << endl;

    cout << "\nВвод из консоли (operator>>):" << endl;
    istringstream inputStream("Hello, world!");
    CharacterSet inputSet;
    inputStream >> inputSet;
    cout << "Ввод: " << endl;
    cout << "Результат: " << inputSet << endl;
    cout << "Мощность: " << inputSet.getCardinality() << endl;

    cout << "\nПроверка наличия элемента (contains):" << endl;
    CharacterSet set3("abcde");
    cout << "Множество: " << set3 << endl;
    cout << "Содержит 'a'? " << (set3.contains('a') ? "Да" : "Нет") << endl;
    cout << "Содержит 'z'? " << (set3.contains('z') ? "Да" : "Нет") << endl;
    if (!set3.contains('a')) {
        cout << "Ошибка: Множество должно содержать символ 'a'" << endl;
    }
    if (set3.contains('z')) {
        cout << "Ошибка: Множество не должно содержать символ 'z'" << endl;
    }

    cout << "\nПолучение мощности (getCardinality):" << endl;
    CharacterSet set4("abcde abc");
    cout << "Множество: " << set4 << endl;
    cout << "Мощность: " << set4.getCardinality() << endl;
    if (set4.getCardinality() != 6) {
        cout << "Ошибка: Мощность множества должна быть 6" << endl;
    }

    cout << "\nПрисваивание (operator=):" << endl;
    CharacterSet set5;
    set5 = set4;
    cout << "Исходное: " << set4 << endl;
    cout << "После присваивания: " << set5 << endl;
    cout << "Равны? " << (set5 == set4 ? "Да" : "Нет") << endl;
    if (!(set5 == set4)) {
        cout << "Ошибка: Множества должны быть равны после присваивания" << endl;
    }

    cout << "\nСравнение на равенство (operator==):" << endl;
    CharacterSet set6a("abc");
    CharacterSet set6b("abc");
    cout << "Первое множество: " << set6a << endl;
    cout << "Второе множество: " << set6b << endl;
    cout << "Равны? " << (set6a == set6b ? "Да" : "Нет") << endl;
    if (!(set6a == set6b)) {
        cout << "Ошибка: Два одинаковых множества должны быть равны" << endl;
    }

    cout << "\nСравнение на неравенство (operator!=):" << endl;
    CharacterSet set7a("abc");
    CharacterSet set7b("def");
    cout << "Первое множество: " << set7a << endl;
    cout << "Второе множество: " << set7b << endl;
    cout << "Не равны? " << (set7a != set7b ? "Да" : "Нет") << endl;
    if (!(set7a != set7b)) {
        cout << "Ошибка: Разные множества должны быть не равны" << endl;
    }

    cout << "\nОбъединение множеств (operator|):" << endl;
    CharacterSet set8a("abc");
    CharacterSet set8b("cde");
    CharacterSet unionSet = set8a | set8b;
    cout << "Множество A: " << set8a << endl;
    cout << "Множество B: " << set8b << endl;
    cout << "Объединение A | B: " << unionSet << endl;
    cout << "Мощность: " << unionSet.getCardinality() << endl;
    if (unionSet.getCardinality() != 5) {
        cout << "Ошибка: Мощность объединения должна быть 5" << endl;
    }

    cout << "\nПересечение множеств (operator&):" << endl;
    CharacterSet set9a("abc");
    CharacterSet set9b("bcd");
    CharacterSet intersectSet = set9a & set9b;
    cout << "Множество A: " << set9a << endl;
    cout << "Множество B: " << set9b << endl;
    cout << "Пересечение A & B: " << intersectSet << endl;
    cout << "Мощность: " << intersectSet.getCardinality() << endl;
    if (intersectSet.getCardinality() != 2) {
        cout << "Ошибка: Мощность пересечения должна быть 2" << endl;
    }

    cout << "\nРазность множеств (operator/):" << endl;
    CharacterSet set10a("abcde");
    CharacterSet set10b("cde");
    CharacterSet diffSet = set10a / set10b;
    cout << "Множество A: " << set10a << endl;
    cout << "Множество B: " << set10b << endl;
    cout << "Разность A / B: " << diffSet << endl;
    cout << "Мощность: " << diffSet.getCardinality() << endl;
    if (diffSet.getCardinality() != 2) {
        cout << "Ошибка: Мощность разности должна быть 2" << endl;
    }

    cout << "\nДополнение множества (operator~):" << endl;
    CharacterSet set11("ab");
    CharacterSet complementSet = ~set11;
    cout << "Исходное множество: " << set11 << endl;
    cout << "Мощность исходного: " << set11.getCardinality() << endl;
    cout << "Мощность дополнения: " << complementSet.getCardinality() << endl;
    cout << "Содержит 'a' в дополнении? " << (complementSet.contains('a') ? "Да" : "Нет") << endl;
    cout << "Содержит 'c' в дополнении? " << (complementSet.contains('c') ? "Да" : "Нет") << endl;
    if (complementSet.getCardinality() != 254) {
        cout << "Ошибка: Мощность дополнения множества из 2 элементов должна быть 254 " << endl;
    }

    cout << "\nДобавление элемента (operator+):" << endl;
    CharacterSet set12("abc");
    CharacterSet set12plus = set12 + 'd';
    cout << "Исходное множество: " << set12 << endl;
    cout << "После добавления 'd': " << set12plus << endl;
    cout << "Содержит 'd'? " << (set12plus.contains('d') ? "Да" : "Нет") << endl;
    cout << "Мощность: " << set12plus.getCardinality() << endl;
    if (set12plus.getCardinality() != 4) {
        cout << "Ошибка: Мощность после добавления 'd' к множеству {a,b,c} должна быть 4" << endl;
    }

    cout << "\nУдаление элемента (operator-):" << endl;
    CharacterSet set13("abc");
    CharacterSet set13minus = set13 - 'b';
    cout << "Исходное множество: " << set13 << endl;
    cout << "После удаления 'b': " << set13minus << endl;
    cout << "Содержит 'b'? " << (set13minus.contains('b') ? "Да" : "Нет") << endl;
    cout << "Мощность: " << set13minus.getCardinality() << endl;
    if (set13minus.getCardinality() != 2) {
        cout << "Ошибка: Мощность после удаления 'b' из множества {a,b,c} должна быть 2" << endl;
    }

    cout << "\nДобавление существующего элемента:" << endl;
    CharacterSet set14a("abc");
    CharacterSet set14a_plus = set14a + 'a';
    cout << "Исходное множество: " << set14a << endl;
    cout << "После добавления 'a': " << set14a_plus << endl;
    cout << "Мощность: " << set14a_plus.getCardinality() << endl;
    if (set14a_plus.getCardinality() != 3) {
        cout << "Ошибка: Мощность не должна измениться при добавлении существующего элемента" << endl;
    }

    cout << "\nУдаление несуществующего элемента:" << endl;
    CharacterSet set14b("abc");
    CharacterSet set14b_minus = set14b - 'z';
    cout << "Исходное множество: " << set14b << endl;
    cout << "После удаления 'z': " << set14b_minus << endl;
    cout << "Множества равны? " << (set14b == set14b_minus ? "Да" : "Нет") << endl;
    if (!(set14b == set14b_minus)) {
        cout << "Ошибка: Множества должны остаться равными при удалении несуществующего элемента" << endl;
    }

    return 0;
}