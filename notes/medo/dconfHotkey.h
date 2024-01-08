//
// Created by DrTang on 2023/12/25.
//

#ifndef NOTES_DCONFHOTKEY_H
#define NOTES_DCONFHOTKEY_H

#pragma once
#include <QObject>
#include <QKeySequence>

namespace Medo{class DCOnfHotKey;}

class DConfHotkey:public QObject{
    Q_OBJECT        // 使用 Qt 的宏，用于启用信号和槽机制

public:
    explicit DConfHotkey(QString name,QObject* parent= nullptr);

    /*! 注册热键。
     * \param key 热键。不能有多个键组合。 */
    bool registerHotkey(QKeySequence key);

    /*! 禁用当前注册的热键。 */
    bool unregisterHotkey();

    /*! 是否有注册的热键。 */
    bool hasRegisteredHotkey();

private:
    QString _name;// 用于存储热键名称的成员变量

};









#endif //NOTES_DCONFHOTKEY_H
