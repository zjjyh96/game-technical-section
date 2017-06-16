#include"mainwindow.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QPixmap>
#include<QPalette>

mainwindow::mainwindow(QWidget* parent):
    QWidget(parent)
//    ui(new Ui::Widget)
{
    w = new wwindow();



    //定义按钮
    Draw1Button = new QPushButton();
    Draw1Button->setText(tr("绘制起始形状"));
    Draw2Button = new QPushButton();
    Draw2Button->setText(tr("绘制结束形状"));

    ArrowButton = new QPushButton();
    ArrowButton->setText(tr("绘制预设箭头"));

//    CarButton = new QPushButton();
//    CarButton->setText(tr("绘制预设小车"));

//    HandButton = new QPushButton();
//    HandButton->setText(tr("绘制预设手臂"));

    LinearButton = new QPushButton();
    LinearButton->setText(tr("线性插值运动"));
    VectorButton = new QPushButton();
    VectorButton->setText(tr("矢量插值运动"));

    ShowButton = new QPushButton();
    ShowButton->setText(tr("显示路径"));
    HideButton = new QPushButton();
    HideButton->setText(tr("隐藏路径"));

    ClearButton = new QPushButton();
    ClearButton->setText(tr("清空画布"));

    SpeedLabel = new QLabel();
    SpeedLabel->setText(tr("运动速度："));
    SpeedLine = new QLineEdit();

    //定义滑动条
    Speedslider= new QSlider(Qt::Horizontal);
    Speedslider->setMinimum(0);
    Speedslider->setMaximum(100);
    Speedslider->setValue(50);
//    Speedslider->setFixedWidth(140);

    //初始生成轨迹按钮disable
    LinearButton->setDisabled(true);
    VectorButton->setDisabled(true);
    HideButton->setDisabled(true);

    //进行槽链接
    connect(Speedslider, SIGNAL(valueChanged(int)), this, SLOT(SpeedEdit(int)));

    connect(Draw1Button,SIGNAL(clicked()),this,SLOT(Draw1update()));
    connect(Draw2Button,SIGNAL(clicked()),this,SLOT(Draw2update()));

    connect(ClearButton,SIGNAL(clicked()),this,SLOT(clear()));
    connect(LinearButton,SIGNAL(clicked()),this,SLOT(linear()));
    connect(VectorButton,SIGNAL(clicked()),this,SLOT(vector()));

    connect(ArrowButton,SIGNAL(clicked()),this,SLOT(DrawArrow()));

    connect(ShowButton,SIGNAL(clicked()),this,SLOT(Show()));
    connect(HideButton,SIGNAL(clicked()),this,SLOT(Hide()));


    //设定初始文本内容
    SpeedLine->setText("50");

    //布局添加控件
    speedlayout= new QHBoxLayout();
    speedlayout->addWidget(SpeedLabel);
    speedlayout->addWidget(SpeedLine);

    SpeedS = new QVBoxLayout();
    SpeedS->addWidget(Speedslider);

    buttoms = new QVBoxLayout();
    buttoms->addWidget(ArrowButton);
//    buttoms->addWidget(CarButton);
//    buttoms->addWidget(HandButton);
    buttoms->addWidget(Draw1Button);
    buttoms->addWidget(Draw2Button);
    buttoms->addWidget(LinearButton);
    buttoms->addWidget(VectorButton);
    buttoms->addWidget(ClearButton);
    buttoms->addWidget(ShowButton);
    buttoms->addWidget(HideButton);

    tools= new QVBoxLayout();
    tools->addLayout(buttoms);
    tools->addLayout(speedlayout);
    tools->addLayout(SpeedS);

    menuWindow = new QWidget();
    menuWindow->setFixedWidth(150);
    menuWindow->setLayout(tools);

    //整合工具条与画板
    windowlayout = new QHBoxLayout();
    resize(800,450);
    windowlayout->addWidget(w);
    windowlayout->addWidget(menuWindow);

    //设置画面
    setLayout(windowlayout);
}

void mainwindow::Draw1update()
{
    w->mode=1;
    w->update();
}
void mainwindow::Draw2update()
{
    w->mode=2;
    LinearButton->setDisabled(false);
    VectorButton->setDisabled(false);
    w->update();
}
void mainwindow::linear()
{
    w->mode=3;
    w->startmove();
    w->update();
}
void mainwindow::vector()
{
    w->mode=4;
    w->startmove();
    w->update();
}

void mainwindow::DrawArrow()
{
    w->Arrow();
    LinearButton->setDisabled(false);
    VectorButton->setDisabled(false);
    w->update();
}


//清除界面
void mainwindow::clear()
{
    w->clear();
    LinearButton->setDisabled(true);
    VectorButton->setDisabled(true);
}

void mainwindow::SpeedEdit(int value)
{
  int pos = Speedslider->value();
  QString str = QString("%1").arg(pos);
  SpeedLine->setText(str);
  w->SetSpeed(pos);
  update();
}

//显示和隐藏路径槽函数
void mainwindow::Show(){
    ShowButton->setDisabled(true);
    HideButton->setDisabled(false);
    w->bshow=true;
    update();
}
void mainwindow::Hide(){
    ShowButton->setDisabled(false);
    HideButton->setDisabled(true);
    w->bshow=false;
    update();
}
