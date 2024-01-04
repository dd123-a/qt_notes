//
// Created by DrTang on 2023/12/25.
//

#include <QCoreApplication>
#include <QMessageBox>
#include "about.h"

void About::showDialog(QWidget *parent) {
    //构建描述信息
    QString description=QCoreApplication::applicationName();
    description.append(" ");

    // 判断是否定义了版本号，选择使用预定义的版本号或运行时版本号
#ifdef APP_VERSION
    description.append(APP_VERSION);
#else
    description.append(QCoreApplication::applicationVersion());
#endif

    // 判断是否定义了提交号，如果有则附加到版本号后
#ifdef APP_COMMIT
QString commit = APP_COMMIT;
if (commit.length() > 0) {
    description.append("+");
    description.append(APP_COMMIT);
}
#endif

// 判断是否为调试版本，如果是则在描述信息中添加 "DEBUG"
#ifdef QT_DEBUG
description.append("\nDEBUG");
#endif

description.append("\n\nQt ");
QString runtimeVersion = qVersion(); // 获取运行时 Qt 版本
QString compileVersion = QT_VERSION_STR;; // 获取编译时 Qt 版本
description.append(runtimeVersion);
if (runtimeVersion != compileVersion) {
    description.append(" / ");
    description.append(compileVersion);
}
description.append("\n" + QSysInfo::prettyProductName()); // 系统名称
description.append("\n" + QSysInfo::kernelType() + " " + QSysInfo::kernelVersion()); // 内核类型和版本

// 判断是否定义了版权信息，如果有则添加到描述信息中
#ifdef APP_COPYRIGHT
description.append("\n\n");
description.append(APP_COPYRIGHT);
#endif

// 显示关于对话框
QMessageBox::about(parent, "About",  description); // 使用 QMessageBox::about 方法显示关于对话框

}
