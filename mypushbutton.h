#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    explicit MyPushButton(QString normalImgPath,QString pressImgPath,QWidget *parent = nullptr);
    void moveDown();
    void moveUp();
    enum MyPushButtonStat
    {
        Normal,
        Pressed
    };
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

private:
    QString mNormalImgPath;//默认显示图路径
    QString mPressImgPath;//按下显示图路径

    MyPushButtonStat mStat;
};

#endif // MYPUSHBUTTON_H
