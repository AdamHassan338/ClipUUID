#ifndef CLIPUUID_H
#define CLIPUUID_H

#include <QApplication>

#include <QQmlApplicationEngine>
#include <QIcon>
class QMenu;
class QDialog;
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
    QIcon qtIcon;

    QSystemTrayIcon* tray;
    QMenu *trayMenu;
    QAction *quitAction;
    QAction *qtAction;
    QAction *headerAction;

    QDialog* about;

    void createActions();

    void createTrayIcon();

public slots:
    void showAbout();

};

#endif // CLIPUUID_H
