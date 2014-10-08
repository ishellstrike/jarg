#include "blockdatabase.h"
#include "QJsonExtension.h"

void BlockDataBase::write(QJsonObject &json)
{
    for(BlockData part : data)
    {
        json["id"] = part.id;
        json["name"] = part.name;
        json["description"] = part.description;
        json["color"] = toJson(part.color);
    }
}

void BlockDataBase::load()
{
    BlockData a = BlockData();
    a.id = "asdasd";
    data.push_back(a);

    QFile saveFile("save.json");
    saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}
