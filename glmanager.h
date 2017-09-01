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
#include <QSound>
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
    std::map<QString,int> texture_mapping;
    std::map<QString,QSound*> sound_mapping;
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
    void initStack();
    int LoadTexture(const QString& name);
    QOpenGLTexture* getTexture(const QString& name);
    QOpenGLTexture* getTexture(int idx) const;
    QVector3D unproject(float x,float y,float z);
    //Indeed it's not something that GL manager should do...
    void LoadSound(const QString& name);
    QSound* getSound(const QString& name) const;
signals:

public slots:
};

#endif // GLMANAGER_H
