#include "mypismap.h"

Mypismap::Mypismap(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(parent),
    rate(0.1)
{

}
void Mypismap::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    setPos(pos()+mapToParent(event->pos())-mapToParent(event->lastPos()));
}
void Mypismap::mousePressEvent(QGraphicsSceneMouseEvent *){

}
void Mypismap::wheelEvent(QGraphicsSceneWheelEvent *event){
    int delta=event->delta();
    double factor=scale();
    if(delta>0){
        factor*=(1+rate);
}
    if(delta<0){
        factor*=(1-rate);
    }
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(factor);//
}
void Mypismap::reset(){
    setPos(0,0);
    setScale(1);
}
