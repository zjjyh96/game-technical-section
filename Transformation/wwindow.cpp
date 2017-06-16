#include"wwindow.h"
#include"mainwindow.h"
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<wwindow.h>
#include<cmath>
#include<QTimer>
#include<qDebug>


//构造函数
wwindow::wwindow(QWidget *parent):QWidget(parent)
{

    setPalette(QPalette(Qt::white));

//    QPalette palette=this->palette();
//    QPixmap pixmap = QPixmap("001.png");//picture routes
//    setPalette(QPalette(pixmap));
//    palette.setBrush(QPalette::Background, QBrush(pixmap));//window backgrount picture setting

    setAutoFillBackground(true);
    setMinimumSize(400,400);

    shape1 = new Shape();
    shape2 = new Shape();
    for(int i=0;i<21;i++) shapeTemp[i] = new Shape();
    mode=0;
    size1=size2=0;
    index=0;
    grain=30;
    bshow=false;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

//默认析构函数
wwindow::~wwindow()
{
}

void wwindow::move()
{
    index++;
    if(index>=20) timer->stop();
    update();
}

void wwindow::startmove()
{
    int i,j;
    index=0;
    if(mode==3)
        //进行线性插值计算插值点的坐标
        for(i=0;i<size1;i++)
            for(j=0;j<21;j++)
            {
                shapeTemp[j]->point[i].x= \
                        shape1->point[i].x+(shape2->point[i].x-shape1->point[i].x)/20*j;
                shapeTemp[j]->point[i].y= \
                        shape1->point[i].y+(shape2->point[i].y-shape1->point[i].y)/20*j;
            }
    else if(mode==4)
    {
        float r1[size1],theta1[size1],r2[size1],theta2[size1],r=0,theta=0;
        float dx,dy,x0=0,y0=0;
        int flag=0;

        //计算对应形状的极坐标表达
        for(i=1;i<size1;i++)
        {
            dx=shape1->point[i].x-shape1->point[i-1].x;
            dy=shape1->point[i].y-shape1->point[i-1].y;
            r1[i]=sqrt(dx*dx+dy*dy);
            if(dx<0) theta1[i]=atan(dy/dx)+3.1415;
            else theta1[i]=atan(dy/dx);
//            printf("r1[%d]=%f,theta1[%d]=%f\n",i,r1[i],i,theta1[i]);

        }

        for(i=1;i<size2;i++)
        {
            dx=shape2->point[i].x-shape2->point[i-1].x;
            dy=shape2->point[i].y-shape2->point[i-1].y;
            r2[i]=sqrt(dx*dx+dy*dy);
            if(dx<0) theta2[i]=atan(dy/dx)+3.1415;
            else theta2[i]=atan(dy/dx);
//            if(theta2[i]>theta1[i]) theta2[i]=theta2[i]-2*3.1415;
            printf("r2[%d]=%f,theta2[%d]=%f\n",i,r2[i],i,theta2[i]);
        }

        if(theta2[1]>theta1[1]) flag=2;else flag=1;
        for(i=1;i<size1;i++)
        {
            if (flag==1 && theta2[i]>theta1[i]) theta2[i]=theta2[i]-2*3.1415;
            if (flag==2 && theta1[i]>theta2[i]) theta1[i]=theta1[i]-2*3.1415;


        }
        //进行矢量线性差值求得插值点的坐标
        for(j=0;j<21;j++)
        {
            shapeTemp[j]->point[0].x=shape1->point[0].x+(shape2->point[0].x-shape1->point[0].x)/20*j;
            shapeTemp[j]->point[0].y=shape1->point[0].y+(shape2->point[0].y-shape1->point[0].y)/20*j;
        }
        for(j=0;j<21;j++)
            for(i=1;i<size1;i++)
            {
                //得到之前点的坐标
                x0=shapeTemp[j]->point[i-1].x;
                y0=shapeTemp[j]->point[i-1].y;
//                printf("x%d=%f,y%d=%f\n",i,x0,i,y0);

                //计算插值后的r和theta
                r=(r2[i]-r1[i])/20*j+r1[i];
                theta=(theta2[i]-theta1[i])/20*j+theta1[i];
//                printf("r=%f,theta=%f\n",r1,theta);
                //计算插值后的坐标
                dx=r*cos(theta);
                dy=r*sin(theta);
//                printf("dx=%f,dy=%f\n",dx,dy);
                shapeTemp[j]->point[i].x=x0+dx;
                shapeTemp[j]->point[i].y=y0+dy;
//                printf("x=%f,y=%f\n",x0+dx,y0+dy);
                printf("\n");
            }
    }


    timer->start(speed);
}


//清空画板与各参数
void wwindow::clear()
{
//    delete shape1,shape2,shapeTemp;
//    timer->stop();
    mode=0;
    index=0;
    size1=size2=0;
    update();
    printf("clear\n");
}

//设置运动速度
void wwindow::SetSpeed(int s)
{
    speed=5000/s;
}

void wwindow::Arrow()
{
    size1=size2=8;
    index=0;
    mode=0;

    //手动计算输入的箭头点位置数据
    shape1->point[0].setPoint(100,200);
    shape1->point[1].setPoint(200,200);
    shape1->point[2].setPoint(200,180);
    shape1->point[3].setPoint(240,210);
    shape1->point[4].setPoint(200,240);
    shape1->point[5].setPoint(200,220);
    shape1->point[6].setPoint(100,220);
    shape1->point[7].setPoint(100,200);

    shape2->point[0].setPoint(380,260);
    shape2->point[1].setPoint(380,160);
    shape2->point[2].setPoint(360,160);
    shape2->point[3].setPoint(390,120);
    shape2->point[4].setPoint(420,160);
    shape2->point[5].setPoint(400,160);
    shape2->point[6].setPoint(400,260);
    shape2->point[7].setPoint(380,260);
}


void wwindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    //设置笔刷样式，暗灰色，宽度4，实线
    paint.setPen(QPen(QBrush(Qt::green), 3, Qt::SolidLine));
    //绘制原始图形
    for(int i=0;i<size1-1;i++){
        paint.drawLine(shape1->point[i].x,shape1->point[i].y,\
                       shape1->point[i+1].x,shape1->point[i+1].y);
    }
    for(int i=0;i<size1;i++){
        paint.drawEllipse(shape1->point[i].x-3,shape1->point[i].y-2,5,5);
    }
    //绘制终止图形
    paint.setPen(QPen(QBrush(Qt::blue), 4, Qt::SolidLine));
    for(int i=0;i<size2-1;i++){
        paint.drawLine(shape2->point[i].x,shape2->point[i].y,\
                       shape2->point[i+1].x,shape2->point[i+1].y);
    }
    for(int i=0;i<size2;i++){
        paint.drawEllipse(shape2->point[i].x-2,shape2->point[i].y-2,5,5);
    }

    //过程动画的绘制
    if(mode==3||mode==4){
        paint.setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine));
        //若显示轨迹，则绘制所有插值图形
        if(bshow==true){
            for(int j=0;j<21;j++)
                for(int i=0;i<size1-1;i++)
                {
                    paint.drawLine(shapeTemp[j]->point[i].x,shapeTemp[j]->point[i].y,\
                                   shapeTemp[j]->point[i+1].x,shapeTemp[j]->point[i+1].y);
                }
            for(int j=0;j<21;j++)
                for(int i=0;i<size1;i++){
                    paint.drawEllipse(shapeTemp[j]->point[i].x-2,shapeTemp[j]->point[i].y-2,5,5);
                }
        }
        //若不显示轨迹，则仅绘制当前插值图形
        else{
            for(int i=0;i<size1-1;i++)
            {
                paint.drawLine(shapeTemp[index]->point[i].x,shapeTemp[index]->point[i].y,\
                               shapeTemp[index]->point[i+1].x,shapeTemp[index]->point[i+1].y);
            }
            for(int i=0;i<size1;i++){
                paint.drawEllipse(shapeTemp[index]->point[i].x-2,shapeTemp[index]->point[i].y-2,5,5);
            }
        }

    }
}

void wwindow::mousePressEvent(QMouseEvent *e)
{
    float x = e->pos().x();
    float y = e->pos().y();
    //对控制点模式的获取与存储
    if(mode==1)
    {
        shape1->point[size1].x=x;
        shape1->point[size1].y=y;
        size1++;
    }
    else if(mode==2 && size1>=size2)
    {
        shape2->point[size2].x=x;
        shape2->point[size2].y=y;
        size2++;
    }
    update();
}
