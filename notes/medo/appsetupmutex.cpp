//
// Created by DrTang on 2023/12/25.
//
#include <QDebug>
#include "appsetupmutex.h"

const int mutexNameLength =4096;

AppSetupMutex::AppSetupMutex(const QString &mutexName) {
#if defined(Q_OS_WIN)
    // 在 Windows 操作系统上创建互斥体
    wchar_t mutexNameChars[mutexNameLength]; // 假设 4K 够用
    int len = mutexName.toWCharArray(mutexNameChars);
    assert(len + 1 < mutexNameLength);
    mutexNameChars[len] = '\0';
    _mutexHandle = CreateMutex(NULL, false, reinterpret_cast<LPCSTR>(mutexNameChars));
    if (_mutexHandle != nullptr) {
        qDebug().noquote() << "[AppSetupMutex]" << mutexName << "created as" << _mutexHandle; // 输出创建成功的日志信息
    } else {
        qDebug().noquote() << "[AppSetupMutex]" << mutexName << "could not be created"; // 输出创建失败的日志信息
    }
#else
    Q_UNUSED(mutexName) // 在非 Windows 平台上防止编译器警告
#endif
}

AppSetupMutex::~AppSetupMutex() {
#if defined(Q_OS_WIN)
    // 在 Windows 操作系统上关闭互斥体
    CloseHandle(_mutexHandle); // 关闭互斥体，CloseHandle 是 Windows API 函数
    qDebug().noquote() << "[AppSetupMutex]" << _mutexHandle << "closed"; // 输出关闭互斥体的日志信息
#endif
}

