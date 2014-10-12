#include "blockdatabase.h"
#include "QJsonExtension.h"
#include "jscript.h"

void BlockDataBase::load()
{
    BlockData a;
    a.set_id("asdasd");
    data.insert("1", a);

    QFile saveFile("save.json");
    saveFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonObject gameObject;
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

    JScript::Instance().runScript("test.js");
}

BlockDataBase::BlockDataBase()
{

}

BlockDataBase::BlockDataBase(const BlockDataBase &root)
{

}
