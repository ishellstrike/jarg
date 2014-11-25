#include "ui_container.h"

ui_container::ui_container()
{
}

ui_container::~ui_container()
{
    qDebug() << "container";
    for(ui_element *i : elements)
    {
        delete i;
    }
    elements.clear();
}

void ui_container::addElement(ui_element *element)
{
    elements.push_back(element);
}

ui_element::ui_element(ui_element *par) : ui_parent(par)
{
}

ui_element::~ui_element()
{
    qDebug() << "elemtnt";
}

vec2 ui_element::get_position()
{
    if(ui_parent)
    {
        ui_parent->loc + loc;
    }
    return loc;
}
