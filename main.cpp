#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QShortcut>
#include <QKeySequence>
#include "uuidgenorator.h"
#include <QQmlContext>
#include <QSystemTrayIcon>
#include <uiohook.h>
#include <QDebug>
#include <QThread>
#include "inputhandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QThread* inputThread = new QThread();
    InputHandler& inputHandler = InputHandler::getInstance();

    QObject::connect(inputThread,&QThread::started,&inputHandler,&InputHandler::start);
    QObject::connect(&inputHandler,&InputHandler::stopped,inputThread,&QThread::quit);
    UUIDGenorator* uuidGenorator = new UUIDGenorator;


    inputHandler.moveToThread(inputThread);
    QObject::connect(&inputHandler,&InputHandler::hotkeyPressed,uuidGenorator,&UUIDGenorator::generateUuid,Qt::QueuedConnection);
    inputThread->start();





    // Create a QShortcut objec
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);



    // Expose the instance to QML
    engine.rootContext()->setContextProperty("uuuidGenorator", uuidGenorator);
    engine.rootContext()->setContextProperty("inputHandler", &inputHandler);


    engine.loadFromModule("uuid", "Main");

    QSystemTrayIcon* tray = new QSystemTrayIcon();
    tray->show();
    return app.exec();
}
