//
// Created by DrTang
//

#pragma once
#include <QObject>
#include <QKeySequence>

namespace Medo { class DConfHotkey; }

class DConfHotkey : public QObject {
        Q_OBJECT

    public:

        /*! Creates a new instance */
        explicit DConfHotkey(QString name, QObject* parent = nullptr);

        /*! Registers hotkey.
         * \param key Hotkey. Cannot have more than one key combination. */
        bool registerHotkey(QKeySequence key);

        /*! Disables currently registered hotkey. */
        bool unregisterHotkey();

        /*! Has registered hotkey. */
        bool hasRegisteredHotkey();


    private:
        QString _name;

};
