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

private:
    //! Override the default close event if we need to cleanup
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void updateValue(int secsLeft);
    void workFinished(const QString& rResult);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Controller> mpController;
};
