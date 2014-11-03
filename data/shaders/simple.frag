#version 330 core

#define VERT_POSITION 0
#define VERT_TEXCOORD 1
#define VERT_NORMAL 2
#define VERT_COLOR 3
#define FRAG_OUTPUT0 0

uniform sampler2D colorTexture;
in vec2 fragTexcoord;

void main(void)
{
    vec4 color = texture2D(colorTexture, fragTexcoord);
    gl_FragColor = color;
}
