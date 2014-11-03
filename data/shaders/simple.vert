#version 330 core

#define VERT_POSITION 0
#define VERT_TEXCOORD 1
#define VERT_NORMAL 2
#define VERT_COLOR 3
#define FRAG_OUTPUT0 0

layout(location = VERT_POSITION) in vec3 position;
layout(location = VERT_TEXCOORD) in vec2 texcoord;
layout(location = VERT_NORMAL) in vec3 normal;
uniform mat4 qt_ModelViewProjectionMatrix;
varying vec2 qt_TexCoord0;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * vec4(position, 1);
    qt_TexCoord0 = texcoord;
}
