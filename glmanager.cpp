#include "glmanager.h"
#include <QFile>
#include <QTextStream>
#include <utility>

GLManager::GLManager(QObject *parent) : QObject(parent)
{
    matrix_modelview.push(QMatrix4x4());
    matrix_projection.push(QMatrix4x4());
}

QOpenGLShaderProgram* GLManager::LoadShader(const QString &name)
{
    QOpenGLShaderProgram* prog=new QOpenGLShaderProgram(this);
    prog->addShaderFromSourceFile(QOpenGLShader::Vertex,":/assets/shaders/"+name+"/shader.vert");
    prog->addShaderFromSourceFile(QOpenGLShader::Fragment,":/assets/shaders/"+name+"/shader.frag");
    prog->link();
    shaders.insert(std::make_pair(name,prog));
    return prog;
}

int GLManager::LoadShaderAttribute(const QString &shader_name, const QString &attr, const QOpenGLShaderProgram *shader)
{
    if(shader==nullptr) shader=getShader(shader_name);
    int arg=shader->attributeLocation(attr);
    shader_attr.insert(std::make_pair(shader_name+"|"+attr,arg));
    return arg;
}

QOpenGLShaderProgram *GLManager::getShader(const QString &name)
{
    return shaders.at(name);
}

void GLManager::popMVMatrix()
{
    matrix_projection.pop();
}

void GLManager::popProjMatrix()
{
    matrix_projection.pop();
}

void GLManager::pushMVMatrix()
{
    matrix_modelview.push(matrix_modelview.top());
}

void GLManager::pushProjMatrix()
{
    matrix_projection.push(matrix_projection.top());
}

QMatrix4x4 &GLManager::getMVMatrix() const
{
    QMatrix4x4& mat=(QMatrix4x4&)matrix_modelview.top();
    return mat;
}

QMatrix4x4 &GLManager::getProjMatrix() const
{
    return (QMatrix4x4&)matrix_projection.top();
}

QMatrix4x4 GLManager::getMatrix() const
{
    return getProjMatrix()*getMVMatrix();
}

QOpenGLTexture *GLManager::getTexture(int idx) const
{
    return textures[idx];
}

int GLManager::LoadTexture(const QString &name)
{
    int idx=textures.size();
    QOpenGLTexture* texture=new QOpenGLTexture(QImage(QString(":/assets/images/%1.png").arg(name)));
    textures.push_back(texture);
    return idx;
}

