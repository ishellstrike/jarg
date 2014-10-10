#include "jscript.h"

#include <QFile>
#include <QDebug>

JScript::JScript() :
    engine ()
{

}

void JScript::runString(const QString &s)
{
    QScriptValue ret = engine.evaluate(s);
    if (engine.hasUncaughtException()) {
         int line = engine.uncaughtExceptionLineNumber();
         qDebug() << "uncaught exception at line" << line << ":" << ret.toString();
    }
}

void JScript::runScript(const QString &s)
{
    QScriptEngine engine;
    QString scriptFileName(s);
    QFile scriptFile(scriptFileName);
    scriptFile.open(QIODevice::ReadOnly);
    QString readed = scriptFile.readAll();
    QScriptValue fun = engine.evaluate(readed, scriptFileName);
    QScriptValueList args;
    args << 1 << 2;
    int ret = fun.call(QScriptValue(), args).toInt32();
    if (engine.hasUncaughtException()) {
         int line = engine.uncaughtExceptionLineNumber();
         qDebug() << "uncaught exception at line" << line << ":" << ret;
    }
    scriptFile.close();
}
