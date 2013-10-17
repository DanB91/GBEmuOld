#include "Pixel.h"
#include <QPainter>

Pixel::~Pixel(){

}

Pixel::Pixel(const QColor &color, int x, int y, int scale, QGraphicsItem *parent)
    :QGraphicsItem(parent), color(color),rect(x, y, scale, scale)
{
    setPos(mapToParent(rect.x(), rect.y()));
}

void Pixel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect);

}

QRectF Pixel::boundingRect() const{
    return rect;
}

void Pixel::setColor(const QColor &c) noexcept{
    color = c;

}

void Pixel::advance(int phase){
    if(phase == 1){
        color = color == Qt::yellow ? Qt::red : Qt::yellow;
    }
}
