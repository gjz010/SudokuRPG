#version 320 es
uniform sampler2D t;
uniform highp float brightness;
uniform bool renderTone;
in highp vec4 coord;
in highp vec4 fragTone;
out highp vec4 vFragColor;
void main(void)
{
    highp vec4 color=texture(t,coord.st);
    if(renderTone){
        color=color*fragTone;
    }
    color=min(color,1.f);
    vFragColor=brightness*color;
}
