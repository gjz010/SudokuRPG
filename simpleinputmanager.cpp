#include "simpleinputmanager.h"

SimpleInputManager::SimpleInputManager(QObject *parent) : QObject(parent),istap(false),isdown(false)
{

}

void SimpleInputManager::onMouseDown(int x,int y)
{
    isdown=true;
    onMouseMove(x,y);
}

void SimpleInputManager::onMouseMove(int x, int y)
{
    this->x=x;
    this->y=y;
}

void SimpleInputManager::onMouseUp(int x, int y)
{
    isdown=false;
    istap=true;
    tapx=x;
    tapy=y;
    onMouseMove(x,y);
}

int SimpleInputManager::getX()
{
    return x;
}

int SimpleInputManager::getY()
{
    return y;
}


bool SimpleInputManager::isDown()
{
    return isdown;
}

bool SimpleInputManager::isTap()
{
    bool t=istap;
    istap=false;
    return t;

}

int SimpleInputManager::getTapX()
{
    return tapx;
}

int SimpleInputManager::getTapY()
{
    return tapy;
}
