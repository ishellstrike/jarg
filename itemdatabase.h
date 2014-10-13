#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H
#include "itemdata.h"
#include "itemrecipe.h"
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QScriptValue>
#include <QObject>
#include <QMutex>

class ItemDataBase : public QObject
{
        Q_OBJECT
public:
        static ItemDataBase *instance()
        {
            static QMutex mutex;
            if(!m_inst)
            {
                mutex.lock();

                if (!m_inst)
                    m_inst = new ItemDataBase();

                mutex.unlock();
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
        }

        QMap<QString, ItemData> data;
        QMap<QString, Recipe> recipes;

        void load();

        void RegisterApi();
        QScriptValue api;
private:
        ItemDataBase();
        ItemDataBase(const ItemDataBase& root);
        ItemDataBase &operator=(const ItemDataBase&);

        static ItemDataBase *m_inst;
};

#endif // ITEMDATABASE_H
