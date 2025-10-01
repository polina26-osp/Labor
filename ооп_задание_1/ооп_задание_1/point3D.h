#pragma once
#include <iostream>
#include <math.h>

class Point3D {
private:
    double x, y, z; // ���������� �����

public:
    // ����������� �� ��������� (������������� ��������� ������)
    Point3D();

    // ����������� � ����������� (������������� ���������)
    Point3D(double x_val, double y_val, double z_val);

    // ����� ��� ������ ���������
    void print() const;

    // ����� ��� ����� ���������
    void input();

    // ���������
    double getX() const;
    double getY() const;
    double getZ() const;

    // ������������ 
    void setX(double x_val);
    void setY(double y_val);
    void setZ(double z_val);

    // ��������, ����� �� ����� �� ��������� xOy
    bool xyPlane() const;

    // ��������, ����� �� ����� �� ��������� xOz
    bool xzPlane() const;

    // ��������, ����� �� ����� �� ��������� yOz
    bool yzPlane() const;

    // ��������, ����� �� ��� ����� � ����� �������
    bool sameOctant(const Point3D& other) const;

    // ��������, ����������� �� ��� ����� ������������ ������ ���������
    bool isSymmetric(const Point3D& other) const;

    // ��������� ������������ ��� Ox
    bool isSymmetricOx(const Point3D& other) const;

    // ��������� ������������ ��� Oy
    bool isSymmetricOy(const Point3D& other) const;

    // ��������� ������������ ��� Oz
    bool isSymmetricOz(const Point3D& other) const;

    // �������� "-" (�������� ���� ����� = ������)
    Point3D operator-(const Point3D& other) const;

    // ���������� ����� ������� (���������� ����� �������)
    double distance() const;

    // ����� ������-������� (���������� �� ������ ���������)
    double length() const;

    // ��������� ���������
    bool operator>(const Point3D& other) const;
    bool operator<(const Point3D& other) const;
    bool operator==(const Point3D& other) const;

    // �������� "*" (��������� ����� �� �����)
    Point3D operator*(double k) const;

    // ���������� �� ��� Ox
    double distanceToOx() const;

    // ���������� �� ��� Oy
    double distanceToOy() const;

    // ���������� �� ��� Oz
    double distanceToOz() const;

    // ��������, �������� �� ��� ����� �����������
    bool formsTriangle(const Point3D& p2, const Point3D& p3) const;

    // ���������� ������� ������������, ������������� ����� �������
    double triangleArea(const Point3D& p2, const Point3D& p3) const;

    // ������ friend ��� ��������� "����� * �����"
    friend Point3D operator*(double k, const Point3D& p);
};