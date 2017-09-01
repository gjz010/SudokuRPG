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

int SimpleInputManager::getX() const
{
    return x;
}

int SimpleInputManager::getY() const
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

bool SimpleInputManager::checkTap() const
{
    return istap;
}

void SimpleInputManager::clearTap()
{
    istap=false;
}

float SimpleInputManager::getXPos() const
{
    return (float)x/width;
}

float SimpleInputManager::getYPos() const
{
    return (float)y/height;
}

float SimpleInputManager::getTapXPos() const
{
    return (float)tapx/width;
}

float SimpleInputManager::getTapYPos() const
{
    return (float)tapy/height;
}

void SimpleInputManager::setViewport(int w, int h)
{
    width=w;
    height=h;
}

int SimpleInputManager::getViewWidth()
{
    return width;
}

int SimpleInputManager::getViewHeight()
{
    return height;
}

int SimpleInputManager::getTapX() const
{
    return tapx;
}

int SimpleInputManager::getTapY() const
{
    return tapy;
}
