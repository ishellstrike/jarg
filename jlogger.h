#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QCoreApplication>
#include <QtGlobal>
#include <QFile>
#include <QTime>

void loggerHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile file("application.log");
    if(!file.exists("application.log"))
        file.open(QIODevice::WriteOnly | QIODevice::Text);
    else
        file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);

    QString mT = "";
    switch(type)
    {
        case QtDebugMsg: mT="D"; break;
        case QtWarningMsg: mT="W"; break;
        case QtCriticalMsg: mT="C"; break;
        case QtFatalMsg: mT="F"; break;

        default: mT="System Message";
    }
    QDate date = QDate::currentDate();
    out << QString("%1 %2 ").arg(mT).arg(date.toString());
    out << QString("%1.%2 ").arg(QTime::currentTime().toString()).arg(QTime::currentTime().msec());
    out << QString("%5:%6] %7\n").arg(context.file).arg(context.line).arg(msg);
    if(msg.contains("\n"))
    {
        out << "\n";
    }

    file.close();
    return;
}

#endif // LOGGER_H
