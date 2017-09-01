#ifndef SCENE_H
#define SCENE_H
#include "glmanager.h"
#include <QObject>
#include "sudokuwindow.h"
class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(GLManager* gl,SudokuWindow *parent = nullptr);

signals:

public slots:
    virtual void render()=0;
    virtual void act()=0;
protected:
    GLManager* gl;
    SudokuWindow* context;
};

#endif // SCENE_H
