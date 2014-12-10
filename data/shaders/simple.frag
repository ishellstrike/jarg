#version 120

uniform sampler2D colorTexture;
varying vec2 fragTexcoord;

void main(void)
{
    gl_FragColor = vec4(0, 0, 0, texture2D(colorTexture, fragTexcoord).a);
}
