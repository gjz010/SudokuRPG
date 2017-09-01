#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "glmanager.h"
#include "simpleinputmanager.h"
class Scene;
class SudokuWindow : public QOpenGLWindow,public QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit SudokuWindow(QWidget *parent = 0);
    QSize sizeHint() const;
    ~SudokuWindow();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    SimpleInputManager* input() const;
    void switchScene(Scene* scene);
protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

private:
    GLManager* gl;
    SimpleInputManager* _input;
    class Internal;
    Internal* data;
public slots:
    void onFrame();
};

#endif // SUDOKUWINDOW_H
