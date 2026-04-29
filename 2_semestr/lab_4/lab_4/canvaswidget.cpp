#include <QPainter>
#include <QPaintEvent>

#include "mainwindow.h"
#include "binarysearchtree.h"
#include "canvaswidget.h"

// Конструктор
CanvasWidget::CanvasWidget(QWidget* parent) : QWidget(parent)
{
    // Настройка шрифта для цифр
    treeNodeKeyFont = QFont("Arial", 24, QFont::Weight::Bold);

    // Настройка пера для границы кружка (чёрная)
    nodeBorderPen = QPen(QColor(0, 0, 0));
    nodeBorderPen.setWidth(2);

    // Настройка пера для линий (чёрная)
    linePen = QPen(QColor(0, 0, 0));
    linePen.setWidth(3);

    // Настройка пера для цифр (чёрная)
    nodeKeyTextPen = QPen(QColor(0, 0, 0));

    // Настройка кисти для заливки кружка (розовая)
    nodeBrush = QBrush(QColor(255, 182, 193));
}

// Перерисовка виджета
void CanvasWidget::paintEvent(QPaintEvent* event)
{
    // Получаем указатель на главное окно
    MainWindow* mainWindowInstance = qobject_cast<MainWindow*>(window());
    // Получаем дерево из главного окна
    BinaryTree* tree = mainWindowInstance->getTree();

    QPainter painter(this);

    // Заливаем фон белым цветом
    painter.fillRect(event->rect(), QBrush(QColor(255, 255, 255)));

    int rectWidth = event->rect().width();

    // Если дерево не пустое, рисуем его
    if (tree && tree->getRoot())
    {
        drawTreeNode(tree->getRoot(), painter, rectWidth, rectWidth / 2, 0);
    }
}

// Рекурсивная отрисовка узла и его потомков
void CanvasWidget::drawTreeNode(BinaryTree::TreeNode* treeNode, QPainter& painter, int width, int xOffset, int yOffset)
{
    // Координаты центра кружка
    QPoint nodeCenterCoords(xOffset, yOffset + NODE_CIRCLE_RADIUS);
    // Координаты для вывода цифры
    QPoint nodeKeyCoords(xOffset - 3 * NODE_CIRCLE_RADIUS / 4, yOffset + 2 * NODE_CIRCLE_RADIUS - NODE_CIRCLE_RADIUS / 2);

    int halfWidth = width / 2;
    int bottomNodeOffset = yOffset + PADDING_BETWEEN_TREE_LEVELS;

    // Отрисовка линии к левому потомку
    if (treeNode->getLeftChild())
    {
        int leftSubTreeXOffset = xOffset - halfWidth / 2;
        painter.setPen(linePen);
        painter.drawLine(nodeCenterCoords, QPoint(leftSubTreeXOffset, bottomNodeOffset + NODE_CIRCLE_RADIUS));
        drawTreeNode(treeNode->getLeftChild(), painter, halfWidth, leftSubTreeXOffset, bottomNodeOffset);
    }

    // Отрисовка линии к правому потомку
    if (treeNode->getRightChild())
    {
        int rightSubTreeXOffset = xOffset + halfWidth / 2;
        painter.setPen(linePen);
        painter.drawLine(nodeCenterCoords, QPoint(rightSubTreeXOffset, bottomNodeOffset + NODE_CIRCLE_RADIUS));
        drawTreeNode(treeNode->getRightChild(), painter, halfWidth, rightSubTreeXOffset, bottomNodeOffset);
    }

    // Отрисовка кружка
    painter.setBrush(nodeBrush);
    painter.setPen(nodeBorderPen);
    painter.drawEllipse(nodeCenterCoords, NODE_CIRCLE_RADIUS, NODE_CIRCLE_RADIUS);

    // Отрисовка цифры
    painter.setFont(treeNodeKeyFont);
    painter.setPen(nodeKeyTextPen);
    painter.drawText(nodeKeyCoords, QString::number(treeNode->getKey()));
}