#version 320 es
uniform sampler2D t;
in highp vec4 coord;
out highp vec4 vFragColor;
void main(void)
{

    vFragColor=texture(t,coord.st);
}
