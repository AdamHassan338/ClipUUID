#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>

#include <uiohook.h>
#include <QDebug>
#include <unordered_set>
#include <QUuid>
class InputHandler : public QObject
{
    Q_OBJECT
public:
    static InputHandler& getInstance() {
        static InputHandler instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }
    InputHandler(InputHandler const&) = delete;
    void operator=(InputHandler const&) = delete;

    void emitHotkey(){
        emit hotkeyPressed();
        emit focus();
    }
    void emitFocus(){
        emit focus();
    }

public slots:
    void start();
    void stop();

signals:
    void stopped();
    void hotkeyPressed();
    void focus();

private:
    explicit InputHandler(QObject *parent = nullptr);

    static std::unordered_set<uint16_t> keys;

    bool startHook();

    bool stopHook();


    static bool logger_proc(unsigned int level, const char *format, ...);

    static void dispatch_proc(uiohook_event * const event);

    static std::unordered_set<uint16_t> hotKey;

signals:
};

#endif // INPUTHANDLER_H
