#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMutex>
#include "jmath.h"
#define OUTLINE 2
#define HEADER 20

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
    QSize resolution = QSize(500, 500);
    QColor ui_body = Qt::lightGray;
    QColor ui_header = Qt::gray;
    QColor ui_outline = Qt::black;
private:
    static Settings *m_inst;
    Settings();
    ~Settings();
    Settings(const Settings &root);
    Settings &operator=(const Settings &);
};

#endif // SETTINGS_H
