#include "clipuuid.h"

#include "uuidgenorator.h"
#include "inputhandler.h"

#include <QQmlContext>
#include <QSystemTrayIcon>
#include <QThread>
#include <QMenu>
#include <QAction>

ClipUUID::ClipUUID(int &argc, char **argv) : QApplication(argc, argv) {

    inputThread = new QThread();
    InputHandler& inputHandler = InputHandler::getInstance();

    QObject::connect(inputThread,&QThread::started,&inputHandler,&InputHandler::start);
    QObject::connect(&inputHandler,&InputHandler::stopped,inputThread,&QThread::quit);
    uuidGenorator = new UUIDGenorator;

    inputHandler.moveToThread(inputThread);
    QObject::connect(&inputHandler,&InputHandler::hotkeyPressed,uuidGenorator,&UUIDGenorator::generateUuid,Qt::QueuedConnection);
    QObject::connect(&inputHandler,&InputHandler::focus,uuidGenorator,&UUIDGenorator::requestFocus,Qt::QueuedConnection);

    inputThread->start();



    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        this,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    engine.rootContext()->setContextProperty("uuuidGenorator", uuidGenorator);
    engine.rootContext()->setContextProperty("inputHandler", &inputHandler);
    engine.loadFromModule("clipuuid", "Main");
    createActions();
    createTrayIcon();
    tray->show();
}

void ClipUUID::createActions(){
    headerAction = new QAction("ClipUUID",this);
    headerAction->setDisabled(true);
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

}

void ClipUUID::createTrayIcon(){
    trayMenu = new QMenu();
    trayMenu->addSection("ClipUUID");
    trayMenu->addAction(headerAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);
    icon = QIcon(":/icons/icon.png");
    tray = new QSystemTrayIcon();
    tray->setIcon(icon);
    tray->setContextMenu(trayMenu);

}

ClipUUID::~ClipUUID()
{
    InputHandler::getInstance().stop();
    if(inputThread->isRunning()){
        inputThread->quit();
    }
    inputThread->wait();

    delete uuidGenorator;
    uuidGenorator = nullptr;

    delete inputThread;
    inputThread = nullptr;

    QSystemTrayIcon* tray;
    QMenu *trayMenu;
    QAction *quitAction;

    delete tray;
    tray = nullptr;

    delete trayMenu;
    trayMenu = nullptr;

    delete quitAction;
    quitAction = nullptr;

}
