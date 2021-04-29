#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , openedFileName("")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compressButton_clicked()
{
    if(openedFileName == "")
        QMessageBox::warning(this," ","No file to compress");
    else
        QMessageBox::about(this," ","File was successfully compressed");
}

void MainWindow::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose file to open", QDir::homePath(), ".eps (*.eps)");
    openedFileName = fileName.toStdString();
    if(fileName != "")
        QMessageBox::information(this," ",fileName);
}

double MainWindow::squareRoot(const double a) {
    double b = sqrt(a);
    if(b != b) { // nan check
        return -1.0;
    }
    else{
        return sqrt(a);
    }
}
