#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>

class dataConfig : public QObject
{
    Q_OBJECT
public:
    explicit dataConfig(QObject *parent = 0);

public:

    QMap<int, QVector< QVector<int> > >mData; //映射(key,value)   QVector< QVector<int> 二维数组
    //所以此处<int, QVector< QVector<int> > >   <第几关卡, 硬币的4x4排布>


signals:

public slots:
};

#endif // DATACONFIG_H
