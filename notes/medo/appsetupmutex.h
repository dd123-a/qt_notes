//
// Created by DrTang
//

#pragma once

#include <QString>
#if defined(Q_OS_WIN)
    #include "windows.h"
#endif

namespace Medo { class AppSetupMutex; }

/* Intended for use with InnoSetup - make sense for Windows only */
class AppSetupMutex {

    public:
        AppSetupMutex(const QString& mutexName);
        ~AppSetupMutex();

    private:
#if defined(Q_OS_WIN)
        HANDLE _mutexHandle;
#endif

};
