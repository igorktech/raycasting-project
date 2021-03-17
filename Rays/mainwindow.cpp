#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //устанавливаем фокус ввода на DrawMap
    ui->map->setFocus();
    //передаем указатель на игрока
    ui->playerView->setPl(ui->map->mpp()->player());

}

MainWindow::~MainWindow()
{
    delete ui;
}

