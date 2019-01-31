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

class Controller : public QObject {
    Q_OBJECT
    QThread workerThread;
public:
    Controller() {
        auto worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::requestWork, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        connect(worker, &Worker::progressUpdate, this, [this](int secsLeft) {
            emit onWorkProgress(secsLeft);
        });

        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

        // Stack Overflow End
        workerThread.start();
    }

    ~Controller() {
        if (workerThread.isRunning()) {
            workerThread.quit();
            workerThread.wait();
        }
    }
public slots:
    void handleResults(const QString &result) {
        // update the mainWindow with the final result
        emit onWorkFinished(result);
    }

signals:
    void onWorkFinished(const QString&);
    void onWorkProgress(int secsLeft);
    void requestWork(int);
};
