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

public slots:
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
    int width=1;
    int height=1;
public:
    int getX() const;
    int getY() const;
    bool isDown();
    bool isTap();
    bool checkTap() const;
    void clearTap();
    int getTapX() const;
    int getTapY() const;
    float getXPos() const;
    float getYPos() const;
    float getTapXPos() const;
    float getTapYPos() const;
    void setViewport(int,int);
    int getViewWidth();
    int getViewHeight();
};

#endif // SIMPLEINPUTMANAGER_H
