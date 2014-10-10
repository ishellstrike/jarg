#ifndef JSCRIPT_H
#define JSCRIPT_H
#include <QScriptEngine>

class JScript
{
public:
    QScriptEngine engine;

    void runString(const QString &s);

    void runScript(const QString &s);

    static JScript& Instance()
    {
            static JScript theSingleInstance;
            return theSingleInstance;
    }

private:
    JScript();
    JScript(const JScript& root);
    JScript& operator=(const JScript&);
};

#endif // JSCRIPT_H
