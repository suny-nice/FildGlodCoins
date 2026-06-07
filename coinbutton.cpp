#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent)
    : QPushButton{parent}
{
    //设置硬币状态（金币=1）
    this->setStat(1);
    //按钮不规则样式设置，改为无背景
    setStyleSheet("QPushButton{border:0px}");

    connect(&timer,&QTimer::timeout,[=](){
        if(this->mStat){
            this->mFrame--;
        }else{//金币变银币
            this->mFrame++;
        }

        QString frameName = QString(":/res/Coin000%1.png").arg(mFrame);
        this->setIcon(QIcon(frameName));
        //停止计时器
        if(this->mFrame == 8 || this->mFrame == 1)
        {
            this->timer.stop();
        }

    });
}

int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int newStat)
{
    if (mStat == newStat)
        return;
    mStat = newStat;
    emit statChanged();
    if(this->mStat){ //如果mStat=1 为真(金币)
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else{
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    this->setIconSize(this->size());//此处可能还未填满，由于在创建按钮后有重新设置了按钮
}

void CoinButton::resetStat()
{
    setStat({}); // TODO: Adapt to use your actual default value
}

void CoinButton::flip()//每次点击取反
{
    //this->setStat(!this->stat());
    this->setStateWithAnimation(!this->stat());
}

//翻金币的动画 用Qtimer+图片切换实现
void CoinButton::setStateWithAnimation(int stat)
{
    this->mStat = stat;
    //金币翻银币的过程 (mFrame从1～8的过程)
    if(this->mStat){   //mStat == 1 表示从0到1 银币变金币
        this->mFrame = 8;
    }
    else{//金币变银币
        this->mFrame = 1;
    }

    this->timer.start(35);


}

void CoinButton::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    QPushButton::paintEvent(ev);
}
