#ifndef PIXEL_H
#define PIXEL_H

#include <QGraphicsItem>
#include <QRect>

class Pixel : public QGraphicsItem
{

public:
    Pixel(const QColor &color, int x, int y, int scale, QGraphicsItem *parent = 0);
    ~Pixel();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void setColor(const QColor &c) noexcept;
    void advance(int phase) Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
    QColor color;
    QRect rect;
};

#endif // PIXEL_H
