/**
     * @file main.cpp
     * @brief Plik zawierajacy funkcję main
     * @author Piotr Lewandowski
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
