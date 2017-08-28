#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "glmanager.h"
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

private:
    GLManager* gl;
    class Internal;
    Internal* data;
};

#endif // SUDOKUWINDOW_H
