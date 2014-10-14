#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H
#include "itemdata.h"
#include "itemrecipe.h"
#include "jscript.h"
#include <QJsonObject>
#include <QHash>
#include <QString>
#include <QScriptValue>
#include <QObject>
#include <QMutex>
#include <qdebug.h>
#include <QScriptEngine>

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
                qDebug() << "making ItemDataBase instance";
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
            qDebug() << "droping ItemDataBase instance";
        }

        QHash<QString, ItemData *> data;
        QHash<QString, Recipe *> recipes;
        Q_PROPERTY(QString name READ name WRITE name)

        void load();

        void RegisterApi();
        QScriptValue api;
        QString name() const
        {
            return m_name;
        }

private:
        ItemDataBase();
        ~ItemDataBase();
        ItemDataBase(const ItemDataBase& root);
        ItemDataBase &operator=(const ItemDataBase&);

        static ItemDataBase *m_inst;
        QString m_name;

public slots:
        QScriptValue newItemData(const QString &id)
        {
            ItemData *idat = new ItemData();
            idat->id(id);
            data.insert(id, idat);
            return JScript::instance()->engine.toScriptValue(idat);
        }
        void name(QString arg)
        {
            m_name = arg;
        }
};

#endif // ITEMDATABASE_H
