#include "selectscene.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QPainter>
#include <QPixmap>

SelectScene::SelectScene(QWidget *parent)
    : MyMainWindow{parent}
{
    this->setWindowTitle("选择关卡");

    mSound = new QSoundEffect(this);

    //创建返回按钮
    backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    backBtn->setFixedSize(72,32);
    //移动到窗口右下角
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

//点击返回按钮发出关闭信号
    connect(backBtn,&MyPushButton::clicked,[=](){
        emit this->backBtnClicked();
    });

//创建关卡按钮
    //xy 偏移量
    const int xOffset = 25;
    const int yOffset = 130;
    //行高和列宽
    const int columnWidth = 70;
    const int rowHeight = 70;
    for(int i=0; i < 20; ++i){
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png","",this);
        //4x5布局，确定，每个按钮的行、列，其次在确定其坐标
        int row = i/4;
        int column = i%4;
        int x = xOffset + column * columnWidth;
        int y = yOffset + row * rowHeight;
        //在设置按钮宽高，不设置所有按钮是连在一起的
        btn->setGeometry(x, y, 57, 57);

        //这里设置的文字会被按钮图片覆盖，所以需要在MyPushButton里重新绘制文字
        //一般在一个按钮里画两张图用绘画设备QPixmap 和 绘画事件 两者叠加
        btn->setText(QString::number(i+1));


    //点击关卡按钮跳转页面
        connect(btn,&MyPushButton::clicked,[=](){
            mSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
            mSound->play();
            PlayScene *playScene = new PlayScene(i+1);
            playScene->setAttribute(Qt::WA_DeleteOnClose);
           playScene->show();
           this->hide();

           //保持窗口位置一致
           playScene->move(this->pos());

           connect(playScene,&PlayScene::backBtnClicked,[=](){
               mSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
               mSound->play();
               this->show();
               playScene->hide();

               //保持窗口位置一致
               this->move(playScene->pos());
           });
        });

    }

}
//绘制点击开始后页面切换的界面图片
void SelectScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题Logo
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
