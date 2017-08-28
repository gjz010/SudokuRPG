#include "sudokuwindow.h"
#include <QOpenGLShaderProgram>
#include <QtOpenGL>
struct SudokuWindow::Internal{
    QOpenGLShaderProgram* prog;
    int huaji;
    //QOpenGLContect* m_context;
};
SudokuWindow::SudokuWindow(QWidget *parent)
{
    setFormat(QSurfaceFormat::defaultFormat());
    this->setWidth(400);
    this->setHeight(600);
    gl=new GLManager(this);
    data=new Internal;
    //data->m_context = new QOpenGLContext;
    create();
}

QSize SudokuWindow::sizeHint() const
{
    return QSize(400,600);
}

SudokuWindow::~SudokuWindow()
{
    delete data;
}

void SudokuWindow::initializeGL()
{

    makeCurrent();
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    QOpenGLShaderProgram* prog=gl->LoadShader("test");
    data->prog=prog;
    //data->vertAttr=prog->attributeLocation("vertAttr");
    //data->vertColorAttr=prog->attributeLocation("vertColorAttr");
    prog->release();
    data->huaji=gl->LoadTexture("huaji");
}

void SudokuWindow::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
}

void SudokuWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    makeCurrent();
    data->prog->bind();
    gl->getProjMatrix().ortho(-1,1,-1,1,1,-1);
    //matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.translate(0, 0, -2);
    data->prog->setUniformValue("matrix",gl->getMatrix());
    //data->prog->setUniformValue("texture",);
    GLfloat vertices[] = {
        0.0f, 1.f, 0.0f,
        -1.f, -1.f, 0.0f,
        1.f, -1.f, 0.0f,
        1.f, 0.f, -1.0f
    };

    GLfloat coords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    data->prog->setAttributeArray("vertAttr",GL_FLOAT,vertices,3,0);
    data->prog->setAttributeArray("texCoord",GL_FLOAT,coords,2,0);
    data->prog->enableAttributeArray("vertAttr");
    data->prog->enableAttributeArray("texCoord");
    gl->getTexture(data->huaji)->bind();
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    data->prog->disableAttributeArray("vertAttr");
    data->prog->disableAttributeArray("texCoord");
    data->prog->release();
}
