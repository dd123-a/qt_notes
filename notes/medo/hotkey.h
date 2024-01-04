//
// Created by DrTang on 2023/12/25.
//

#ifndef NOTES_HOTKEY_H
#define NOTES_HOTKEY_H

#pragma once  // 防止头文件被重复引用

#include <QObject>         // 包含 QObject 类的头文件
#include <QKeySequence>    // 包含 QKeySequence 类的头文件

#if defined(Q_OS_WIN)
    #include "winHotkey.h"  // 包含 Windows 平台的热键实现头文件
#elif defined(Q_OS_LINUX)
    #include "dconfHotkey.h"  // 包含 Linux 平台 DConf 热键实现头文件
    #include "xcbHotkey.h"    // 包含 Linux 平台 Xcb 热键实现头文件
#else
    #error "Only Linux and Windows are supported!"  // 不支持的平台错误
#endif

namespace Medo { class Hotkey; }  // Medo 命名空间中声明 Hotkey 类

class Hotkey : public QObject {  // Hotkey 类继承自 QObject 类，因为不想涉及接口
    Q_OBJECT                        // 使用 Qt 的宏，用于启用信号和槽机制

public:

    /*! 创建一个新实例 */
    explicit Hotkey(QString name, bool forceDConf, bool forceXcb, QObject* parent = nullptr);

    /*! 销毁实例 */
    ~Hotkey();

    /*! 注册热键。
     * \param key 热键。不能有多个键组合。 */
    bool registerHotkey(QKeySequence key);

    /*! 重新注册不同的热键。
     * \param key 热键。不能有多个键组合。 */
    bool reregisterHotkey(QKeySequence key);

    /*! 禁用当前注册的热键。 */
    bool unregisterHotkey();

    /*! 暂时挂起热键捕获。不是线程安全的。 */
    void suspend();

    /*! 恢复之前挂起的捕获。不是线程安全的。 */
    void resume();

private:
#if defined(Q_OS_WIN)
    WinHotkey* _winHotkey = nullptr;    // Windows 平台的热键实例
#elif defined(Q_OS_LINUX)
DConfHotkey* _dconfHotkey = nullptr;  // Linux 平台 DConf 热键实例
XcbHotkey* _xcbHotkey = nullptr;      // Linux 平台 Xcb 热键实例
#endif
bool _isRegistered = false;           // 是否已注册热键标志

signals:

    /*! 信号，表示热键已被触发 */
    void activated();

    private slots:
    void onActivated();  // 槽函数，处理热键触发事件

};

#endif //NOTES_HOTKEY_H
