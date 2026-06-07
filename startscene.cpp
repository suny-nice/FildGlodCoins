#include "startscene.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QTimer>
#include <QSoundEffect>

StartScene::StartScene(QWidget *parent)
    : MyMainWindow{parent}
{
    this->setWindowTitle("开始场景");

    MyPushButton *btnStar = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);
    btnStar->resize(114,114);
    btnStar->setFocusPolicy(Qt::NoFocus);
    //按钮在页面水平居中，垂直居中3/4的位置
    //x = 窗口宽度/2 - 按钮宽度/2       y= 窗口高度3/4 - 按钮高度/2
    btnStar->move((this->width() - btnStar->width())/2,this->height()*3/4 - btnStar->height()/2 );

    sound =  new QSoundEffect(this);

    mSelectScene = new SelectScene(this);
    // mSelectScene->setAttribute(Qt::WA_DeleteOnClose);
    connect(btnStar,&MyPushButton::clicked,[=](){

        //点击开始按钮音频
        sound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
        sound->play();
        //一开始就禁用按钮
        btnStar->setEnabled(false);
        btnStar->moveDown();//立即执行向下的动画
        //往上会覆盖往下的动画
        QTimer::singleShot(150,[=](){
            btnStar->moveUp();
        });

        QTimer::singleShot(300,[=](){
            btnStar->setEnabled(true);
            //场景转换
            this->hide();
            //获取父窗口的位置使其切换时不移动和设置窗口大小；
            //mac里的显示和windous不一样，会导致窗口大小不一样，直接把mSelectScene当成属性会导致窗口大小不一样，所以这里new
            QRect point = MyMainWindow::geometry();
            this->mSelectScene->move(point.x(),point.y()-27);//mac显示有问题所以这里简单-27保持窗口一致
            this->mSelectScene->setFixedSize(320,588);
            this->mSelectScene->show();

            //当前显示窗口mSelectScene移动到上一个窗口的位置
            this->mSelectScene->move(this->pos());
        });
    });

    //接收到backBtnClicked的信号关闭SelectScene窗口
    connect(this->mSelectScene,&SelectScene::backBtnClicked,[=](){
        //返回按钮点击音频
        sound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
        sound->play();
        this->show();
        this->mSelectScene->hide();

        //保持与原窗口位置一致
        this->move(this->mSelectScene->pos());
    });
}

