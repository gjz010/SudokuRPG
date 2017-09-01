#ifndef SHADERPACKER_H
#define SHADERPACKER_H
#include <QVector3D>
#include <QVector2D>
#include <QColor>
#include <QVector4D>
/*
in highp vec4 vertAttr;
in highp vec4 texCoord;
uniform highp mat4 matrix;
*/
struct SimpleVertex{
    QVector3D vertAttr;
    QVector2D texCoord;
    QVector4D tone;
    QString toString();
};
/*
in highp vec3 vertAttr;
in highp vec3 vertNormal;
in highp vec2 texCoord;
 */
struct DefaultVertex{
    QVector3D vertAttr;
    QVector3D vertNormal;
    QVector2D texCoord;

};
/*
uniform vec4 posEye;
uniform vec4 posLight;
uniform vec4 colLight;
uniform vec4 emissive;
uniform vec4 diffuse;
//uniform vec4 specular;
//uniform float shininess;
uniform vec4 ambient;
uniform float brightness;
*/
struct DefaultEnv{
    QVector3D posEye;
    QVector3D posLight;
    QColor colLight;
    QVector3D emmisive;
    QVector3D diffuse;
    QVector3D ambient;
    float brightness;

};
#endif // SHADERPACKER_H
