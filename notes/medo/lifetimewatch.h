//
// Created by DrTang
//

#pragma once

#include <QElapsedTimer>
#include <QMutex>
#include <QString>
#include <QUuid>

namespace Medo { class LifetimeWatch; }

class LifetimeWatch {

    public:
        LifetimeWatch(const QString& text);
        LifetimeWatch(const QString& text, bool addGuid);
        ~LifetimeWatch();
        void done();
        void elapsed();
        void elapsed(const QString& extraText);

    private:
        QMutex _mutex;
        QUuid _uuid;
        QElapsedTimer* _stopwatch = nullptr;
        QString _text;

};
