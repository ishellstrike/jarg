#include <QApplication>
#include "window.h"
#include "jlogger.h"
#include "blockdatabase.h"
#include "itemdatabase.h"
#include "jscript.h"
#include "sector.h"
#include "jatlas.h"
#include <QtGlobal>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //qInstallMessageHandler(loggerHandler);
    qDebug() << "Jarg Start";

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(2);
    format.setSamples(4);

    Window window(app.primaryScreen());
    window.setFormat(format);
    window.initialize();
    window.show();
    window.setAnimating(true);
    int a = app.exec();
    qDebug() << "Jarg End";
    return a;
}
