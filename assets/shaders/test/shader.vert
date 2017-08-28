#version 320 es
in highp vec4 vertAttr;
in highp vec4 texCoord;
uniform highp mat4 matrix;
out highp vec4 coord;

void main(void)
{
    gl_Position = matrix * vertAttr;
    coord=texCoord;
}
