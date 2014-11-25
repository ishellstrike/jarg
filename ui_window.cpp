#include "ui_window.h"
#include "window.h"

ui_window::ui_window(ui_element *parent) :
    ui_element(parent)
{
    loc = vec2(10,10);
    size = vec2(200,200);
}

void ui_window::render()
{
    MainWindow::drawer->drawRect(get_position(), vec2(), Qt::white);

    for(ui_element *i : elements)
    {
        i->render();
    }
}

void ui_window::update()
{
    for(ui_element *i : elements)
    {
        i->update();
    }
}


window_system::window_system() :
    ui_element(0)
{

}

void window_system::render()
{
    for(ui_element *i : elements)
    {
        i->render();
    }
}

void window_system::update()
{
    for(ui_element *i : elements)
    {
        i->update();
    }
}

void window_system::init()
{
    addElement(new ui_window(this));
}
