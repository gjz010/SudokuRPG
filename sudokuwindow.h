#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "glmanager.h"
#include "simpleinputmanager.h"
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
protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
private:
    GLManager* gl;
    SimpleInputManager* input;
    class Internal;
    Internal* data;
public slots:
    void onFrame();
};

#endif // SUDOKUWINDOW_H
