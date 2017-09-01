#version 320 es
uniform sampler2D t;
in highp vec4 fragPosition;
in highp vec4 fragNormal;
in highp vec2 fragCoord;
uniform highp vec4 posEye;
uniform highp vec4 posLight;
uniform highp vec4 colLight;
uniform highp vec4 emissive;
uniform highp vec4 diffuse;
//uniform vec4 specular;
//uniform float shininess;
uniform highp vec4 ambient;
uniform highp float brightness;
out highp vec4 vFragColor;
void main(void)
{
    //Only considering emissive, diffuse and ambient.
    highp vec4 l1=emissive;
    highp vec4 normal=normalize(fragNormal);
    highp vec4 light_ray=normalize(posLight-fragPosition);
    //vec4 eyesight=normalize(posEye-fragPosition);
    //vec4 aver=normalize(light_ray+eyesight);
    highp vec4 reflection=reflect(-light_ray,normal);
    highp vec4 l2=max(dot(normal,light_ray),0.0f)*colLight*diffuse;
    //vec4 l3=pow(max(dot(reflection,eyesight),0)*colLight*specular);
    highp vec4 total_light=l1+l2+ambient; //ignoring specular
    vFragColor=brightness*total_light*texture(t,fragCoord.st);
}
