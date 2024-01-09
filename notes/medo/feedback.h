//
// Created by DrTang
//

#pragma once

#include <QNetworkReply>
#include <QWidget>

namespace Medo { class Feedback; }

class Feedback {

    public:
        /*! Shows feedback dialog. */
        static bool showDialog(QWidget* parent, QUrl url);

    private:
        static bool sendFeedback(QString text, QString senderEmail, QString senderDisplayName, QUrl url);
        static QString _errorMessage;

};
