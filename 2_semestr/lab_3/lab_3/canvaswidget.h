#pragma once

#include <QWidget>
#include <QFont>
#include <QPen>
#include <QBrush>

#include "binarytree.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT;

public:

    // Конструктор
    CanvasWidget(QWidget* parent = nullptr);

    // Перерисовка виджета
    virtual void paintEvent(QPaintEvent* event) override;

private:

    // Рекурсивная отрисовка узла и его потомков
    void drawTreeNode(BinaryTree::TreeNode* treeNode, QPainter& painter, int width, int xOffset, int yOffset);

    // Константы для отрисовки
    const int NODE_CIRCLE_RADIUS = 20;
    const int PADDING_BETWEEN_TREE_LEVELS = 80;

    // Шрифт для цифр
    QFont treeNodeKeyFont;
    // Перо для границы кружка
    QPen nodeBorderPen;
    // Перо для линий
    QPen linePen;
    // Перо для цифр
    QPen nodeKeyTextPen;
    // Кисть для заливки кружка
    QBrush nodeBrush;
};