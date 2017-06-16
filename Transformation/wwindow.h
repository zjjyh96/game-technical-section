#ifndef WWINDOW_H
#define WWINDOW_H
#include<QWidget>

class QTimer;

class Point{
public:
    float x,y;
    void setPoint(float a,float b){
        x=a;
        y=b;
    }
};

class Shape{
public:
    Point point[20];
};

class wwindow : public QWidget
{
    Q_OBJECT
private:
    //定时器
    QTimer* timer;
    Shape* shape1,* shape2,* shapeTemp[30];
    int size1,size2,index,grain,speed=100;

public:
    int mode;
    bool bshow;

public:
    wwindow(QWidget *parent = 0);
    ~wwindow();

    void clear();
    void startmove();
    void Arrow();
    void SetSpeed(int s);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
private slots:
    void move();
};

#endif // WWINDOW_H
