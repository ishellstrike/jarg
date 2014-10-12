#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H
#include "itemdata.h"
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QScriptValue>
#include <QObject>

class ItemDataBase : public QObject
{
        Q_OBJECT
public:
        static ItemDataBase& Instance()
        {
                static ItemDataBase theSingleInstance;
                return theSingleInstance;
        }

        QMap<QString, ItemData> data;

        void load();

        void RegisterApi();
        QScriptValue api;
private:
        ItemDataBase();
        ItemDataBase(const ItemDataBase& root);
        ItemDataBase &operator=(const ItemDataBase&);
};

#endif // ITEMDATABASE_H
