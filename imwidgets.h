#ifndef IMWIDGETS_H
#define IMWIDGETS_H
#include <vector>
#include <QVector2D>
#include "scenes/shaderpacker.h"
#include "glmanager.h"
#include "simpleinputmanager.h"
#include <QOpenGLBuffer>
/*
 * Singleton for create Immediate Widgets.
 * Not at all thread-safe.
 */
class IMWidgets
{
public:
    static void init(GLManager* gl,SimpleInputManager* input);
    static int Button(QRectF rect,QRectF tex_up,QRectF tex_down,float z,QVector4D tone={1.f,1.f,1.f,1.f});
    static void Sprite(QRectF rect,QRectF texcoord,float z,QVector4D tone={1.f,1.f,1.f,1.f});
    static void Shape(QVector2D pos[],QVector2D tex[],int len,float z,QVector4D tone={1.f,1.f,1.f,1.f});
    static int MouseArea(QRectF rect,float z);
    static int MouseArea(QVector2D pos[],float z);
    static const SimpleVertex* list();
    static int refresh(QOpenGLBuffer*);
private:
    IMWidgets();
};

#endif // IMWIDGETS_H
