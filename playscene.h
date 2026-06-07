#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include "mymainwindow.h"
#include "coinbutton.h"
#include "mypushbutton.h"
#include <QMainWindow>
#include <QSoundEffect>

class PlayScene : public MyMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level, QWidget *parent = nullptr);

    void flip(int row, int col);
    void judgeWin();

signals:
    void backBtnClicked();

private:
    //胜利的状态
    bool mHasWin;
    void paintEvent(QPaintEvent *event);
    QSoundEffect *tSound;

    CoinButton *mCoins[4][4];
};

#endif // PLAYSCENE_H
