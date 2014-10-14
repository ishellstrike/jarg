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

    JScript::instance();
    ItemDataBase::instance()->RegisterApi();
    ItemDataBase::instance()->name("apiapiapi");
    BlockDataBase::instance()->load();
    ItemDataBase::instance()->load();

    Sector sec;
    sec.setBlock(0,0,0, "error");
    auto t = sec.getBlock(0,0,0);

    Window window;
    window.show();
    int a = app.exec();

    ItemDataBase::drop();
    BlockDataBase::drop();
    JScript::drop();
    qDebug() << "Jarg End";
    return a;
}
