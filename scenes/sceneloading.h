#ifndef SCENELOADING_H
#define SCENELOADING_H
#include "scene.h"
#include <QObject>

class SceneLoading : public Scene
{
    Q_OBJECT
public:
    explicit SceneLoading(GLManager* gl,SudokuWindow *parent = nullptr);
    void render();
    void act();
    bool load();
    ~SceneLoading();
private:
    struct Internal;
    Internal* data;
};

#endif // SCENELOADING_H
