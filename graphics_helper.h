#ifndef GRAPHICS_HELPER_H
#define GRAPHICS_HELPER_H
#include "jmath.h"
#include "graphics.h"
#define OUTLINE 2

inline void drawBoxOutline(vec2 pos, vec2 size, QColor col, abstract_engine &eng)
{
    eng.drawRect(pos, vec2(size.x(), OUTLINE), col);
    eng.drawRect(pos, vec2(OUTLINE, size.y()), col);
    eng.drawRect(pos + vec2(0, size.y() - OUTLINE), vec2(size.x(), OUTLINE), col);
    eng.drawRect(pos + vec2(size.x() - OUTLINE, 0), vec2(OUTLINE, size.y()), col);
}

inline void drawBox(vec2 pos, vec2 size, QColor col, abstract_engine &eng)
{
    eng.drawRect(pos, size, col);
    drawBoxOutline(pos, size, col, eng);
}

inline void drawBoxScissor(vec2 pos, vec2 size, QColor col, abstract_engine &eng)
{
   drawBox(pos, size, col, eng);
   eng.setScissor(pos + vec2(2, 2), size - vec2(4, 4));
}

#endif // GRAPHICS_HELPER_H
