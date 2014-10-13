#include <QApplication>
#include "window.h"
#include "jlogger.h"
#include "blockdatabase.h"
#include "itemdatabase.h"
#include "jscript.h"
#include "sector.h"
#include <QtGlobal>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qInstallMessageHandler(loggerHandler);
    qDebug() << "Jarg Start";

    JScript::Instance();
    ItemDataBase::instance()->RegisterApi();
    BlockDataBase::instance()->load();
    ItemDataBase::instance()->load();

    Sector sec;
    sec.setBlock(0,0,0, "error");
    auto t = sec.getBlock(0,0,0);

    Window window;
    window.show();
    int a = app.exec();

    BlockDataBase::drop();
    ItemDataBase::drop();
    qDebug() << "Jarg End";
    return a;
}
