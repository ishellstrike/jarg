#include "blockdatabase.h"
#include "QJsonExtension.h"
#include "jscript.h"

void BlockDataBase::load()
{
    BlockData* a = new BlockData(this);
    a->set_id("error");
    data.insert("error", a);
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
