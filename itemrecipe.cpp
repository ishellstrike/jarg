#include "itemrecipe.h"

Recipe::Recipe() :
    exact_items(),
    flag_items(),
    reqire(),
    m_name(),
    m_description(),
    m_id(),
    result()
{

}

Recipe &Recipe::operator=(const Recipe &val)
{
    if (this != &val)
    {
        m_id = val.m_id;
        m_name = val.m_name;
        m_description = val.m_description;
        exact_items = val.exact_items;
        flag_items = val.flag_items;
        reqire = val.reqire;
        result = val.result;
    }
    return *this;
}

Recipe::Recipe(const Recipe &val) :
       exact_items(val.exact_items),
       flag_items(val.flag_items),
       reqire(val.reqire),
       m_name(val.m_name),
       m_description(val.m_description),
       m_id(val.m_id),
       result(val.result)
{

}

void Recipe::addExact(QString name, int count)
 {
     Flag a;
     a.name(name);
     a.value(count);
     exact_items.push_back(a);
}

void Recipe::addResult(QString name, int count)
{
    Flag a;
    a.name(name);
    a.value(count);
    result.push_back(a);
}

void Recipe::addRequire(QString name, int count)
{
    Flag a;
    a.name = name;
    a.value = count;
    reqire.push_back(a);
}

void Recipe::addFlag(QString name, int count, int quality)
{
    RPart a;
    a.name = name;
    a.count = count;
    a.quality = quality;
    flag_items.push_back(a);
}
