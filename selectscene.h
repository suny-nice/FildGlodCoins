#ifndef SELECTSCENE_H
#define SELECTSCENE_H
#include "mymainwindow.h"
#include "mypushbutton.h"
#include <QSoundEffect>

class SelectScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit SelectScene(QWidget *parent = nullptr);

signals:
    void backBtnClicked();
private:
    void paintEvent(QPaintEvent *event);
    MyPushButton *backBtn;

    QSoundEffect *mSound;
};

#endif // SELECTSCENE_H
