//
// Created by DrTang on 2023/12/26.
//

#include "config.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QSaveFile>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>

// 配置类的静态成员变量声明及初始化

// 用于公共访问的互斥锁，支持递归
QMutex Config::_publicAccessMutex(QMutex::Recursive);

// 用于配置文件访问的互斥锁，不支持递归
QMutex Config::_configFileMutex(QMutex::NonRecursive);

// 用于状态文件访问的互斥锁，不支持递归
QMutex Config::_stateFileMutex(QMutex::NonRecursive);

// 配置文件路径
QString Config::_configurationFilePath;

// 状态文件路径
QString Config::_stateFilePath;

// 数据目录路径
QString Config::_dataDirectoryPath;

// 应用的可移植状态，初始为未知
Config::PortableStatus Config::_isPortable(PortableStatus::Unknown);

// 是否立即保存配置的标志
bool Config::_immediateSave(true);

// 配置文件实例指针
Config::ConfigFile* Config::_configFile(nullptr);

// 状态文件实例指针
Config::ConfigFile* Config::_stateFile(nullptr);

// 重置配置信息
void Config::reset() {
    // 输出调试信息，表示开始重置配置
    qDebug().noquote().nospace() << "[Config] reset()";

    // 计时器，用于测量重置过程的时间
    QElapsedTimer stopwatch;
    stopwatch.start();

    // 使用互斥锁，确保在多线程环境中安全地执行重置操作
    QMutexLocker locker(&_publicAccessMutex);

    // 将配置文件路径、状态文件路径、数据目录路径置为空字符串
    _configurationFilePath = QString();
    _stateFilePath = QString();
    _dataDirectoryPath = QString();

    // 将应用的可移植状态设置为未知
    _isPortable = PortableStatus::Unknown;

    // 将是否立即保存配置的标志设置为 true
    _immediateSave = true;

    // 调用重置配置文件的函数
    resetConfigFile();

    // 调用重置状态文件的函数
    resetStateFile();

    // 输出调试信息，表示重置完成，并输出重置所用的时间
    qDebug().noquote().nospace() << "[Config] reset() done in " << stopwatch.elapsed() << "ms";
}

// 加载配置信息
bool Config::load() {
    // 使用互斥锁确保在多线程环境中安全地执行加载操作
    QMutexLocker locker(&_publicAccessMutex);

    // 输出调试信息，表示开始加载配置
    qDebug().noquote().nospace() << "[Config] load()";

    // 调用重置配置文件的函数
    resetConfigFile();

    // 调用重置状态文件的函数
    resetStateFile();

    // 创建 QFile 对象，表示配置文件
    QFile file(configurationFilePath());

    // 检查配置文件是否存在
    if (file.exists()) {
        // 如果配置文件存在，返回 true 表示加载成功
        return true;
    } else {
        // 如果配置文件不存在，返回 false 表示加载失败
        return false;
    }
}

// 保存配置信息
bool Config::save() {
    // 使用互斥锁确保在多线程环境中安全地执行保存操作
    QMutexLocker locker(&_publicAccessMutex);

    // 输出调试信息，表示开始保存配置
    qDebug().noquote().nospace() << "[Config] save()";

    // 调用 getConfigFile 函数获取配置文件实例，并调用其 save 函数保存配置
    bool success = getConfigFile()->save();

    // 调用 getStateFile 函数获取状态文件实例，并调用其 save 函数保存状态
    getStateFile()->save();  // 忽略状态以确定返回码

    // 返回保存配置是否成功的标志
    return success;
}

void Config::quit() {
    QMutexLocker locker(&_publicAccessMutex);
    qDebug().noquote().nospace() << "[Config] quit()";

    getConfigFile()->save();
    resetConfigFile();

    getStateFile()->save();
    resetStateFile();
}













































