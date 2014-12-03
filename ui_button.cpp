#include "ui_button.h"
#include "window.h"
#include "graphics_helper.h"

ui_button::ui_button(ui_element *parent) :
    ui_element(parent)
{
    size = vec2(50, 20);
}

void ui_button::render(abstract_engine &eng)
{
    auto pos = get_position();
    drawBox(pos, size, Qt::white, eng);
}

void ui_button::update()
{

}
