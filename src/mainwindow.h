#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static double squareRoot(const double a); // to be removed

private slots:
    void on_compressButton_clicked();

    void on_openFileButton_clicked();

private:
    Ui::MainWindow *ui;
    QString openedFileName;
};
#endif // MAINWINDOW_H
