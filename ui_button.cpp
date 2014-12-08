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
    drawBox(pos, size, !aimed ? LIGHTGRAY : WHITE, eng);
}

void ui_button::update()
{

}

void ui_button::keyEvent(QKeyEvent *key)
{

}

void ui_button::mousePress(QMouseEvent *mouse)
{
    emit onPress();
}

void ui_button::mouseRelease(QMouseEvent *mouse)
{

}

void ui_button::mouseDoubleClick(QMouseEvent *mouse)
{

}

void ui_button::mouseMove(QMouseEvent *mouse)
{

}


ui_close_button::ui_close_button(ui_element *parent) :
    ui_button(parent)
{

}

void ui_close_button::render(abstract_engine &eng)
{
    ui_button::render(eng);
    auto p = get_position();
    eng.drawLine(p, p + size, 2, LIGHTGRAY/2);
    eng.drawLine(p + vec2(0, size.y()), p + vec2(size.x(), 0), 2, LIGHTGRAY/2);
}
