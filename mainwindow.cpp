#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_guzik1_clicked()
{
    ui->widget->setTryb(0);
    ui->widget->resetScene();
}


void MainWindow::on_guzik2_clicked()
{
    ui->widget->setTryb(1);
    ui->widget->resetScene();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->widget->setN(value);
}

