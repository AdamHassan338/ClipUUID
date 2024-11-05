#include "clipuuid.h"

#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    ClipUUID app(argc, argv);

    bool isRunning = false;
    QSharedMemory shared("43d93d12-aebd-4e04-8a7f-60a1b532d17c");

    if( !shared.create( 512, QSharedMemory::ReadWrite) )
    {
        qDebug() << "Attempting Restart.";
        shared.attach();
        shared.detach();
        if(!shared.create( 512, QSharedMemory::ReadWrite)){
            isRunning = true;
            qWarning() << "Can't start more than one instance of the application.";
        }
    }

    if(isRunning){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("ClipUUID Is Already Running!");
        msgBox.setInformativeText("Click OK to exit.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        if (msgBox.exec() == QMessageBox::Ok) {
            exit(0);
        }
    }

    qDebug() << "Application started successfully.";

    app.init();

    return app.exec();

}
