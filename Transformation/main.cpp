#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainwindow w;
    w.show();

//    QPalette palette(w.palette());
//    //palette.setColor(QPalette::Background, Qt::blue);//windown background color setting
//    QPixmap pixmap = QPixmap("001.png").scaled(w.size());//picture routes
//    palette.setBrush(QPalette::Background, QBrush(pixmap));//window backgrount picture setting
//    w.setAutoFillBackground(true);
//    w.setPalette(palette);


    return a.exec();
}
