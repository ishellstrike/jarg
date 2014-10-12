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
                temp.id(one["id"].toString());
                temp.name(one["name"].toString());
                temp.description(one["description"].toString());
                temp.weight(one["weight"].toInt());
                QJsonArray flags = one["flags"].toArray();
                for (int j = 0; j < flags.size(); j++)
                {
                    QJsonArray flag = flags[i].toArray();

                    Flag fl;
                    fl.name = flag[0].toString();
                    fl.value = flag[1].toInt();
                    temp.flags.push_back(fl);
                }
                if(temp.id() == "") {
                    qDebug() << s << "some object has no id";
                    continue;
                }
                data.insert(temp.id(), temp);
            }
            qDebug() << obj.size() << "objects from" << s;
        }
    }

    {
        QDir items_dir = QDir::current();
        items_dir.cd("data/js/items");
        QStringList files = items_dir.entryList(QStringList("*.js"));
        int ok = 0;
        for(QString s : files)
        {
            QString scriptFileName(items_dir.path() + "/" + s);
            QFile scriptFile(scriptFileName);
            scriptFile.open(QIODevice::ReadOnly);
            QString readed = scriptFile.readAll();
            scriptFile.close();
            ItemData d;
            JScript &eng = JScript::Instance();
            QScriptValue dq = eng.engine.newQObject(&d);
            QScriptValue ret = eng.engine.evaluate(readed);
            QScriptValue add = eng.engine.globalObject().property("set");
            ret.call(add, QScriptValueList() << dq);
            if(d.id() == "") {
                qDebug() << s << " error";
                continue;
            }
            ok++;
            data.insert(d.id(), d);
        }
        qDebug() << ok << "objects from js";
    }
}

void ItemDataBase::RegisterApi()
{
    api = JScript::Instance().engine.newQObject(this);
    JScript::Instance().engine.globalObject().setProperty("itemDataBase", api);
}

ItemDataBase::ItemDataBase()
{

}

ItemDataBase::ItemDataBase(const ItemDataBase &root)
{

}

ItemDataBase &ItemDataBase::operator=(const ItemDataBase &)
{

}
