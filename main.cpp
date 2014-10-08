#include <QApplication>
#include "window.h"
#include "jlogger.h"
#include "blockdatabase.h"
#include <QtGlobal>


int main(int argc, char *argv[])
{
    qInstallMessageHandler(loggerHandler);
    qDebug() << "Jarg Start";

    BlockDataBase::Instance().load();

    QApplication app(argc, argv);
    Window window;
    window.show();
    int a = app.exec();
    qDebug() << "Jarg End";
    return a;
}
