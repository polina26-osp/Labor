#include <windows.h>
#include "Point3D.h"
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // Создание точки и вывод ее на экран
    Point3D p1;  // Конструктор по умолчанию
    p1.print();

    Point3D p2(2, 8, 15);  // Конструктор с аргументами
    p2.print();

    // Создание точки с вводом координат с клавиатуры
    Point3D p3;
    p3.input();
    p3.print();

    // Проверка октанта
    if (p2.sameOctant(p3)) {
        cout << "Точки p2 и p3 находятся в одном октанте.\n\n";
    }
    else {
        cout << "Точки p2 и p3 находятся в разных октантах.\n\n";
    }

    // Проверка симметрии относительно начала координат
    if (p2.isSymmetric(p3)) {
        cout << "Точки p2 и p3 симметричны относительно начала координат.\n";
    }
    else {
        cout << "Точки p2 и p3 не симметричны относительно начала координат.\n";
    }

    // Проверка симметрии относительно осей
    if (p2.isSymmetricOx(p3))
        cout << "Точки симметричны относительно оси Ox.\n";
    if (p2.isSymmetricOy(p3))
        cout << "Точки симметричны относительно оси Oy.\n";
    if (p2.isSymmetricOz(p3))
        cout << "Точки симметричны относительно оси Oz.\n";

    // Нахождение расстояния
    Point3D diff = p2 - p3;
    cout << "Расстояние между точками p2 и p3: " << diff.distance() << endl;

    // Сравнение точек по расстоянию от начала координат
    if (p2 > p3)
        cout << "\np2 дальше от начала координат, чем p3\n";
    else if (p2 < p3)
        cout << "\np2 ближе к началу координат, чем p3\n";
    else
        cout << "\np2 и p3 находятся на одинаковом расстоянии от начала координат\n";

    // Умножение точки на число
    double k;
    cout << "\nВведите число для умножения точки p2: ";
    cin >> k;

    // Умножение точки на введённое число
    Point3D scaled1 = p2 * k;   // точка * число
    Point3D scaled2 = k * p2;   // число * точка

    cout << "p2 * " << k << " = "; scaled1.print();
    cout << k << " * p2 = "; scaled2.print();

    cout << "\nРасстояние от p2 до оси Ox: " << p2.distanceToOx() << endl;
    cout << "Расстояние от p2 до оси Oy: " << p2.distanceToOy() << endl;
    cout << "Расстояние от p2 до оси Oz: " << p2.distanceToOz() << endl;

    cout << "\nРасстояние от p3 до оси Ox: " << p3.distanceToOx() << endl;
    cout << "Расстояние от p3 до оси Oy: " << p3.distanceToOy() << endl;
    cout << "Расстояние от p3 до оси Oz: " << p3.distanceToOz() << endl;

    // Проверка, образуют ли три точки треугольник
    if (p1.formsTriangle(p2, p3)) {
        cout << "\nТочки p1, p2 и p3 образуют треугольник.\n";
    }
    else {
        cout << "\nТочки p1, p2 и p3 не образуют треугольник (лежат на одной прямой).\n";
    }

    // Вычисление площади треугольника
    if (p1.formsTriangle(p2, p3)) {
        double area = p1.triangleArea(p2, p3);
        cout << "Площадь треугольника, образованного точками p1, p2, p3: " << area << endl;
    }
    else {
        cout << "Треугольник не образован, площадь = 0\n";
    }

    return 0;
}
