#include "itemdata.h"
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
    scriptFile.close();
}

JScript *JScript::m_inst = nullptr;
