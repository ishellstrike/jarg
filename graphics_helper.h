#ifndef GRAPHICS_HELPER_H
#define GRAPHICS_HELPER_H
#include "jmath.h"
#include "graphics.h"
#include "settings.h"
#define OUTLINE 2
#define RAMK 5
#define HEADER 20

inline void drawLineEx(vec2 loc, vec2 size, col4 col, abstract_engine &eng, float w, int count, ...)
{
    if(count < 2)
        return;

    va_list ap;
    va_start(ap, count);
    vec2 p = va_arg(ap, vec2);
    count--;
    while (count--)
    {
        vec2 pre = p;
        p = va_arg(ap, vec2);

        eng.drawLine(loc + (size * pre), loc + (size * p), w, col);
    }
    va_end(ap);
}

inline void drawOutline(vec2 pos, vec2 size, col4 col, abstract_engine &eng)
{
    eng.drawRect(pos, vec2(size.x(), OUTLINE), col/2);
    eng.drawRect(pos, vec2(OUTLINE, size.y()), col/2);
    eng.drawRect(pos + vec2(0, size.y() - OUTLINE), vec2(size.x(), OUTLINE), col/2);
    eng.drawRect(pos + vec2(size.x() - OUTLINE, 0), vec2(OUTLINE, size.y()), col/2);
}

inline void drawBox(vec2 pos, vec2 size, vec4 col, abstract_engine &eng)
{
    eng.drawRect(pos, size, col);
    drawOutline(pos, size, col, eng);
}

inline void drawBox(vec2 pos, vec2 size, vec4 col, vec4 col2, abstract_engine &eng)
{
    eng.drawRect(pos, size, col, col2);
    drawOutline(pos, size, col, eng);
}

inline void drawBoxScissor(vec2 pos, vec2 size, vec4 col, vec4 col2, abstract_engine &eng)
{
   eng.drawRect(pos, size, col, col2);
  // eng.setScissor(pos + vec2(OUTLINE, OUTLINE), size - vec2(OUTLINE*2, OUTLINE*2));
}

inline void drawBoxScissor(vec2 pos, vec2 size, vec4 col, abstract_engine &eng)
{
   drawBox(pos, size, col, eng);
   //eng.setScissor(pos + vec2(OUTLINE, OUTLINE), size - vec2(OUTLINE*2, OUTLINE*2));
}

#endif // GRAPHICS_HELPER_H
