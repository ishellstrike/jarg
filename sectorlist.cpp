#include "sectorlist.h"


SectorList::SectorList()
{
}

SectorList::~SectorList()
{
    for(auto a : data)
    {
        delete a;
        a = nullptr;
    }
    qDebug() << data.size() << "sector list destructor";
    data.clear();
}

int SectorList::count()
{
    return data.size();
}
