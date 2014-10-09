#include <QApplication>
#include "window.h"
#include "jlogger.h"
#include "blockdatabase.h"
#include "itemdatabase.h"
#include <QtGlobal>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qInstallMessageHandler(loggerHandler);
    qDebug() << "Jarg Start";

    BlockDataBase::Instance().load();
    ItemDataBase::Instance().load();

    Window window;
    window.show();
    int a = app.exec();
    qDebug() << "Jarg End";
    return a;
}
