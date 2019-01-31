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
    ui->secondsLeft->setText(QString());
    ui->statusBar->showMessage("reset", 1000);
    emit mpController->requestWork(10);
}

void 
MainWindow::updateValue(int secsLeft)
{
    ui->secondsLeft->setText(
        secsLeft> 0? QString::number(secsLeft) : "timeout!");
}

void 
MainWindow::workFinished(const QString& rResult)
{
    ui->statusBar->showMessage(rResult);
}
