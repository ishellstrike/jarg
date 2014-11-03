#ifndef PARSER_H
#define PARSER_H
#include <QJsonValue>
#include <QObject>

void perseReq(QJsonValue &val, QObject &prop, QString field)
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

#endif // PARSER_H
