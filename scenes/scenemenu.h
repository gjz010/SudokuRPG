#ifndef SCENEMENU_H
#define SCENEMENU_H
#include "scene.h"
#include <QObject>

class SceneMenu : public Scene
{
    Q_OBJECT
public:
    explicit SceneMenu(GLManager* gl,SudokuWindow *parent = nullptr);
    void render();
    void act();
    ~SceneMenu();
private:
    struct Internal;
    Internal* data;
};

#endif // SCENEMENU_H
