#include <QHBoxLayout>
#include <time.h>
#include <stdlib.h>
#include "canvaswidget.h"
#include "mainwindow.h"
#include "binarytree.h"

// Конструктор главного окна
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    // Создание дерева
    tree_ = new BinaryTree();

    // Добавление 30 случайных узлов в дерево
    for (int i = 0; i < 30; i++)
    {
        tree_->addNode(rand() % 100);
    }

    // Настройка окна
    setWindowTitle("Binary Tree");
    resize(960, 720);

    // Компоновка и виджет для отрисовки
    mainLayout_ = new QHBoxLayout();
    canvasWidget_ = new CanvasWidget();
    mainLayout_->addWidget(canvasWidget_);

    // Установка центрального виджета
    container_ = new QWidget();
    setCentralWidget(container_);
    container_->setLayout(mainLayout_);
}

// Деструктор главного окна
MainWindow::~MainWindow()
{
    delete tree_;
}