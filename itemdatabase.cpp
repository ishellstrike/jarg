#include "itemdatabase.h"
#include "itemdata.h"
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QtWidgetsDepends>
#include "jscript.h"

void ItemDataBase::load()
{
    QDir items_dir = QDir::current();
    items_dir.cd("data/json/items");
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
        for (int i = 0; i < obj.size(); i++)
        {
            QJsonObject one = obj[i].toObject();

            ItemData temp;
            temp.set_id(one["id"].toString());
            temp.name = one["name"].toString();
            temp.description = one["description"].toString();
            QJsonArray flags = one["flags"].toArray();
            for (int j = 0; j < flags.size(); j++)
            {
                QJsonArray flag = flags[i].toArray();

                Flag fl;
                fl.name = flag[0].toString();
                fl.value = flag[1].toInt();
                temp.flags.push_back(fl);
            }
            data.insert(temp.id(), temp);
        }
        qDebug() << obj.size() << "objects from" << s;
    }
    ItemData d;
    JScript &eng = JScript::Instance();
    QScriptValue ret = eng.engine.evaluate("test.js");
    QScriptValue add = eng.engine.globalObject().property("add");
    QScriptValue dq = eng.engine.newQObject(&d);
    eng.engine.globalObject().setProperty("d", dq);
    ret.call(add, QScriptValueList() << dq);
    data.insert("asd", d);
    qDebug() << d.toString();
    qDebug() << dq.toString();
}

void ItemDataBase::RegisterApi()
{
    api = JScript::Instance().engine.newQObject(this);
    JScript::Instance().engine.globalObject().setProperty("itemDataBase", api);
}

ItemDataBase::ItemDataBase()
{

}
