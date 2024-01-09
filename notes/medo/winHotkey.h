//
// Created by DrTang
//

#pragma once
#include <QAbstractNativeEventFilter>
#include <QByteArray>
#include <QObject>
#include <QKeySequence>

namespace Medo { class WinHotkey; }

class WinHotkey : public QObject, QAbstractNativeEventFilter {
        Q_OBJECT

    public:

        /*! Creates a new instance */
        explicit WinHotkey(QObject* parent = nullptr);

        /*! Destroys the instance */
        ~WinHotkey();

        /*! Registers hotkey.
         * \param key Hotkey. Cannot have more than one key combination. */
        bool registerHotkey(QKeySequence key);

        /*! Disables currently registered hotkey. */
        bool unregisterHotkey();

        /*! Temporarily suspends hotkey capturing. Not thread-safe. */
        void suspend();

        /*! Resumes previously suspended capturing. Not thread-safe. */
        void resume();


    signals:

        /*! Signals hotkey has been activated */
        void activated();


    protected:
        bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;

    private:
        bool _isRegistered = false;
        int suspensionLevel = 0;
        QKeySequence _key;
        void nativeInit();
        bool nativeRegisterHotkey(Qt::Key key, Qt::KeyboardModifiers modifiers);
        bool nativeUnregisterHotkey();

        static std::atomic<uint64_t> _globalHotkeyCounter; //actually WPARAM; just 64-bit integer here to avoid include of windows.h
        uint64_t _hotkeyId = 0; //0x0000 through 0xBFFF

};
