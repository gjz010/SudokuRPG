#version 320 es
in highp vec3 vertAttr;
in highp vec3 vertNormal;
in highp vec2 texCoord;
uniform highp mat4 matrix;
out highp vec4 fragPosition;
out highp vec4 fragNormal;
out highp vec2 fragCoord;
void main(void)
{
    gl_Position = matrix * vec4(vertAttr,1);
    fragPosition=matrix*vec4(vertAttr,1);
    fragNormal=matrix*vec4(vertNormal,0);
    fragCoord=texCoord;
}
