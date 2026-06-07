#include "mypushbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>

//构建默认和按下显示图片路径，和初始化这两个属性
MyPushButton::MyPushButton(QString normalImgPath, QString pressImgPath, QWidget *parent)
    : QPushButton{parent}, mNormalImgPath(normalImgPath),mPressImgPath(pressImgPath)
{
    mStat = Normal;
}

void MyPushButton::paintEvent(QPaintEvent *event)
{
    //利用绘画事件绘制按钮
    QPainter painter(this);
    QPixmap pix;
    //根据状态选择
    if(mStat == Normal ){
        pix.load(mNormalImgPath);
    }
    if(mStat == Pressed){
        pix.load(mPressImgPath);
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    painter.drawText(-1,-1,this->width(),this->height(),Qt::AlignCenter,this->text());//mac与windows显示有点偏差，这里的x、y本应为(0,0),这里改为(-1,-1)
}


//实现按钮上下移动效果：
void MyPushButton::moveDown()
{
    //利用属性动画：1.位置大小 2.开始位置 3.结束位置 4.动画时长
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    this->mStat = Pressed;
    update();
    QPushButton::mousePressEvent(e);
}



void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->mStat = Normal;
    update();
    QPushButton::mouseReleaseEvent(e);
}

