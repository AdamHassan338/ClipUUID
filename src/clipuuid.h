#ifndef CLIPUUID_H
#define CLIPUUID_H

#include <QApplication>

#include <QQmlApplicationEngine>
#include <QIcon>
class QMenu;
class QThread;
class QAction;
class UUIDGenorator;
class QSystemTrayIcon;
class ClipUUID : public QApplication
{
public:
    ClipUUID(int &argc, char **argv);
    ~ClipUUID();
    void init();


    QThread* inputThread;
    UUIDGenorator* uuidGenorator;
    QQmlApplicationEngine engine;
    QIcon icon;

    QSystemTrayIcon* tray;
    QMenu *trayMenu;
    QAction *quitAction;
    QAction *headerAction;

    void createActions();

    void createTrayIcon();

};

#endif // CLIPUUID_H
