#ifndef JSCRIPT_H
#define JSCRIPT_H
#include <QMutex>
#include <QScriptEngine>
#include <qdebug.h>

class JScript
{
public:
    QScriptEngine engine;

    void runString(const QString &s);

    void runScript(const QString &s);

    static JScript *instance()
    {
        static QMutex mutex;
        if(!m_inst)
        {
            mutex.lock();

            if (!m_inst)
                m_inst = new JScript();

            mutex.unlock();
            qDebug() << "making JScript instance";
        }
        return m_inst;
    }

    static void drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_inst;
        m_inst = nullptr;
        mutex.unlock();
        qDebug() << "droping JScript instance";
    }

private:
    JScript();
    JScript(const JScript& root);
    JScript& operator=(const JScript&);

    static JScript *m_inst;
};

#endif // JSCRIPT_H
