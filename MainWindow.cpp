#include <QThread>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Controller.h"

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mpController(std::make_unique<Controller>())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit mpController->operate(100);
}

void MainWindow::updateValue(int secsLeft)
{
    ui->secondsLeft->setText(QString::number(secsLeft));
}
