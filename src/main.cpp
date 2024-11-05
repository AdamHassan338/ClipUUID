#include "clipuuid.h"
#include <QSharedMemory>
int main(int argc, char *argv[])
{
    ClipUUID app(argc, argv);
    QSharedMemory shared("7fdac389-d15f-4210-9917-766d32cc8778");
    if( !shared.create( 512, QSharedMemory::ReadWrite) )
    {
        qDebug() << "Attempting Restart.";
        shared.attach();
        shared.detach();
        if(!shared.create( 512, QSharedMemory::ReadWrite)){
        qWarning() << "Can't start more than one instance of the application.";
        exit(0);
        }
    }

    qDebug() << "Application started successfully.";

    return app.exec();

}
