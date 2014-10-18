#include "blockdatabase.h"
#include "QJsonExtension.h"
#include "jscript.h"

void BlockDataBase::load()
{
    {
        QDir items_dir = QDir::current();
        items_dir.cd("data/js/blocks");
        QStringList files = items_dir.entryList(QStringList("*.js"));
        int ok = 0;
        for(QString s : files)
        {
            QString scriptFileName(items_dir.path() + "/" + s);
            QFile scriptFile(scriptFileName);
            scriptFile.open(QIODevice::ReadOnly);
            QString readed = scriptFile.readAll();
            scriptFile.close();
            BlockData *d = new BlockData();
            JScript *eng = JScript::instance();
            QScriptValue dq = eng->engine.newQObject(d);
            QScriptValue ret = eng->engine.evaluate(readed);
            QScriptValue add = eng->engine.globalObject().property("set");
            ret.call(add, QScriptValueList() << dq);
            if(d->id() == "") {
                qDebug() << s << " error";
                continue;
            }
            ok++;
            data.insert(d->id(), d);
        }
        qDebug() << ok << "blocks from js";
    }
}

void BlockDataBase::RegisterApi()
{
    api = JScript::instance()->engine.newQObject(this);
    JScript::instance()->engine.globalObject().setProperty("blockDataBase", api);
}

BlockDataBase::BlockDataBase()
{

}

BlockDataBase::~BlockDataBase()
{
    for(BlockData* t : data)
    {
        delete t;
    }
}

BlockDataBase::BlockDataBase(const BlockDataBase &root)
{

}

BlockDataBase *BlockDataBase::m_inst = nullptr;
