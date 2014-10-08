#ifndef QJSONEXTENSION_H
#define QJSONEXTENSION_H
#include <QColor>
#include <QJsonObject>

QJsonObject toJson(const QColor &val)
{
    auto a = QJsonObject();
    a["r"] = val.red();
    a["g"] = val.green();
    a["b"] = val.blue();
    a["a"] = val.alpha();
    return a;
}

#endif // QJSONEXTENSION_H
