#include <QApplication>
#include "jlogger.h"
#include "blockdatabase.h"
#include "itemdatabase.h"
#include "jscript.h"
#include "sector.h"
#include "jatlas.h"
#include "glwidget.h"
#include <QtGlobal>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //qInstallMessageHandler(loggerHandler);
    qDebug() << "Jarg Start";


    glwidget g;
    g.show();
    int a = app.exec();
    qDebug() << "Jarg End";
    return a;
}
