#ifndef PARSER_H
#define PARSER_H
#include "itemdata.h"

#include <QDir>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>


void parse(QJsonValue &val, QObject &prop, QString field)
{
    if(val.isObject())
    {
        auto arr = val.toObject();
        auto keys = arr.keys();
        for(auto i: keys)
        {
            //QMetaProperty prop_ref = prop.read(nullptr);
            //QJsonValue val_r = arr[i];
            //perseReq();
        }
        qDebug() << "recursive";
    } else
    {
        if(!prop.setProperty(field.toStdString().c_str(), val.toVariant()))
        {
            qDebug() << "property error" << val.toVariant() << "to" << field;
        }
    }
}


template<class T>
void parseArray(QHash<QString, T*> &db, QJsonArray &obj, QString s)
{
    for (int i = 0; i < obj.size(); i++)
    {
        QJsonObject one = obj[i].toObject();

        T *temp = new T();
        auto fields = one.keys();
        for(QString field: fields)
        {
            QJsonValue value = ((QJsonValue)one[field]);
            parse(value, *temp, field);
        }
        if(((ObjectData*)temp)->id() == "") {
            qDebug() << s << "some object has no id";
            continue;
        }
        db.insert(((ObjectData*)temp)->id(), temp);
    }
}

template<class T>
void parseDir(QHash<QString, T*> &db, QString subdir)
{
    QDir items_dir = QDir::current();
    items_dir.cd(subdir);
    QStringList files = items_dir.entryList(QStringList("*.json"));
    for(QString s : files)
    {
        QString ss = items_dir.path() + "/" + s;
        QFile file(ss);
        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();
        QJsonDocument json(QJsonDocument::fromJson(array));
        file.close();
        QJsonArray obj = json.array();
        parseArray(db, obj, s);
        qDebug() << obj.size() << typeid(T).name() << "objects from" << s;
    }
}

#endif // PARSER_H
