#version 120

uniform sampler2D colorTexture;
varying vec2 fragTexcoord;
varying vec4 col;

void main(void)
{
    gl_FragColor = col * vec4(1, 1, 1,  texture2D(colorTexture, fragTexcoord).a);
}
