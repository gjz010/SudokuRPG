#include "sudokuwindow.h"
#include <QOpenGLShaderProgram>
#include <QtOpenGL>
#include <ctime>
struct SudokuWindow::Internal{
    QOpenGLShaderProgram* prog;
    int huaji;
    int t=0;
    clock_t last_time=0;
    //QOpenGLContect* m_context;
};
SudokuWindow::SudokuWindow(QWidget *parent)
{
    //this->setAttribute(Qt::WA_AcceptTouchEvents,false);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(4);
    format.setSwapInterval(1);
    setFormat(format);
    this->setWidth(400);
    this->setHeight(600);
    gl=new GLManager(this);
    input=new SimpleInputManager(this);
    data=new Internal;
    //this->context()->setAutoBufferSwap(true);
    //data->m_context = new QOpenGLContext;
    QTimer* timer=new QTimer(this);
    timer->setInterval(16); //Lock at 60 fps
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(onFrame()));
    data->last_time=clock();
    timer->start();
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
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    //glClearDepth(2000.0);
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    makeCurrent();
    data->prog->bind();
    gl->getProjMatrix().ortho(-1,1,-1,1,1,-1);
    //matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.translate(0, 0, -2);
    data->prog->setUniformValue("matrix",gl->getMatrix());
    //data->prog->setUniformValue("texture",);
    GLfloat vertices[] = {
        0.0f, 1.f, 0.0f,
        -1.f+0.01f*data->t, -1.f, 0.0f,
        1.f, -1.f, 0.0f,
        1.f, 0.f, 0.5f
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

void SudokuWindow::mousePressEvent(QMouseEvent *ev)
{
    input->onMouseDown(ev->x(),ev->y());
}
void SudokuWindow::mouseMoveEvent(QMouseEvent *ev)
{
    input->onMouseMove(ev->x(),ev->y());
}
void SudokuWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    input->onMouseUp(ev->x(),ev->y());
}


void SudokuWindow::onFrame()
{

    long long delta=clock()-data->last_time;
    data->t++;
    update();
    if(input->isTap()){
        QMessageBox* msgbox=new QMessageBox(nullptr);
        msgbox->setAttribute(Qt::WA_DeleteOnClose);
        msgbox->setStandardButtons(QMessageBox::Ok);
        msgbox->setWindowTitle("Tap!");
        msgbox->setText(QString("FPS:%3 Tapped at (%1 , %2).").arg(input->getTapX()).arg(input->getTapY()).arg((double)data->t*CLOCKS_PER_SEC/delta));
        msgbox->setModal(false);
        msgbox->show();
        //QMessageBox::information(nullptr,"Tap!","Tap!",QMessageBox::Ok);
        //qDebug()<<;
    }
    if(data->t%100==0){
        //qDebug()<<(double)data->t*CLOCKS_PER_SEC/delta;

    }
}
