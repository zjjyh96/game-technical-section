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
    QPixmap pix;
    QWidget* menuWindow;
    QVBoxLayout* buttoms,* tools,*SpeedS;
    QHBoxLayout* speedlayout,* windowlayout;
    wwindow* w;

    QLineEdit* SpeedLine;
    QSlider *Speedslider;
    QLabel* SpeedLabel;
    QPushButton* Draw1Button,* Draw2Button,* ArrowButton,
               * CarButton,* HandButton,* LinearButton,
               * VectorButton,* ClearButton,* ShowButton,* HideButton;

public:
    mainwindow(QWidget* parent = 0);
public slots:
    void SpeedEdit(int value);
private slots:
    void Draw1update();
    void Draw2update();
    void linear();
    void vector();
    void clear();
    void DrawArrow();
    void Show();
    void Hide();
private:
//    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
