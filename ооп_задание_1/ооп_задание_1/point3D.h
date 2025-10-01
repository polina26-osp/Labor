#pragma once
#include <iostream>
#include <math.h>

class Point3D {
private:
    double x, y, z; // Координаты точки

public:
    // Конструктор по умолчанию (инициализация координат нулями)
    Point3D();

    // Конструктор с аргументами (инициализация координат)
    Point3D(double x_val, double y_val, double z_val);

    // Метод для вывода координат
    void print() const;

    // Метод для ввода координат
    void input();

    // Аксессоры
    double getX() const;
    double getY() const;
    double getZ() const;

    // Модификаторы 
    void setX(double x_val);
    void setY(double y_val);
    void setZ(double z_val);

    // Проверка, лежит ли точка на плоскости xOy
    bool xyPlane() const;

    // Проверка, лежит ли точка на плоскости xOz
    bool xzPlane() const;

    // Проверка, лежит ли точка на плоскости yOz
    bool yzPlane() const;

    // Проверка, лежат ли две точки в одном октанте
    bool sameOctant(const Point3D& other) const;

    // Проверка, симметричны ли две точки относительно начала координат
    bool isSymmetric(const Point3D& other) const;

    // Симметрия относительно оси Ox
    bool isSymmetricOx(const Point3D& other) const;

    // Симметрия относительно оси Oy
    bool isSymmetricOy(const Point3D& other) const;

    // Симметрия относительно оси Oz
    bool isSymmetricOz(const Point3D& other) const;

    // Оператор "-" (разность двух точек = вектор)
    Point3D operator-(const Point3D& other) const;

    // Вычисления длины вектора (расстояние между точками)
    double distance() const;

    // Длина радиус-вектора (расстояние от начала координат)
    double length() const;

    // Операторы сравнения
    bool operator>(const Point3D& other) const;
    bool operator<(const Point3D& other) const;
    bool operator==(const Point3D& other) const;

    // Оператор "*" (умножение точки на число)
    Point3D operator*(double k) const;

    // Расстояние до оси Ox
    double distanceToOx() const;

    // Расстояние до оси Oy
    double distanceToOy() const;

    // Расстояние до оси Oz
    double distanceToOz() const;

    // Проверка, образуют ли три точки треугольник
    bool formsTriangle(const Point3D& p2, const Point3D& p3) const;

    // Вычисление площади треугольника, образованного тремя точками
    double triangleArea(const Point3D& p2, const Point3D& p3) const;

    // Делаем friend для поддержки "число * точка"
    friend Point3D operator*(double k, const Point3D& p);
};