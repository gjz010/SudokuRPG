#ifndef SIMPLEINPUTMANAGER_H
#define SIMPLEINPUTMANAGER_H

#include <QObject>
/*
 * This is a simple input manager which handles only mouse/touch input.
 *
 *
 */
class SimpleInputManager : public QObject
{
    Q_OBJECT
public:
    explicit SimpleInputManager(QObject *parent = nullptr);

signals:

public:
    void onMouseDown(int,int);
    void onMouseMove(int,int);
    void onMouseUp(int,int);
private:
    bool isdown;
    bool istap;
    int x;
    int y;
    int tapx;
    int tapy;
public:
    int getX();
    int getY();
    bool isDown();
    bool isTap();
    int getTapX();
    int getTapY();
};

#endif // SIMPLEINPUTMANAGER_H
