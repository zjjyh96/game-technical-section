#ifndef SPLINE_H
#define SPLINE_H

class point
{
public:
    float x;
    float y;
    void setPoint(float _x, float _y);
};

class spline
{
private:
    float a[2][50],b[2][50],c[2][50],d[2][50];//每段Cardinal曲线的参数
    float A[50], B[50], C[50], D[50], E[50];
    float m[16];//矩阵M
    point* knots;//插值点
    point* Spline;//曲线上点
    int grain;//每两个控制点之间的插值点数
    int n;//控制点的数量
    float tension;//参数t
    float Matrix(int i,int j,float u);
    void init(int i,int j,float a0, float b0, float c0, float d0);

public:
    spline(point* p, int _n, int _grain, float _tension);
    ~spline();
    void print();
    float getX(int i);
    float getY(int i);
    int size();
};

#endif // SPLINE_H
