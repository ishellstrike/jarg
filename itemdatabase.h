#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H
#include "itemdata.h"
#include <QJsonObject>
#include <QMap>
#include <QString>

class ItemDataBase
{
public:
        static ItemDataBase& Instance()
        {
                static ItemDataBase theSingleInstance;
                return theSingleInstance;
        }

        QMap<QString, ItemData> data;

        void load();

private:
        ItemDataBase(){};
        ItemDataBase(const ItemDataBase& root);
        ItemDataBase& operator=(const ItemDataBase&);

        void write(QJsonObject &json);
};

#endif // ITEMDATABASE_H
