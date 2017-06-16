#include"mainwindow.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>

mainwindow::mainwindow(QWidget* parent):QWidget(parent)
{
    w = new wwindow();
    menuWindow = new QWidget();

    //定义按钮与输入框
    grainLabel = new QLabel();
    grainLabel->setText(tr("grain:"));
    tensionLabel = new QLabel();
    tensionLabel->setText(tr("tension:"));
    speedLabel = new QLabel();
    speedLabel->setText(tr("speed:"));
    genButton = new QPushButton();
    genButton->setText(tr("生成轨迹"));
    startButton = new QPushButton();
    startButton->setText(tr("开始运动"));
    clearButton = new QPushButton();
    clearButton->setText(tr("清空画布"));
    grainLine = new QLineEdit();
    tensionLine = new QLineEdit();
    speedLine = new QLineEdit();

    //定义滑动条
    tslider= new QSlider(Qt::Horizontal);
    tslider->setMinimum(0);
    tslider->setMaximum(100);
    tslider->setValue(100);
    tslider->setFixedWidth(140);

    gslider= new QSlider(Qt::Horizontal);
    gslider->setMinimum(1);
    gslider->setMaximum(50);
    gslider->setValue(50);
    gslider->setFixedWidth(140);

    sslider= new QSlider(Qt::Horizontal);
    sslider->setMinimum(1);
    sslider->setMaximum(100);
    sslider->setValue(100);
    sslider->setFixedWidth(140);

    //初始生成轨迹按钮disable
    startButton->setDisabled(true);

    //进行槽链接
    connect(tslider, SIGNAL(valueChanged(int)), this, SLOT(tensionEdit(int)));
    connect(gslider, SIGNAL(valueChanged(int)), this, SLOT(grainEdit(int)));
    connect(sslider, SIGNAL(valueChanged(int)), this, SLOT(speedEdit(int)));
    connect(genButton,SIGNAL(clicked()),this,SLOT(updatePaintWindow()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clear()));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));

    //设定初始文本内容
    grainLine->setText("50");
    grainLine->setFixedWidth(100);
    tensionLine->setText("1");
    tensionLine->setFixedWidth(100);
    speedLine->setText("100");
    speedLine->setFixedWidth(100);

    windowlayout = new QVBoxLayout();
    buttoms = new QVBoxLayout();
    bottomlayout= new QHBoxLayout();
    factors= new QGridLayout();

    //布局添加控件
    factors->addWidget(grainLabel,0,0);
    factors->addWidget(grainLine,0,1);
    factors->addWidget(gslider,0,2);

    factors->addWidget(tensionLabel,1,0);
    factors->addWidget(tensionLine,1,1);
    factors->addWidget(tslider,1,2);

    factors->addWidget(speedLabel,2,0);
    factors->addWidget(speedLine,2,1);
    factors->addWidget(sslider,2,2);

    buttoms->addWidget(genButton);
    buttoms->addWidget(startButton);
    buttoms->addWidget(clearButton);

    bottomlayout->addLayout(factors);
    bottomlayout->addLayout(buttoms);

    menuWindow->setFixedSize(400,100);
    menuWindow->setLayout(bottomlayout);

    //整合工具条与画板
    resize(400,450);
    windowlayout->addWidget(w);
    windowlayout->addWidget(menuWindow);

    //设置画面
    setLayout(windowlayout);
}

//画板更新
void mainwindow::updatePaintWindow()
{
    startButton->setDisabled(false);
    w->setSpline(grainLine->text().toInt(),tensionLine->text().toFloat());
    w->setCar(speedLine->text().toFloat());
    w->update();
}

//清除界面
void mainwindow::clear()
{
    w->clear();
    startButton->setDisabled(true);
}

//开始运动
void mainwindow::start()
{
    w->setCar(speedLine->text().toFloat());
    w->startMove();
}

void mainwindow::tensionEdit(int value)
{
  float pos = tslider->value()/100.0;
  QString str = QString("%1").arg(pos);
  tensionLine->setText(str);
  updatePaintWindow();
}

void mainwindow::grainEdit(int value)
{
  int pos = gslider->value();
  QString str = QString("%1").arg(pos);
  grainLine->setText(str);
  updatePaintWindow();
}

void mainwindow::speedEdit(int value)
{
  int pos = sslider->value();
  QString str = QString("%1").arg(pos);
  speedLine->setText(str);
  updatePaintWindow();
}
