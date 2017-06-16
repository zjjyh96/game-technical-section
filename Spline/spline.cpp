#include "spline.h"
#include <math.h>
#include <stdio.h>

void point::setPoint(float _x, float _y)
{
    x = _x;
    y = _y;
}

spline::spline(point* p, int _n, int _grain, float _tension)
{
    n = _n;
    grain = _grain;
    tension = _tension;

    point *s;
    int i, j;
    float* u = new float[grain];

    //复制第一和最后一个点，重新储存控制点序列
    knots = new point[n + 2];
    int index=0;
    for (int i = 1; i<=n; i++) {
        knots[i].x = p[i-1].x;
        knots[i].y = p[i-1].y;
        //printf("x=%f,y=%f\n",knots[i].x,knots[i].y);
    }
    knots[0].x = p[0].x;
    knots[0].y = p[0].y;
    knots[n + 1].x = p[n - 1].x;
    knots[n + 1].y = p[n - 1].y;

    //新建grain点储存于Spline
    Spline = new point[(n-1)* grain + 1];


    //手动设定cardinal样条里的矩阵内容
    m[0] = -tension;
    m[1] = 2 - tension;
    m[2] = tension - 2;
    m[3] = tension;
    m[4] = 2 * tension;
    m[5] = tension - 3;
    m[6] = 3 - 2 * tension;
    m[7] = -tension;
    m[8] = -tension;
    m[9] = 0;
    m[10] = tension;
    m[11] = 0;
    m[12] = 0;
    m[13] = 1;
    m[14] = 0;
    m[15] = 0;

    //计算把u分成grain份之后每一个插值点的u值
    for (i = 0; i<grain; i++) {
        u[i] = ((float)i) / grain;
    }
    s = Spline;

    //计算矩阵
    for (i = 0; i<n-1; i++) {
        init(0,i,knots[index].x,knots[index+1].x,knots[index+2].x,knots[index+3].x);
        init(1,i,knots[index].y,knots[index+1].y,knots[index+2].y,knots[index+3].y);
        for (j = 0; j<grain; j++) {
            s->x = Matrix(0, i, u[j]);
            s->y = Matrix(1, i, u[j]);
            s++;
        }
        index++;
    }
    s->x = knots[n].x;
    s->y = knots[n].y;
    delete u;
}

int spline::size()
{
    return (n-1)*grain + 1;
}

float spline::getX(int i)
{
    return Spline[i].x;
}

float spline::getY(int i)
{
    return Spline[i].y;
}

//初始化矩阵计算插值点的x与y坐标值（i为0则是计算x，i为1则是计算y）
void spline::init(int i,int j,float a0, float b0, float c0, float d0)
{
    a[i][j] = m[0] * a0 + m[1] * b0 + m[2] * c0 + m[3] * d0;
    b[i][j] = m[4] * a0 + m[5] * b0 + m[6] * c0 + m[7] * d0;
    c[i][j] = m[8] * a0 + m[9] * b0 + m[10] * c0 + m[11] * d0;
    d[i][j] = m[12] * a0 + m[13] * b0 + m[14] * c0 + m[15] * d0;
}
float spline::Matrix(int i, int j,float u)
{
    return(d[i][j] + u*c[i][j] + u*u*b[i][j] + u*u*u*a[i][j]);
}

spline::~spline()
{
    delete[] knots;
    delete[] Spline;
}
