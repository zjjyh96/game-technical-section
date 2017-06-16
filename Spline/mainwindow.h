#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSlider>


class QHBoxLayout;
class QVBoxLayout;


class mainwindow : public QWidget
{
    Q_OBJECT
private:
    QWidget* menuWindow;
    QVBoxLayout* windowlayout,* buttoms;
    QHBoxLayout* bottomlayout;
    QGridLayout* factors;
    wwindow* w;

    QLineEdit* grainLine,* tensionLine,* speedLine;
    QSlider *tslider,* gslider, *sslider;
    QLabel* grainLabel,* tensionLabel,* speedLabel;
    QPushButton* genButton,* startButton,* clearButton;

public:
    mainwindow(QWidget* parent = 0);
public slots:
    void tensionEdit(int value);
    void grainEdit(int value);
    void speedEdit(int value);
private slots:
    void updatePaintWindow();
    void clear();
    void start();
};

#endif // MAINWINDOW_H
