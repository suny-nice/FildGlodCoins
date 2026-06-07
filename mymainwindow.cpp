#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPainter>
MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);


    //设置窗口标题、图片、大小
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));//mac电脑不显示
    this->setFixedSize(320,588);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}
//继承允许派生类继承基类的成员函数。如果派生类没有重写该个虚函数，则调用父类的
void MyMainWindow::paintEvent(QPaintEvent *event)
{//此处StartScene继承MyMainWindow的绘画事件，绘制背景图

    QPainter painter(this);
    QPixmap pix(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
