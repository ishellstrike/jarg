#version 120

uniform sampler2D colorTexture;
varying vec2 fragTexcoord;

void main(void)
{
    vec4 color = texture2D(colorTexture, fragTexcoord);
    gl_FragColor = color;
}
