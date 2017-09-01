#include "scenemenu.h"
#include <QOpenGLBuffer>
#include "shaderpacker.h"
#include <QSound>
#include "imwidgets.h"
#include <QtOpenGL>
#include "sceneingame.h"
struct SceneMenu::Internal{
    float brightness=0;
    QOpenGLBuffer* buf;
    QOpenGLBuffer* widgetbuffer;
    bool switching_off=false;
    bool enabled=false;
    int choice=0;
};
SceneMenu::SceneMenu(GLManager *gl, SudokuWindow *parent): Scene(gl,parent)
{
    data=new Internal;
    gl->initStack();
    gl->getProjMatrix().ortho(0.f,1.f,0.f,1.f,-1,1);
    static const SimpleVertex vertexData[]={
        //Main Window
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
        //Button Classic
        {
            {0.1f,0.5f,0.1f},
            {0.f,0.f}
        },
        {
            {0.1f,0.3f,0.1f},
            {0.f,1.f}
        },
        {
            {0.9f,0.3f,0.1f},
            {.5f,1.f}
        },
        {
            {0.9f,0.5f,0.1f},
            {.5f,0.f}
        },
        //Button RPG
        {
            {0.1f,0.3f,0.1f},
            {0.f,0.f}
        },
        {
            {0.1f,0.1f,0.1f},
            {0.f,1.f}
        },
        {
            {0.9f,0.1f,0.1f},
            {.5f,1.f}
        },
        {
            {0.9f,0.3f,0.1f},
            {.5f,0.f}
        },
        //Button Classic Pressed
        {
            {0.1f,0.5f,0.1f},
            {0.5f,0.f}
        },
        {
            {0.1f,0.3f,0.1f},
            {0.5f,1.f}
        },
        {
            {0.9f,0.3f,0.1f},
            {1.f,1.f}
        },
        {
            {0.9f,0.5f,0.1f},
            {1.f,0.f}
        },
        //Button RPG Pressed
        {
            {0.1f,0.3f,0.1f},
            {0.5f,0.f}
        },
        {
            {0.1f,0.1f,0.1f},
            {0.5f,1.f}
        },
        {
            {0.9f,0.1f,0.1f},
            {1.f,1.f}
        },
        {
            {0.9f,0.3f,0.1f},
            {1.f,0.f}
        },
    };

    data->buf=new QOpenGLBuffer();
    data->buf->create();
    data->buf->bind();
    data->buf->allocate(sizeof(vertexData));

    data->buf->write(0,vertexData,sizeof(vertexData));
    data->buf->release();


    data->widgetbuffer=new QOpenGLBuffer();
    data->widgetbuffer->create();
    data->widgetbuffer->bind();
    data->widgetbuffer->allocate(sizeof(SimpleVertex)*2048);
    data->widgetbuffer->release();

}

void SceneMenu::render()
{
    //gl->getProjMatrix().ortho(0,1,0,1,1,0);
    context->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    context->glEnable(GL_BLEND);
    context->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    QOpenGLShaderProgram* prog=gl->getShader("test");
    prog->bind();
    prog->setUniformValue("matrix",gl->getMatrix());
    prog->setUniformValue("brightness",data->brightness);
    prog->enableAttributeArray("vertAttr");
    prog->enableAttributeArray("texCoord");

    data->buf->bind();
    prog->setAttributeBuffer("vertAttr",GL_FLOAT,offsetof(SimpleVertex,vertAttr),3,sizeof(SimpleVertex));
    prog->setAttributeBuffer("texCoord",GL_FLOAT,offsetof(SimpleVertex,texCoord),2,sizeof(SimpleVertex));
    data->buf->release();

    gl->getTexture("bg")->bind();
    context->glDrawArrays(GL_TRIANGLE_FAN,0,4);


    int count=IMWidgets::refresh(data->widgetbuffer);
    gl->getTexture("ingame_gui")->bind();
    data->widgetbuffer->bind();
    prog->setAttributeBuffer("vertAttr",GL_FLOAT,offsetof(SimpleVertex,vertAttr),3,sizeof(SimpleVertex));
    prog->setAttributeBuffer("texCoord",GL_FLOAT,offsetof(SimpleVertex,texCoord),2,sizeof(SimpleVertex));
    data->widgetbuffer->release();
    //qDebug()<<count;
    context->glDrawArrays(GL_TRIANGLES,0,count);
    /*
    gl->getTexture("menu")->bind();
    context->glDrawArrays(GL_TRIANGLE_FAN,0,4);
    gl->getTexture("classic")->bind();
    context->glDrawArrays(GL_TRIANGLE_FAN,(data->classic_pressed?12:4),4);
    gl->getTexture("rpg")->bind();
    context->glDrawArrays(GL_TRIANGLE_FAN,(data->rpg_pressed?16:8),4);
    */
    prog->disableAttributeArray("vertAttr");
    prog->disableAttributeArray("texCoord");

    prog->release();
}

void SceneMenu::act()
{
    IMWidgets::init(gl,context->input());
    if(data->brightness<1.f && !data->switching_off){
        data->brightness+=0.1f;
        if(data->brightness>=1.f) data->enabled=true;
    }
    if(data->switching_off){
        data->brightness-=0.1f;

        if(data->brightness<=.0f){
            Scene* scene;
            if(data->choice==1) scene=new SceneIngame(gl,context);
            else scene=new SceneMenu(gl,context);
            context->switchScene(scene);
            return;

        }
    }
        IMWidgets::Sprite(QRectF(.1f,.8f,.8f,.1f),
                          QRectF(0.f,301.f/512,320.f/512,64.f/512),
                          0.1f);
        int classic_button=IMWidgets::Button(QRectF(.2f,.3f,.6f,.1f),
                                             //QRectF(0.f,0.f,1.f,1.f),
                                             QRectF(0.0f,205.0f/512,0.25f,48.0f/512),
                                             QRectF(0.0f,(205.0f+48.0f)/512,0.25f,48.0f/512),
                                             0.1f);
        int rpg_button=IMWidgets::Button(QRectF(.2f,.15f,.6f,.1f),
                                             QRectF(0.25f,205.0f/512,0.25f,48.0f/512),
                                             QRectF(0.25f,(205.0f+48.0f)/512,0.25f,48.0f/512),
                                             0.1f);
        if(data->enabled){
            if(classic_button==2){
                gl->getSound("click.wav")->play();
                data->switching_off=true;
                data->enabled=false;
                data->choice=1;
            }else if(rpg_button==2){
                qDebug("Not implemented yet!");
                gl->getSound("click.wav")->play();
                data->switching_off=true;
                data->enabled=false;
                data->choice=2;
            }
        }


}

SceneMenu::~SceneMenu()
{
    data->buf->destroy();
    data->widgetbuffer->destroy();
    delete data;
}
