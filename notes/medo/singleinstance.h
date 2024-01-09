//
// Created by DrTang
//

#pragma once

#include <QLocalServer>
#include <QMutex>
#include <QObject>

namespace Medo { class SingleInstance; }

class SingleInstance : public QObject {
        Q_OBJECT

    public:

        /*! Returns singleton instance. */
        static SingleInstance* instance();

        /*! Returns true if current application is the first instance. */
        static bool attach();

        /*! Returns true if there is another instance running. */
        static bool isOtherInstanceRunning();

    signals:

        /*! Signals that a new instance attempted attach operation. */
        void newInstanceDetected();


    private:
        explicit SingleInstance();
        ~SingleInstance() override;
        SingleInstance(const SingleInstance&) = delete;
        SingleInstance& operator=(const SingleInstance&) = delete;
        static SingleInstance _instance;
        static QMutex _mutex;
        static QLocalServer* _server;
        static bool _isFirstInstance;

    private slots:
        void onNewConnection();

};
