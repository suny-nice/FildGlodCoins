#include "playscene.h"
#include "coinbutton.h"
#include "dataconfig.h"

#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QPropertyAnimation>

PlayScene::PlayScene(int level, QWidget *parent)
    : MyMainWindow{parent}
{

    mHasWin = false;

    tSound = new QSoundEffect(this);

    //返回键按钮设置
    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->resize(72,32);

    connect(btnBack,&MyPushButton::clicked,[=](){
        emit this->backBtnClicked();
    });

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //在左下角添加Label
    QLabel *label = new QLabel(this);
    label->setFont(QFont("微软雅黑",20));
    label->resize(150,50);
    label->move(30,this->height()-label->height());
    label->setText(QString("Level: %1").arg(level));

    const int columnWidth = 58;
    const int rowHeight = 57;
    const int xOffset = 50;
    const int yOffset = 200;

    //取第几关的数据
    dataConfig date;
    QVector<QVector <int> > dateArr = date.mData[level];
    //创建翻金币按钮
    for(int row = 0; row < 4; ++row){
        for(int col = 0; col < 4 ; ++col){
            CoinButton *btn =  new CoinButton(this);
            //把按钮存储到mCoins[row][col]数组中
            mCoins[row][col] = btn;
            int x = xOffset + col * columnWidth;
            int y = yOffset + row * rowHeight;
            btn->setGeometry(x,y,55,55);
            //重新设置btn大小，让金币图片填满按钮
            btn->setStat(dateArr[row][col]);//设置row行col行，从dateConfig的数据中获取

            // 每次点击金币就改变其状态
            connect(btn,&CoinButton::clicked,[=](){
                //btn->flip(); //实现该翻转函数
                //点击一个翻转周围的硬币
                this->flip(row,col);
            });
        };

    }
}
//通过接收row, col来实现翻转(row,col)上下左右的四个硬币
void PlayScene::flip(int row, int col)
{

    if(mHasWin){
        return;
    }
    //金币翻转音效
    tSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    tSound->play();
    //为什么mCoins[row][col]能调用flip()?
    //所以此处需要把CoinButton类型的按钮存储到mCoins[row][col]中
    this->mCoins[row][col]->flip();
    QTimer::singleShot(260,[=](){
        if(row + 1 <4){
            this->mCoins[row+1][col]->flip();
        }
        if(row-1 >=0){
            this->mCoins[row-1][col]->flip();
        }

        if(col + 1 < 4){
            this->mCoins[row][col+1]->flip();
        }
        if(col - 1 >=0){
            this->mCoins[row][col-1]->flip();
        }

        //翻转完了，判断胜利条件
        this->judgeWin();
    });
}

void PlayScene::judgeWin()
{
    for(int row = 0; row < 4; row++){
        for(int col = 0; col <4; col++){
            if(!mCoins[row][col]->stat()){
                //只要有一个银币，就返回继续游戏
                return;
            }
        }
    }
    //全部都是金币的提示窗口
    //QMessageBox::information(this,"恭喜","游戏成功");
    //也可以使用动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);

    labelWin->resize(pix.size());
    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());
    labelWin->show();
    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画播放后删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    mHasWin = true;

    //胜利音频
    tSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    tSound->play();
}


void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题Logo,比关卡初的宽高都少一半
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width()/2,pix.height()/2,pix);

}

