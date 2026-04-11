#pragma once

#include <QMainWindow>

class QHBoxLayout;
class QWidget;

class CanvasWidget;
class BinaryTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:

    // Конструктор
    MainWindow(QWidget* parent = nullptr);
    // Деструктор
    ~MainWindow();

    // Получение указателя на дерево
    BinaryTree* getTree() { return tree_; }

private:

    // Контейнер для виджетов
    QWidget* container_;
    // Виджет для отрисовки дерева
    CanvasWidget* canvasWidget_;
    // Компоновка
    QHBoxLayout* mainLayout_;
    // Указатель на дерево
    BinaryTree* tree_;
};
