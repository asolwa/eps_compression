/**
     * @file mainwindow.h
     * @brief Plik nagłówkowy dla klasy MainWindow
     * @author Piotr Lewandowski
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "eps_loader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
     * @class MainWindow
     * @brief Klasa będąca podstawa interfejsu graficznego programu
     * @author Piotr Lewandowski
 */

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    /**
     * Metoda, która określa działanie programu po wciśnięciu przycisku compress.
    */
    void on_compressButton_clicked();

    /**
     * Metoda, która określa działanie programu po wciśnięciu przycisku openFile.
    */
    void on_openFileButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string openedFileName;
    EpsLoader fileLoader;
};

#endif // MAINWINDOW_H
