#include "ui_button.h"
#include "window.h"
#include "graphics_helper.h"

ui_button::ui_button(ui_container *parent) :
    ui_element(parent)
{
    size = vec2(50, 20);
}

void ui_button::render(abstract_engine &eng)
{
    auto pos = get_position();
    drawBox(pos, size, !aimed ? LIGHTGRAY : WHITE, eng);
    if(!text.isEmpty())
        eng.drawText(text, pos + vec2(3, -5), vec2(0.33,0.33), BLACK);
}

void ui_button::update()
{

}

void ui_button::keyEvent(QKeyEvent *key)
{
    Q_UNUSED(key);
}

void ui_button::mousePress(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    emit onPress();
}

void ui_button::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ui_button::mouseDoubleClick(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ui_button::mouseMove(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}


ui_close_button::ui_close_button(ui_container *parent) :
    ui_button(parent)
{

}

void ui_close_button::render(abstract_engine &eng)
{
    ui_button::render(eng);
    auto p = get_position();
    drawLineEx(p, size - vec2(1, 0), LIGHTGRAY/2, eng, 2, 3, vec2(0, 0), vec2(0.5, 0.5), vec2(1, 0));
    drawLineEx(p, size - vec2(1, 0), LIGHTGRAY/2, eng, 2, 3, vec2(0, 1), vec2(0.5, 0.5), vec2(1, 1));
}
