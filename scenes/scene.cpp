#include "scene.h"

Scene::Scene(GLManager *gl, SudokuWindow *parent) : QObject(parent)
{
    this->gl=gl;
    this->context=parent;
}
