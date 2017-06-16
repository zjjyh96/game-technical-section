#ifndef WWINDOW_H
#define WWINDOW_H

#include"spline.h"
#include<QWidget>
#include<vector>
class QTimer;
class wwindow : public QWidget
{
    Q_OBJECT
private:
    spline* s;
    std::vector<point>vec;
    int size,d=0;
    //定时器
    QTimer* timer;
    //小车
    class car_t{
    public:
        QPixmap* carPic;
        float speed;
    }car;
    //spline的一些参数
    float x1,y1,x2,y2;

    float getRatio();

public:
    wwindow(QWidget *parent = 0);
    ~wwindow();
    void setSpline(int grain, float tension);
    void setCar(float speed);

//    std::vector<point> getVector(){
//        return vec;
//    }

    void clear();
    void startMove();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
private slots:
    void changeState();
};

#endif // WWINDOW_H
