//
// Created by DrTang on 2024/1/7.
//

#include "dconfHotkey.h"
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>

DConfHotkey::DConfHotkey(QString name, QObject* parent)
: QObject(parent) {
    _name = name;
}

// 获取表示键盘快捷键的字符串
QString getKeyString(QKeySequence key) {
    auto keyboardKey = Qt::Key(key[0] & static_cast<int>(~Qt::KeyboardModifierMask));
    auto keyboardModifiers = Qt::KeyboardModifiers(key[0] & static_cast<int>(Qt::KeyboardModifierMask));

    QString keySequence;
    // 处理各种修饰键
    if (keyboardModifiers & Qt::ShiftModifier)   { keySequence += "<Shift>";   keyboardModifiers ^= Qt::ShiftModifier; }
    if (keyboardModifiers & Qt::ControlModifier) { keySequence += "<Control>"; keyboardModifiers ^= Qt::ControlModifier; }
    if (keyboardModifiers & Qt::AltModifier)     { keySequence += "<Alt>";     keyboardModifiers ^= Qt::AltModifier; }
    if (keyboardModifiers & Qt::MetaModifier)    { keySequence += "<Super>";   keyboardModifiers ^= Qt::MetaModifier; }

    // 处理剩余的按键
    if (keyboardModifiers == 0) {
        QKeySequence keySeq = QKeySequence(keyboardKey);
        QString keySeqText = keySeq.toString(QKeySequence::NativeText);
        if (keySeqText.length() == 1) {
            keySequence += keySeqText.toLower();
        } else {
            keySequence += keySeqText;
        }
        return keySequence;
    } else {
        return QString();  // 无法处理所有修饰键
    }
}

// 静态常量，表示DConf中存储自定义键绑定的根路径
static const QString dconfRootPath = QStringLiteral("/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings");

// 获取DConf中的所有子键
QStringList getSubkeys() {
    QProcess dconfList;
    dconfList.start("/usr/bin/dconf",
                    QStringList({
                        "list",
                        dconfRootPath + "/"
                    }));
    dconfList.waitForFinished();
    QString dconfListText(dconfList.readAllStandardOutput());

    QStringList dconfListLines = dconfListText.split('\n', Qt::SkipEmptyParts);
    return dconfListLines;
}

// 获取指定名称的子键
QString getSubkey(QString name, QStringList subkeys) {
    for (const QString& pathSubkey : qAsConst(subkeys)) {
        if (!pathSubkey.isEmpty()) {
            QProcess dconfReadName;
            dconfReadName.start("/usr/bin/dconf",
                                QStringList({
                                    "read",
                                    dconfRootPath + "/" + pathSubkey + "name",
                                    }));
            dconfReadName.waitForFinished();
            QString dconfReadNameText(dconfReadName.readAllStandardOutput());
            dconfReadNameText = dconfReadNameText.trimmed();
            if (dconfReadNameText.compare("'" + name + "'") == 0) {
                return pathSubkey;
            }
        }
    }
    return QString();  // 未找到
}

// 更新DConf中的键绑定配置
bool applyKeybindings() {
    QStringList subkeys = getSubkeys();
    QString newBindings;
    newBindings += "[";
    bool hadOne = false;
    for (const QString& subKey : qAsConst(subkeys)) {
        if (hadOne) { newBindings +=", "; } else { hadOne = true; }
        newBindings += "'" + dconfRootPath + "/" + subKey + "'";
    }
    newBindings += "]";

    bool isOk = true;

    QProcess dconfReadBindings;
    dconfReadBindings.start("/usr/bin/dconf",
                            QStringList {
        "read",
        dconfRootPath,
        });
    dconfReadBindings.waitForFinished();
    QString currBindings;
    if (dconfReadBindings.exitCode() == 0) {
        currBindings = dconfReadBindings.readAllStandardOutput().trimmed();
    }

    // 只有在新旧键绑定不同的情况下更新
    if (newBindings.compare(currBindings) != 0) {
        if (hadOne) {
            QProcess dconfWriteBindings;
            dconfWriteBindings.start("/usr/bin/dconf",
                                     QStringList {
                "write",
                dconfRootPath,
                newBindings,
                });
            dconfWriteBindings.waitForFinished();
            isOk = isOk && (dconfWriteBindings.exitCode() == 0);
        } else {
            QProcess dconfResetBindings;
            dconfResetBindings.start("/usr/bin/dconf",
                                     QStringList {
                "reset",
                dconfRootPath,
                });
            dconfResetBindings.waitForFinished();
            isOk = isOk && (dconfResetBindings.exitCode() == 0);
        }
    }

    return isOk;
}

// 检查是否已经注册了特定名称的热键
bool DConfHotkey::hasRegisteredHotkey() {
    QStringList dconfListLines = getSubkeys();
    QString selectedSubkey = getSubkey(_name, dconfListLines);
    return !selectedSubkey.isEmpty();
}

