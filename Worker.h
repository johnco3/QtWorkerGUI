#pragma once

// SYSTEM INCLUDES
#include <QTimer>
#include <QObject>
#include <QEventLoop>

// APPLICATION INCLUDES
#include "Worker.h"

// DEFINES
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(int count)  {
        QString result = "finished";
        // Event loop allocated in workerThread
        // (non-main) thread affinity (as moveToThread)
        // this is important as otherwise it would occur
        // on the main thread.
        QEventLoop loop;
        for (auto i=0; i< count; i++) {
            // wait 1000 ms doing nothing...
            QTimer::singleShot(1000, &loop, SLOT(quit()));
            // process any signals emitted above
            loop.exec();

            emit progressUpdate(i);
        }
        emit resultReady(result);
    }
signals:
    void progressUpdate(int secondsLeft);
    void resultReady(const QString &result);
};

