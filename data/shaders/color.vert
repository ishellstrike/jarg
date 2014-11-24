#version 120

attribute vec3 position;
attribute vec2 texcoord;
//attribute vec3 normal;
attribute vec4 color;

uniform mat4 MVP;

varying vec4 fragColor;

void main(void)
{
    gl_Position = MVP * vec4(position, 1);
    fragColor = color;
}
