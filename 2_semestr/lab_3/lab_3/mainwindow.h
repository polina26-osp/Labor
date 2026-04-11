#pragma once

#include <QMainWindow>

class QHBoxLayout;
class QWidget;

class CanvasWidget;
class BinarySearchTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:

    // Конструктор
    MainWindow(QWidget* parent = nullptr);
    // Деструктор
    ~MainWindow();

    // Получение указателя на дерево
    BinarySearchTree* getTree() { return tree_; }

private:

    // Контейнер для виджетов
    QWidget* container_;
    // Виджет для отрисовки дерева
    CanvasWidget* canvasWidget_;
    // Компоновка
    QHBoxLayout* mainLayout_;
    // Указатель на дерево
    BinarySearchTree* tree_;
};