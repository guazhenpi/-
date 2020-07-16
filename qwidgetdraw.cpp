#include "qwidgetdraw.h"
#include <QPainter>


QWidgetDraw::QWidgetDraw(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("暑假实习起飞组");
}

void QWidgetDraw::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->drawLine(0,0,100,100);
    painter->drawRect(0,0,100,100);
}
