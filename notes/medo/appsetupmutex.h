//
// Created by DrTang on 2023/12/23.
//

#ifndef NOTES_APPSETUPMUTEX_H
#define NOTES_APPSETUPMUTEX_H
#pragma once
#include <QString>
//根据操作系统的类型（在这里是Windows）选择
// 性地包含头文件或定义一些与操作系统相关的内容。
#if defined (Q_OS_WIN)
#include "windows.h"
#endif

namespace Medo{class AppSetupMutex;}
class AppSetupMutex{
public:
    AppSetupMutex(const QString& mutexName);
    ~AppSetupMutex();

private:
#if defined(Q_OS_WIN)
    //用于在Windows平台下操作互斥量。
    HANDLE _mutexHandle
};


#endif //NOTES_APPSETUPMUTEX_H
