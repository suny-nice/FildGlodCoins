#ifndef STARTSCENE_H
#define STARTSCENE_H
#include "selectscene.h"

#include <QMainWindow>
#include <QSoundEffect>
#include "mymainwindow.h"
class StartScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit StartScene(QWidget *parent = nullptr);

signals:

private:
    SelectScene *mSelectScene;
    QSoundEffect *sound;
};

#endif // STARTSCENE_H
