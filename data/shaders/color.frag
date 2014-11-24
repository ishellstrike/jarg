#version 120

varying vec4 fragColor;

void main(void)
{
    vec4 color = fragColor;
    gl_FragColor = color;
}
