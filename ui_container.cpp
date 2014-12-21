#include "ui_container.h"

ui_container::ui_container(ui_container *par) :
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

void ui_container::mousePress(QMouseEvent *mouse)
{
    for(int cou = elements.size() - 1; cou >=0; cou--)
    {
        auto i = elements[cou];

        auto p = i->get_position();
        QRect rect(p, i->size);
        if(rect.contains(mouse->pos()))
        {
            for(int j = cou; j < elements.size() - 1; j++)
            {
                std::swap(elements[j], elements[j + 1]);
            }
            i->mousePress(mouse);
            break;

        }
    }
}

void ui_container::mouseRelease(QMouseEvent *mouse)
{
    for(ui_element *i : elements)
    {
        i->mouseRelease(mouse);
    }
}

void ui_container::mouseDoubleClick(QMouseEvent *mouse)
{
    for(ui_element *i : elements)
    {
        if(QRect(get_position(), size).contains(mouse->pos()))
        {
            i->mouseDoubleClick(mouse);
            break;
        }
    }
}

void ui_container::mouseMove(QMouseEvent *mouse)
{
    for(ui_element *i : elements)
    {
        if(QRect(i->get_position(), i->size).contains(mouse->pos()))
            i->aimed = true;
        else
            i->aimed = false;

        i->mouseMove(mouse);
    }
}

void ui_container::render(QPainter &eng)
{
    for(ui_element *i : elements)
    {
        i->render(eng);
    }
}

void ui_container::update()
{
    for(ui_element *i : elements)
    {
        i->update();
    }
}

void ui_container::keyEvent(QKeyEvent *key)
{
    Q_UNUSED(key);
}

ui_element::ui_element(ui_container *par) :
    ui_parent(par),
    QObject(par),
    aimed(false)
{
    if(par)
    {
        par->addElement(this);
    }
}

ui_element::~ui_element()
{
}

QPoint ui_element::get_position()
{
    if(ui_parent)
    {
        return ui_parent->loc + loc;
    }
    return loc;
}
