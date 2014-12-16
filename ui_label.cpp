#include "ui_label.h"
#include "window.h"
#include "graphics_helper.h"

ui_label::ui_label(ui_container *parent) :
    ui_element(parent)
{
    size = vec2(50, 20);
}

void ui_label::render(abstract_engine &eng)
{
    auto pos = get_position();
    eng.drawText(text, pos, vec2(0.33,0.33), RED);
}

void ui_label::update()
{

}

void ui_label::keyEvent(QKeyEvent *key)
{
    Q_UNUSED(key);
}

void ui_label::mousePress(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    emit onPress();
}

void ui_label::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ui_label::mouseDoubleClick(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ui_label::mouseMove(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}


void ui_double_label::render(abstract_engine &eng)
{
    auto pos = get_position();
    eng.drawText(text, pos, vec2(0.33,0.33), RED);
    eng.drawText(text, pos, vec2(0.33,0.33), RED);
}

void ui_double_label::update()
{

}
