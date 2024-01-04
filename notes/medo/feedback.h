//
// Created by DrTang on 2023/12/25.
//

#ifndef NOTES_FEEDBACK_H
#define NOTES_FEEDBACK_H

#pragma once  // 防止头文件被重复引用

#include <QNetworkReply>  // 包含 QNetworkReply 类的头文件
#include <QWidget>         // 包含 QWidget 类的头文件

namespace Medo { class Feedback; }  // Medo 命名空间中声明 Feedback 类

class Feedback {

public:
    /*! 显示反馈对话框。 */
    static bool showDialog(QWidget* parent, QUrl url);

private:
    /*! 发送反馈信息。 */
    static bool sendFeedback(QString text, QString senderEmail, QString senderDisplayName, QUrl url);

    static QString _errorMessage;  // 存储错误消息的静态成员变量

};



#endif //NOTES_FEEDBACK_H
