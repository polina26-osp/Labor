#include <QHBoxLayout>
#include <time.h>
#include <stdlib.h>
#include "canvaswidget.h"
#include "mainwindow.h"
#include "binarysearchtree.h"

// Конструктор главного окна
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    srand(time(nullptr));

    // Данные для оптимального дерева
    std::vector<int> keys = { 10, 20, 30, 40 };
    std::vector<unsigned int> keysFreq = { 10, 1, 1, 10 };
    std::vector<unsigned int> trapFreq = { 5, 2, 1, 1, 2 };

    // Построение оптимального дерева
    BinarySearchTree optimalTree = BinarySearchTree::createOptimalSearchTree(keys, keysFreq, trapFreq);

    tree_ = new BinarySearchTree(optimalTree);

    // Настройка окна
    setWindowTitle("Binary Search Tree - Optimal Tree");
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