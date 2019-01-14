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
    connect(mpController.get(), &Controller::onWorkFinished, 
        this, &MainWindow::workFinished);
    connect(mpController.get(), &Controller::onWorkProgress, 
        this, &MainWindow::updateValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void 
MainWindow::closeEvent(QCloseEvent* /*event*/)
{}

void 
MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage("reset", 1000);
    emit mpController->operate(10);
}

void 
MainWindow::updateValue(int secsLeft)
{
    ui->secondsLeft->setText(QString::number(secsLeft));
}

void 
MainWindow::workFinished(const QString& rResult)
{
    ui->statusBar->showMessage(rResult);
}
