#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int stat() const;
    void setStat(int newStat);
    void resetStat();
    void flip();
    void setStateWithAnimation(int stat);


signals:

    void statChanged();
protected:
    void paintEvent(QPaintEvent *ev);


private:
    int mStat;
    Q_PROPERTY(int stat READ stat WRITE setStat RESET resetStat NOTIFY statChanged FINAL)

    int mFrame;

    QTimer timer;
};

#endif // COINBUTTON_H
