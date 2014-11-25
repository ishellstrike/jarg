#include "ui_window.h"
#include "window.h"

ui_window::ui_window(ui_element *parent) :
    ui_element(parent)
{
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

}
