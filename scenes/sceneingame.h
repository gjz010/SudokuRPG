#ifndef SCENEINGAME_H
#define SCENEINGAME_H
#include "scene.h"
#include <QObject>

class SceneIngame : public Scene
{
    Q_OBJECT
public:
    explicit SceneIngame(GLManager* gl,SudokuWindow *parent = nullptr);
    void render();
    void act();
    ~SceneIngame();
private:
    struct Internal;
    Internal* data;
};

#endif // SCENEINGAME_H
