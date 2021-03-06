#ifndef JMATH_H
#define JMATH_H
#include <QtOpenGL>

typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;
typedef vec4 col4;

#define RED vec4(1,0,0,1)
#define WHITE vec4(1,1,1,1)
#define BLACK vec4(0,0,0,1)
#define LIGHTGRAY vec4(0.8,0.8,0.8,1)
template < typename T >
inline uint vec2hash(T x, T y)
{
    return x + (y << 16);
}

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

template < typename T >
inline T max(T a, T b)
{
    return a > b ? a : b;
}

template < typename T >
inline T min(T a, T b)
{
    return a < b ? a : b;
}

#endif // JMATH_H
