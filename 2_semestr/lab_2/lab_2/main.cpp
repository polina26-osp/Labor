#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

#if 0
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "binarytree.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    cout << "1. Конструктор по умолчанию" << endl;
    BinaryTree tree1;
    cout << "   isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << endl << endl;

    cout << "2. Добавление узлов" << endl;
    for (int i = 0; i < 10; i++)
    {
        int key = rand() % 100;
        tree1.addNode(key);
        cout << "   Добавлен ключ: " << key << endl;
    }
    cout << endl;

    cout << "3. Количество узлов: " << tree1.getNodeCount() << endl << endl;

    cout << "4. Высота дерева: " << tree1.getHeight() << endl << endl;

    cout << "5. Минимальный ключ: " << tree1.getMiminalKey() << endl << endl;

    cout << "6. Максимальный ключ: " << tree1.getMaxKey() << endl << endl;

    return 0;
}

#endif
