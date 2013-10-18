#include "GUIPixel.h"
#include <QPainter>

GUIPixel::~GUIPixel(){

}

GUIPixel::GUIPixel(const QColor &color, int x, int y, int scale, QGraphicsItem *parent)
    :QGraphicsItem(parent), color(color),rect(x, y, scale, scale)
{
    setPos(mapToParent(rect.x(), rect.y()));
}

void GUIPixel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect);

}

QRectF GUIPixel::boundingRect() const{
    return rect;
}

void GUIPixel::setColor(const QColor &c) noexcept{
    color = c;

}

void GUIPixel::advance(int phase){
    if(phase == 1){
        color = color == Qt::yellow ? Qt::red : Qt::yellow;
    }
}
