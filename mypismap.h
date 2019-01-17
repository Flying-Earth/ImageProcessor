#ifndef MYPISMAP_H
#define MYPISMAP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>
class Mypismap : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Mypismap(QGraphicsPixmapItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);//鼠标的触摸事件
    void wheelEvent(QGraphicsSceneWheelEvent*);//滚轴事件
    void reset();

signals:

public slots:

private:
    double rate;
};

#endif // MYPISMAP_H
