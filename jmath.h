#ifndef JMATH_H
#define JMATH_H

typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;
typedef QColor col4;

inline float dot3( vec3 g, float x, float y, float z )
{
    return g[0] * x + g[1] * y + g[2] * z;
}
inline float dot4 ( vec4 g, float x, float y, float z, float w )
{
    return g[0] * x + g[1] * y + g[2] * z + g[3] * w;
}
inline float dot2 ( vec3 g, float x, float y )
{
    return g[0] * x + g[1] * y;
}

template < typename _Ty >
inline _Ty mix (_Ty x, _Ty y, _Ty a)
{
    return x * (1.0 - a) + y * a;
}

template < typename _Ty >
inline _Ty fade( _Ty t )
{
    return t * t * t * ( t * ( t * 6 - 15 ) + 10 );
}

#endif // JMATH_H
