#include "sceneloading.h"
#include <QtOpenGL>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include "shaderpacker.h"
#include <vector>
#include "scenemenu.h"
struct SceneLoading::Internal{
    QOpenGLBuffer* buf;
    float brightness=1.f;
    bool loaded=false;
    std::vector<QString> img_loadlist;
    std::vector<QString> sound_loadlist;
};

SceneLoading::SceneLoading(GLManager *gl, SudokuWindow *parent): Scene(gl,parent)
{
    gl->LoadTexture("loading");
    gl->LoadTexture("huaji");

    gl->initStack();
    gl->getProjMatrix().ortho(0.f,1.f,0.f,1.f,-1,1);
    static const SimpleVertex vertexData[]={
        {
            {0.f,1.f,0.f},
            {0.f,0.f}
        },
        {
            {0.f,0.f,0.f},
            {0.f,1.f}
        },
        {
            {1.f,0.f,0.f},
            {1.f,1.f}
        },
        {
            {1.f,1.f,0.f},
            {1.f,0.f}
        },

    };
    /*
    GLfloat vertices[] = {
        0.f, 1.f, 0.0f,
        0.f, 0.f, 0.0f,
        1.f, 0.f, 0.0f,
        1.f, 1.f, 0.0f
    };
    GLfloat coords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    */
    data=new Internal;

    data->buf=new QOpenGLBuffer();
    data->buf->create();
    data->buf->bind();
    data->buf->allocate(sizeof(vertexData));

    data->buf->write(0,vertexData,sizeof(vertexData));
    data->buf->release();

    data->img_loadlist.push_back("menu");
    data->img_loadlist.push_back("classic");
    data->img_loadlist.push_back("rpg");
    data->img_loadlist.push_back("ingame_gui");
    data->img_loadlist.push_back("bg");

    data->sound_loadlist.push_back("click.wav");
}

void SceneLoading::render()
{

    //int texture=gl->getTexture("loading");
    context->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QOpenGLShaderProgram* prog=gl->getShader("test");

    prog->bind();

    //matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.translate(0, 0, -2);
    prog->setUniformValue("matrix",gl->getMatrix());
    prog->setUniformValue("brightness",data->brightness);
    //data->prog->setUniformValue("texture",);


    data->buf->bind();
    prog->setAttributeBuffer("vertAttr",GL_FLOAT,offsetof(SimpleVertex,vertAttr),3,sizeof(SimpleVertex));
    prog->setAttributeBuffer("texCoord",GL_FLOAT,offsetof(SimpleVertex,texCoord),2,sizeof(SimpleVertex));
    data->buf->release();
    //
    /*
    prog->setAttributeBuffer("vertAttr",GL_FLOAT,0,3,0);
    //prog->setAttributeArray("vertAttr",GL_FLOAT,vertices,3,0);
    data->buf->release();
    prog->setAttributeArray("texCoord",GL_FLOAT,coords,2,0);
    */
    prog->enableAttributeArray("vertAttr");
    prog->enableAttributeArray("texCoord");
    QOpenGLTexture* tex=gl->getTexture("loading");
    tex->bind();
    context->glDrawArrays(GL_TRIANGLE_FAN,0,4);

    prog->disableAttributeArray("vertAttr");
    prog->disableAttributeArray("texCoord");
    tex->release();
    prog->release();
}

void SceneLoading::act()
{
    if(!data->loaded){
        if(load()){
            data->loaded=true;

        }
    }else{ //perform fadeout and ready for next scene.
        data->brightness-=0.1f;
        if(data->brightness<0.f){
            data->brightness=0.f;
            context->switchScene(new SceneMenu(gl,context));
            return;
        }


    }
    if(context->input()->isTap()){
        qDebug("Tap!");
        qDebug()<<gl->unproject(context->input()->getTapXPos(),context->input()->getTapYPos(),0.5);
    }

}
/*
 * Written in the form of state-machine to avoid lagging.
 */
bool SceneLoading::load()
{
    if(!data->img_loadlist.empty()){
        QString str=data->img_loadlist.back();
        gl->LoadTexture(str);
        data->img_loadlist.pop_back();
        return false;
    }else if(!data->sound_loadlist.empty()){
        QString str=data->sound_loadlist.back();
        gl->LoadSound(str);
        data->sound_loadlist.pop_back();
        return false;

    }else
    {
        return true;
    }
    //return true;
}

SceneLoading::~SceneLoading()
{
    data->buf->destroy();
    delete data;
}
