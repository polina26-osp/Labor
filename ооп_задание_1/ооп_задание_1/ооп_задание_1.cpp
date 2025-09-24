#include <iostream>
#include <windows.h>
using namespace std;

class Point3D {
private:
    double x, y, z; // Координаты точки

public:
    // Конструктор по умолчанию (инициализация координат нулями)
    Point3D() : x(0), y(0), z(0) {
        cout << "Точка создана с координатами по умолчанию (0, 0, 0)\n";
    }

    // Конструктор с аргументами (инициализация координат)
    Point3D(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {
        cout << "Точка создана с координатами (" << x << ", " << y << ", " << z << ")\n";
    }

    // Метод для вывода координат
    void print() const {
        cout << "Точка: (" << x << ", " << y << ", " << z << ")\n";
    }

    // Метод для ввода координат
    void input() {
        cout << "Введите координаты точки:\n";
        cout << "x: "; cin >> x;
        cout << "y: "; cin >> y;
        cout << "z: "; cin >> z;
    }

    // Аксессоры
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Модификаторы 
    void setX(double x_val) { x = x_val; }
    void setY(double y_val) { y = y_val; }
    void setZ(double z_val) { z = z_val; }

    // Проверка, лежит ли точка на плоскости xOy
    bool xyPlane() const {
        return z == 0;
    }

    // Проверка, лежит ли точка на плоскости xOz
    bool xzPlane() const {
        return y == 0;
    }

    // Проверка, лежит ли точка на плоскости yOz
    bool yzPlane() const {
        return z == 0;
    };

    int main() {
        SetConsoleOutputCP(1251);
        SetConsoleCP(1251);

        // Создание точки и вывод ее на экран
        Point3D p1;  // Конструктор по умолчанию
        p1.print();

        Point3D p2(2, 8, 10.5);  // Конструктор с аргументами
        p2.print();

        // Создание точки с вводом координат с клавиатуры
        Point3D p3;
        p3.input();
        p3.print();

        return 0;
    }