#version 330 core

#define VERT_POSITION 0
#define VERT_TEXCOORD 1
#define VERT_NORMAL 2
#define VERT_COLOR 3
#define FRAG_OUTPUT0 0

layout(location = VERT_POSITION) in vec3 position;
layout(location = VERT_TEXCOORD) in vec2 texcoord;
layout(location = VERT_NORMAL) in vec3 normal;

uniform mat4 MVP;

out vec2 fragTexcoord;

void main(void)
{
    gl_Position = MVP * vec4(position, 1);
    fragTexcoord = texcoord;
}
