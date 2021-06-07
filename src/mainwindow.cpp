/**
     * @file mainwindow.cpp
     * @brief Plik zawierajacy klasę MainWindow
     * @author Piotr Lewandowski
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#include <QDir>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), openedFileName("") {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_compressButton_clicked() {
    if (openedFileName.empty())
        QMessageBox::warning(this, " ", "No file to compress");
    else {
        std::string out_name("result.eps");
        fileLoader.setOutFile(out_name);
        fileLoader.write();
        QMessageBox::about(this, " ", "File was successfully compressed");
    }
}

void MainWindow::on_openFileButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose file to open", QDir::homePath(), ".eps (*.eps)");
    openedFileName = fileName.toStdString();
    if (!openedFileName.empty()) {
        fileLoader.setInFile(openedFileName);
        fileLoader.load();
        QMessageBox::about(this, " ", "File was successfully loaded");
    }
}