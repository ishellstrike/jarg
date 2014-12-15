#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMutex>
#include "jmath.h"


class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings *instance()
    {
        static QMutex mutex;
        if(!m_inst)
        {
            mutex.lock();

            if (!m_inst)
                m_inst = new Settings();

            mutex.unlock();
            qDebug() << "making settings instance";
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
        qDebug() << "droping settings instance";
    }
    vec2 resolution = vec2(500, 500);
private:
    static Settings *m_inst;
    Settings();
    ~Settings();
    Settings(const Settings &root);
    Settings &operator=(const Settings &);
};

#endif // SETTINGS_H
