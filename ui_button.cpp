#include "ui_button.h"
#include "window.h"

ui_button::ui_button(ui_element *parent) :
    ui_element(parent)
{
}

void ui_button::render()
{
    MainWindow::drawer->drawRect(get_position(), vec2(), Qt::blue);
}

void ui_button::update()
{

}
