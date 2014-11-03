#include "agent.h"

#include <QString>

Agent::Agent()
{

}

QString Agent::name()
{
    return "blank";
}

QString Agent::fullName()
{
    if(parent == nullptr)
    {
        name();
    }
    return parent->name() + "." + name();
}

QVector<Agent *> Agent::getBrothers()
{
    if(parent == nullptr)
    {
        return QVector<Agent*>();
    }

    return parent->childrens;
}


QString BaseBlockAgent::name()
{
    return "block";
}


QString BaseCreatureAgent::name()
{
    return "creature";
}


QString BaseItemAgent::name()
{
    return "item";
}


BaseObjectInfo::BaseObjectInfo() :
    id("error")
{

}


ClothAgent::ClothAgent() :
    parts(0)
{

}

void ClothAgent::Destroy()
{
    parts = 0;
}
