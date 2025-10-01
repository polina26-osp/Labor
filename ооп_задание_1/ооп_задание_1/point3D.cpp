#include "Point3D.h"
using namespace std;

// Конструктор по умолчанию (инициализация координат нулями)
Point3D::Point3D() : x(0), y(0), z(0) {
    cout << "Точка создана с координатами по умолчанию (0, 0, 0)\n";
}

// Конструктор с аргументами (инициализация координат)
Point3D::Point3D(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {
    cout << "Точка создана с координатами (" << x << ", " << y << ", " << z << ")\n";
}

// Метод для вывода координат
void Point3D::print() const {
    cout << "Вывод точки: (" << x << ", " << y << ", " << z << ")\n";
}

// Метод для ввода координат
void Point3D::input() {
    cout << "Введите координаты точки:\n";
    cout << "x: "; cin >> x;
    cout << "y: "; cin >> y;
    cout << "z: "; cin >> z;
}

// Аксессоры
double Point3D::getX() const { return x; }
double Point3D::getY() const { return y; }
double Point3D::getZ() const { return z; }

// Модификаторы 
void Point3D::setX(double x_val) { x = x_val; }
void Point3D::setY(double y_val) { y = y_val; }
void Point3D::setZ(double z_val) { z = z_val; }

// Проверка, лежит ли точка на плоскости xOy
bool Point3D::xyPlane() const { return z == 0; }

// Проверка, лежит ли точка на плоскости xOz
bool Point3D::xzPlane() const { return y == 0; }

// Проверка, лежит ли точка на плоскости yOz
bool Point3D::yzPlane() const { return x == 0; }

// Проверка, лежат ли две точки в одном октанте
bool Point3D::sameOctant(const Point3D& other) const {
    return ((x > 0 && other.x > 0) || (x < 0 && other.x < 0)) &&
        ((y > 0 && other.y > 0) || (y < 0 && other.y < 0)) &&
        ((z > 0 && other.z > 0) || (z < 0 && other.z < 0));
}

// Проверка, симметричны ли две точки относительно начала координат
bool Point3D::isSymmetric(const Point3D& other) const {
    return (x == -other.x) && (y == -other.y) && (z == -other.z);
}

// Симметрия относительно оси Ox
bool Point3D::isSymmetricOx(const Point3D& other) const {
    return (x == other.x) && (y == -other.y) && (z == -other.z);
}

// Симметрия относительно оси Oy
bool Point3D::isSymmetricOy(const Point3D& other) const {
    return (x == -other.x) && (y == other.y) && (z == -other.z);
}

// Симметрия относительно оси Oz
bool Point3D::isSymmetricOz(const Point3D& other) const {
    return (x == -other.x) && (y == -other.y) && (z == other.z);
}

// Оператор "-" (разность двух точек = вектор)
Point3D Point3D::operator-(const Point3D& other) const {
    return Point3D(x - other.x, y - other.y, z - other.z);
}

// Метод для вычисления длины вектора (расстояние между точками)
double Point3D::distance() const {
    return sqrt(x * x + y * y + z * z);
}

// Длина радиус-вектора (расстояние от начала координат)
double Point3D::length() const {
    return sqrt(x * x + y * y + z * z);
}

// Операторы сравнения
bool Point3D::operator>(const Point3D& other) const { return length() > other.length(); }
bool Point3D::operator<(const Point3D& other) const { return length() < other.length(); }
bool Point3D::operator==(const Point3D& other) const { return length() == other.length(); }

// Оператор "*" (умножение точки на число)
Point3D Point3D::operator*(double k) const {
    return Point3D(x * k, y * k, z * k);
}

// Реализация "число * точка"
Point3D operator*(double k, const Point3D& p) {
    return Point3D(p.x * k, p.y * k, p.z * k);
}

// Расстояние до оси Ox
double Point3D::distanceToOx() const { return sqrt(y * y + z * z); }

// Расстояние до оси Oy
double Point3D::distanceToOy() const { return sqrt(x * x + z * z); }

// Расстояние до оси Oz
double Point3D::distanceToOz() const { return sqrt(x * x + y * y); }

// Проверка, образуют ли три точки треугольник
bool Point3D::formsTriangle(const Point3D& p2, const Point3D& p3) const {
    Point3D AB = p2 - *this;
    Point3D AC = p3 - *this;

    // Векторное произведение AB × AC
    double crossX = AB.getY() * AC.getZ() - AB.getZ() * AC.getY();
    double crossY = AB.getZ() * AC.getX() - AB.getX() * AC.getZ();
    double crossZ = AB.getX() * AC.getY() - AB.getY() * AC.getX();

    // Если векторное произведение = (0,0,0), точки коллинеарны
    return !(crossX == 0 && crossY == 0 && crossZ == 0);
}

// Вычисление площади треугольника, образованного тремя точками
double Point3D::triangleArea(const Point3D& p2, const Point3D& p3) const {
    Point3D AB = p2 - *this;
    Point3D AC = p3 - *this;

    // Векторное произведение AB × AC
    double crossX = AB.getY() * AC.getZ() - AB.getZ() * AC.getY();
    double crossY = AB.getZ() * AC.getX() - AB.getX() * AC.getZ();
    double crossZ = AB.getX() * AC.getY() - AB.getY() * AC.getX();

    // Длина векторного произведения
    double crossLength = sqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);

    // Площадь треугольника = 0.5 * (AB × AC)
    return 0.5 * crossLength;
}