// 注册热键到DConf中
bool DConfHotkey::registerHotkey(QKeySequence key) {
    if (key.count() != 1) {
        qDebug().noquote() << "[DConfHotkey]" << "必须只有一个键组合!";
        return false;
    }

    QString keySequence = getKeyString(key);
    if (keySequence.isEmpty()) {
        qDebug().noquote() << "[DConfHotkey]" << "无法解析键序列!";
        return false;
    }

    QStringList subkeys = getSubkeys();
    QString selectedSubkey = getSubkey(_name, subkeys);

    // 如果未找到已注册的键，则找到一个可用的子键
    if (selectedSubkey.isEmpty()) {
        int maxCustom = -1;
        for (const QString& pathSubkey : qAsConst(subkeys )) {
            if (pathSubkey.startsWith("custom") && pathSubkey.endsWith("/")) {
                bool nOk;
                int customNumber = pathSubkey.midRef(6, pathSubkey.length() - 7).toInt(&nOk);
                if (nOk && customNumber > maxCustom) {
                    maxCustom = customNumber;
                }
            }
        }
        selectedSubkey = "custom" + QString::number(maxCustom +1) + "/";
    }

    bool isOk = true;
    QString dconfPath = dconfRootPath + "/" + selectedSubkey;

    // 读取当前名称并与新名称比较，只有在不同的情况下才更新
    QProcess dconfReadName;
    dconfReadName.start("/usr/bin/dconf",
                        QStringList {
        "read",
        dconfPath + "name",
        });
    dconfReadName.waitForFinished();
    QString currName;
    if (dconfReadName.exitCode() == 0) {
        currName = dconfReadName.readAllStandardOutput().trimmed();
    }

    QString newName = "'" + _name + "'";
    if (newName.compare(currName) != 0) {
        QProcess dconfWriteName;
        dconfWriteName.start("/usr/bin/dconf",
                             QStringList {
            "write",
            dconfPath + "name",
            newName,
            });
        dconfWriteName.waitForFinished();
        isOk = isOk && (dconfWriteName.exitCode() == 0);
    }

    // 读取当前命令并与新命令比较，只有在不同的情况下才更新
    QProcess dconfReadCommand;
    dconfReadCommand.start("/usr/bin/dconf",
                           QStringList {
        "read",
        dconfPath + "command",
        });
    dconfReadCommand.waitForFinished();
    QString currCommand;
    if (dconfReadCommand.exitCode() == 0) {
        currCommand = dconfReadCommand.readAllStandardOutput().trimmed();
    }

    QString newCommand = "'" + QCoreApplication::applicationFilePath() + "'";
    if (newCommand.compare(currCommand) != 0) {
        QProcess dconfWriteCommand;
        dconfWriteCommand.start("/usr/bin/dconf",
                                QStringList {
            "write",
            dconfPath + "command",
            newCommand,
            });
        dconfWriteCommand.waitForFinished();
        isOk = isOk && (dconfWriteCommand.exitCode() == 0);
    }

    // 读取当前绑定并与新绑定比较，只有在不同的情况下才更新
    QProcess dconfReadBinding;
    dconfReadBinding.start("/usr/bin/dconf",
                           QStringList {
        "read",
        dconfPath + "binding",
        });
    dconfReadBinding.waitForFinished();
    QString currBinding;
    if (dconfReadBinding.exitCode() == 0) {
        currBinding = dconfReadBinding.readAllStandardOutput().trimmed();
    }

    QString newBinding = "'" + keySequence + "'";
    if (newBinding.compare(currBinding) != 0) {
        QProcess dconfWriteBinding;
        dconfWriteBinding.start("/usr/bin/dconf",
                                QStringList {
            "write",
            dconfPath + "binding",
            newBinding,
            });
        dconfWriteBinding.waitForFinished();
        isOk = isOk && (dconfWriteBinding.exitCode() == 0);
    }

    // 如果更新成功，更新DConf中的键绑定配置
    if (isOk) { isOk = isOk && applyKeybindings(); }
    if (!isOk) { qDebug().noquote() << "[DConfHotkey]" << "注册失败!"; }
    return isOk;
}

// 取消注册DConf中的键绑定
bool DConfHotkey::unregisterHotkey() {
    QStringList subkeys = getSubkeys();
    QString selectedSubkey = getSubkey(_name, subkeys);
    if (selectedSubkey.isEmpty()) {
        qDebug().noquote() << "[DConfHotkey]" << "未找到注册信息!";
        return false;
    }

    // 重置DConf中的子键
    QProcess dconfReset;
    QString dconfPath = dconfRootPath + "/" + selectedSubkey;
    dconfReset.start("/usr/bin/dconf",
                     QStringList({
                         "reset",
                         "-f",
                         dconfPath
                     }));
    dconfReset.waitForFinished();
    bool isOk = (dconfReset.exitCode() == 0);

    // 如果更新成功，更新DConf中的键绑定配置
    if (isOk) { isOk = isOk && applyKeybindings(); }
    if (!isOk) { qDebug().noquote() << "[DConfHotkey]" << "取消注册失败!"; }
    return isOk;
}
