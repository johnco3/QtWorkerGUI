#pragma once

// SYSTEM INCLUDES
#include <QObject>
#include <QThread>

// APPLICATION INCLUDES
#include "Worker.h"

// DEFINES
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller(/*MainWindow* mainWindow*/) {
        auto worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::operate, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
    }
    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(const QString &) {
        // how do I update the mainWindow from here
    }
signals:
    void operate(int);
};
