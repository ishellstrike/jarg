#include "ui_container.h"

ui_container::ui_container(ui_element *par) :
    elements(),
    ui_element(par)
{
}

ui_container::~ui_container()
{
}

void ui_container::addElement(ui_element *element)
{
    elements.push_back(element);
}

ui_element::ui_element(ui_element *par) :
    ui_parent(par),
    QObject(par)
{
}

ui_element::~ui_element()
{
}

vec2 ui_element::get_position()
{
    if(ui_parent)
    {
        return ui_parent->loc + loc;
    }
    return loc;
}
