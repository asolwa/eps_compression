#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "eps_loader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_compressButton_clicked();

    void on_openFileButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string openedFileName;
    EpsLoader fileLoader;
};
#endif // MAINWINDOW_H
