#ifndef CLIPUUID_H
#define CLIPUUID_H

#include <QApplication>

#include <QQmlApplicationEngine>
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


    QThread* inputThread;
    UUIDGenorator* uuidGenorator;
    QQmlApplicationEngine engine;


    QSystemTrayIcon* tray;
    QMenu *trayMenu;
    QAction *quitAction;

    void createActions();

    void createTrayIcon();

};

#endif // CLIPUUID_H
