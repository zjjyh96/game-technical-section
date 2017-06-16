#include"wwindow.h"
#include"mainwindow.h"
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<wwindow.h>
#include<cmath>
#include<QTimer>
#include<qDebug>


//构造函数，加载小车的图片
wwindow::wwindow(QWidget *parent):QWidget(parent)
{
    s = NULL;
    size = 0;

    QString picName = "car.png";
    car.carPic= new QPixmap(picName);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(changeState()));
}

//默认析构函数
wwindow::~wwindow()
{
}

//改变状态
void wwindow::changeState()
{
    d++;
    x1=s->getX(d);
    y1=s->getY(d);
    x2=s->getX(d+1);
    y2=s->getY(d+1);

    if(d==(size-2))timer->stop();

    printf("x1=%f,y1=%f ",x1,y1);
    printf("x2=%f,y2=%f\n",x2,y2);

//    printf("d=%d\n",d);
//    printf("size=%d\n",size);
    update();
}

void wwindow::startMove()
{
    timer->start(int(car.speed));
    printf("start\n");
}


//设置小车速度
void wwindow::setCar(float speed)
{
    car.speed = 500/speed;
    printf("speed=%f\n",car.speed);
}

//设置样条参数
void wwindow::setSpline(int grain, float tension)
{
    if(!s)delete s;
    //若仅一个点或没有则返回空
    if(vec.size()<=0)return;
    //新建点
    point* p = new point[vec.size()];
    //把点都存入p
    for(int i=0;i<vec.size();i++){
        p[i].x = vec[i].x;
        p[i].y = vec[i].y;
    }
    //新建样条曲线
    s = new spline(p,vec.size(),grain,tension);
    size = s->size();
    //size = (vec.size()-1)*grain+1;
    printf("setspline\n");
}

//清空画板与各参数
void wwindow::clear()
{
    size = 0;
    vec.clear();
    delete s;
    timer->stop();
    x1 = y1 = x2 = y2 = -1;
    update();
    printf("clear\n");
}

float wwindow::getRatio()
{
    const float pi = 3.14159;

    printf("getratio\n");

    float theta = atan((y2-y1)/(x2-x1));
    return theta/(2*pi)*360;
}

void wwindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    //绘制小车
    if(size>0){
        float ratio;
        ratio = getRatio();
        paint.translate(x1,y1);
        paint.rotate(ratio);
        paint.drawPixmap(-90,-90,180,90,*car.carPic);
        //paint.drawPixmap(QPoint(100,100),*car.carPic);
        //printf("drawcar\n");
        paint.rotate(-ratio);
        paint.translate(-x1,-y1);
    }

    //设置笔刷样式，暗灰色，宽度4，实线
    paint.setPen(QPen(QBrush(Qt::darkGray), 4, Qt::SolidLine));
    //绘制cardinal样条曲线
    for(int i=0;i<size-1;i++){
        paint.drawLine(s->getX(i),s->getY(i),
                       s->getX(i+1),s->getY(i+1));
    }
    //绘制取样点，用画圆表示
    for(int i=0;i<vec.size();i++){
        paint.drawEllipse(vec[i].x-2,vec[i].y-2,5,5);
    }
}

void wwindow::mousePressEvent(QMouseEvent *e)
{
    float x = e->pos().x();
    float y = e->pos().y();
    point p;
    p.setPoint(x,y);
    vec.push_back(p);
    update();
}
