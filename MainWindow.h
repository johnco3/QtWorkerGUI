#pragma once

// SYSTEM INCLUDES
#include <memory>
#include <QMainWindow>

// APPLICATION INCLUDES
// DEFINES
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS
namespace Ui {
class MainWindow;
}

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void updateValue(int secsLeft);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Controller> mpController;
};
