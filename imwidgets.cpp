#include "imwidgets.h"
static float mousex;
static float mousey;
static float mousetapx;
static float mousetapy;
static bool tapped;
static GLManager* gl;
static SimpleInputManager* input;
static std::vector<SimpleVertex> vertices;
void IMWidgets::init(GLManager* _gl,SimpleInputManager* _input)
{
    vertices=std::vector<SimpleVertex>();
    gl=_gl;
    input=_input;
    QVector3D mousepos=gl->unproject(input->getXPos(),input->getYPos(),0);
    QVector3D mousetap=gl->unproject(input->getTapXPos(),input->getTapYPos(),0);
    mousex=mousepos.x();
    mousey=mousepos.y();
    mousetapx=mousetap.x();
    mousetapy=mousetap.y();
    tapped=input->isTap();
}

int IMWidgets::Button(QRectF rect, QRectF tex_up,QRectF tex_down,float z,QVector4D tone)
{
    int mouse_state=MouseArea(rect,z);
    Sprite(rect,(mouse_state==1?tex_down:tex_up),z,tone);
    return mouse_state;
}

void IMWidgets::Sprite(QRectF rect, QRectF texcoord, float z,QVector4D tone)
{
    SimpleVertex v1={{(float)rect.left(),(float)rect.bottom(),z},{(float)texcoord.left(),(float)texcoord.top()},tone};
    SimpleVertex v2={{(float)rect.left(),(float)rect.top(),z},{(float)texcoord.left(),(float)texcoord.bottom()},tone};
    SimpleVertex v3={{(float)rect.right(),(float)rect.top(),z},{(float)texcoord.right(),(float)texcoord.bottom()},tone};
    SimpleVertex v4={{(float)rect.right(),(float)rect.bottom(),z},{(float)texcoord.right(),(float)texcoord.top()},tone};
    //qDebug()<<v1.toString()<<v2.toString()<<v3.toString()<<v4.toString();
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v1);
    vertices.push_back(v3);
    vertices.push_back(v4);
    /*
    SimpleVertex vertices[]={
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
    };
    */
}

void IMWidgets::Shape(QVector2D pos[], QVector2D tex[], int len, float z,QVector4D tone)
{
    for(int i=0;i<len;i++){
        SimpleVertex v={{pos[i].x(),pos[i].y(),z},{tex[i].x(),tex[i].y()},tone};
        vertices.push_back(v);
    }
    //return 0;
}

//0:nothing
//1:down
//2:tapped
int IMWidgets::MouseArea(QRectF rect, float z)
{

    if(tapped){
        if(rect.contains(mousetapx,mousetapy)){
            input->clearTap();
            return 2;

        }
    }else{
        if(input->isDown()){
            if(rect.contains(mousex,mousey)){
                return 1;

            }

        }

    }

    return 0;
}

int IMWidgets::MouseArea(QVector2D pos[], float z)
{
    return 0;
}

const SimpleVertex *IMWidgets::list()
{
    return vertices.data();
}

int IMWidgets::refresh(QOpenGLBuffer * buffer)
{
    buffer->bind();
    buffer->write(0,list(),vertices.size()*sizeof(SimpleVertex));
    buffer->release();
    return vertices.size();
}

IMWidgets::IMWidgets()
{

}
