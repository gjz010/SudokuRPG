#include "sceneingame.h"
#include "shaderpacker.h"
#include <QOpenGLBuffer>
#include "imwidgets.h"
#include "scenemenu.h"
#define CLEAR(x) memset(x,0,sizeof(x))
struct SceneIngame::Internal{
    float brightness=0.0f;
    QOpenGLBuffer* buf;
    QOpenGLBuffer* widgetbuffer;
    bool enabled=false;
    bool switching_off=false;
    int sudoku[9][9];
    bool locked[9][9];
    int number_tone[9][9];
    int number_chosen=-1;
    int grid_tone[9][9];
    int menu_chosen;
    int menu_symbol_tone[2][6];
    int menu_grid_tone[2][6];
};
static QRectF getMark(int row,int column){
    float u=column*51;
    float v=row*51;
    return QRectF(u/512,v/512,51.0f/512,51.0f/512);
}
static const QRectF MARK_NUMBERS[]={
    getMark(0,1),getMark(0,2),getMark(0,3),getMark(0,4),getMark(1,0),
    getMark(1,1),getMark(1,2),getMark(1,3),getMark(1,4),getMark(0,0),
};
static const QRectF MARK_RESTART=getMark(2,0);
static const QRectF MARK_UNDO=getMark(2,1);
static const QRectF MARK_REDO=getMark(2,2);
static const QRectF MARK_PAUSE=getMark(2,3);
static const QRectF MARK_LEVEL=getMark(2,4);
static const QRectF MARK_DONE=getMark(3,0);
static const QRectF MARK_UNDONE=getMark(3,1);
static const QRectF MARK_QUIT=getMark(3,2);
static const QRectF BUTTON_UP(384.0f/512,0,64.f/512,64.f/512);
static const QRectF BUTTON_DOWN(448.0f/512,0,64.f/512,64.f/512);
static const QVector4D TONES[]={{1.f,1.f,1.f,1.f}, //Normal
                                     {0.299f,0.587f,0.114f,1.f}, //Greyscale
                                     {2.f,0.f,0.f,1.f}, //R
                                     {0.f,2.f,0.f,1.f}, //G
                                     {0.f,0.f,2.f,1.f}, //B
                                     {0.f,0.f,0.f,1.f}, //Bitmap
                                     {1.f,1.f,0.f,1.f}, //Y
                                     {0.f,1.f,1.f,1.f}, //C
                               };
enum Tone{
  NORMAL,GREY,FILTER_R,FILTER_G,FILTER_B,FILTER_BITMAP,FILTER_Y,FILTER_C

};
SceneIngame::SceneIngame(GLManager *gl, SudokuWindow *parent): Scene(gl,parent)
{
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
    };
    data=new Internal;
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

    CLEAR(data->sudoku);
    CLEAR(data->number_tone);
    CLEAR(data->grid_tone);
    CLEAR(data->menu_grid_tone);
    CLEAR(data->menu_symbol_tone);
    CLEAR(data->locked);

    data->menu_chosen=1;
}

void SceneIngame::render()
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
    prog->setAttributeBuffer("vertTone",GL_FLOAT,offsetof(SimpleVertex,tone),4,sizeof(SimpleVertex));
    data->widgetbuffer->release();
    //qDebug()<<count;
    prog->enableAttributeArray("vertTone");
    prog->setUniformValue("renderTone",true);
    context->glDrawArrays(GL_TRIANGLES,0,count);
    prog->setUniformValue("renderTone",false);
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
    prog->disableAttributeArray("vertTone");

    prog->release();
}

void SceneIngame::act()
{
    IMWidgets::init(gl,context->input());
    if(data->brightness<1.f && !data->switching_off){
        data->brightness+=0.1f;
        if(data->brightness>=1.f) data->enabled=true;
    }
    if(data->switching_off){
        data->brightness-=0.1f;
        if(data->brightness<=.0f){
            Scene* scene=new SceneMenu(gl,context);
            context->switchScene(scene);
            return;

        }
    }
    /*int classic_button=IMWidgets::Button(QRectF(.2f,.3f,.6f,.1f),
                                         //QRectF(0.f,0.f,1.f,1.f),
                                         QRectF(0.0f,205.0f/512,0.25f,48.0f/512),
                                         QRectF(0.0f,(205.0f+48.0f)/512,0.25f,48.0f/512),
                                         0.1f,
                                         {1.f,0.f,0.f,1.f}
                                         );
                                         */
    float scale=(float)context->input()->getViewWidth()/context->input()->getViewHeight();
    int quit_button=IMWidgets::Button(QRectF(.0f,.92f,.08f/scale,.08f),BUTTON_UP,BUTTON_DOWN,.1f);
    if(quit_button==2 && data->enabled){
        data->enabled=false;
        data->switching_off=true;
    }
    float w=0.9f/9;
    float h=0.9f/9*scale;
    int buttons[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            bool locked=data->locked[i][j];
            int chosen_i=data->number_chosen/9;
            int chosen_j=data->number_chosen%9;
            int chosen_digit=data->sudoku[chosen_i][chosen_j];
            int char_tone=(locked?FILTER_BITMAP:NORMAL);
            int number=data->sudoku[i][j];
            if(chosen_digit==number) char_tone=FILTER_R;
            int button_tone=(data->number_chosen>=0 && (i==chosen_i||j==chosen_j)?FILTER_Y:NORMAL);
            QRectF r={0.01f+i*(w+0.01),.95f-(0.2f+j*(h+0.01)),w,h};

            if(locked){
                IMWidgets::Sprite(r,BUTTON_UP,0.1f);
                buttons[i][j]=0;
            }
            else
            buttons[i][j]=IMWidgets::Button(r,BUTTON_UP,BUTTON_DOWN,0.1f,TONES[button_tone]);


            if(number>0) IMWidgets::Sprite(r,MARK_NUMBERS[number-1],0.2f,TONES[char_tone]);

            if(buttons[i][j]==2 && !locked){
                data->sudoku[i][j]=data->menu_chosen;
                data->number_chosen=i*9+j;
            }

        }

    }
}
SceneIngame::~SceneIngame()
{
    data->buf->destroy();
    data->widgetbuffer->destroy();
    delete data;
}
