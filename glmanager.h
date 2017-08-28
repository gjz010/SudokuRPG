#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <QObject>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <QtOpenGL/QGL>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
using std::string;
using std::map;
using std::stack;
using std::vector;
class GLManager : public QObject
{
    Q_OBJECT
    std::map<QString,QOpenGLShaderProgram*> shaders;
    std::map<QString,int> shader_attr;
    std::vector<QOpenGLTexture*> textures;
    std::stack<QMatrix4x4,std::vector<QMatrix4x4> > matrix_modelview;
    std::stack<QMatrix4x4,std::vector<QMatrix4x4> > matrix_projection;
public:
    explicit GLManager(QObject *parent = nullptr);
    QOpenGLShaderProgram* LoadShader(const QString& name);
    int LoadShaderAttribute(const QString& shader_name,const QString& attr,const QOpenGLShaderProgram* shader=nullptr);
    QOpenGLShaderProgram* getShader(const QString& name);
    void popMVMatrix();
    void popProjMatrix();
    void pushMVMatrix();
    void pushProjMatrix();
    QMatrix4x4& getMVMatrix() const;
    QMatrix4x4& getProjMatrix() const;
    QMatrix4x4 getMatrix() const;
    int LoadTexture(const QString& name);
    QOpenGLTexture* getTexture(int idx) const;
signals:

public slots:
};

#endif // GLMANAGER_H
