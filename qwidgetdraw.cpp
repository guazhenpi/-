#include "qwidgetdraw.h"
#include "wave.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QResizeEvent>

QWidgetDraw::QWidgetDraw(QWidget *parent) : QWidget(parent)
{
    this->resize(10000,10000);
    this->map = QPixmap(this->width(),this->height());

    this->map.fill(Qt::black);

    this->timer = new QTimer(parent);
    this->timer->start(3);//单位毫秒

//    connect(timer,&QTimer::timeout,this,&QWidgetDraw::refresh);
    connect(timer,&QTimer::timeout,this,&QWidgetDraw::sendData);

    connect(this,&QWidgetDraw::rxDataSingal,this,&QWidgetDraw::refreshFormData);
    connect(this,&QWidgetDraw::rxDataSingal,this,&QWidgetDraw::testRx);
}

void QWidgetDraw::resizeEvent(QResizeEvent *event)
{
    QPixmap cleanMap = QPixmap(this->width(), this->height());
    cleanMap.fill(Qt::black);
    this->map = cleanMap;
    this->x = 0;
}

void QWidgetDraw::testRx(int data)
{
    qDebug()<<"Rx:"<<data;
}

void QWidgetDraw::sendData()
{
    int data = 0;
    int height = this->height();

    data = height -etcWave[index]*height/4096;

    this->index += 3;//隔三个取一个

    if(this->index >= sizeof(etcWave)/sizeof(int))//防止越界
            this->index = 0;

    emit rxDataSingal(data);

}

void QWidgetDraw::refreshFormData(int data)
{
    //更新图片缓存
    QPainter *painter = new QPainter();
    painter->begin(&(this->map));

    //配置画笔
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::green);
    painter->setPen(*pen);

    //画图到map(缓存)
    this->drawWave(painter,data);
    painter->end();

    this->update();
}

void QWidgetDraw::refresh()
{
    //更新图片缓存
    QPainter *painter = new QPainter(this);
    painter->begin(&(this->map));

    //画图到map(缓存)
    this->draw(painter);
    painter->end();

    this->update();
}


void QWidgetDraw::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter();

    painter->begin(this);
//    this->draw(painter);
    //画图到界面
    painter->drawPixmap(0,0,this->map);
    painter->end();
}

void QWidgetDraw::drawDemo(QPainter *painter)
{
    QPen *pen = new QPen();
    //配置画笔
    pen->setColor(Qt::green);

    //存储配置
    painter->save();
    painter->setPen(*pen);
    //画图
    painter->drawRect(0,0,100,100);
    //重新加载原来配置
    painter->restore();
}

 void QWidgetDraw::draw(QPainter *painter)
 {
     //配置画笔
     QPen *pen = new QPen();
     pen->setWidth(20);
     pen->setColor(Qt::red);
     painter->setPen(*pen);
/*
//     this->drawDemo(painter);

     //绘图
//     painter->drawLine(0,0,100,100);
//     painter->drawLine(0,0,50,100);
//     this->drawTriangle(painter);
     */
     drawWaveFromArray(painter);
 }

void QWidgetDraw::drawWaveFromArray(QPainter *painter)
{
    int data = 0;
    int height = this->height();

    data = height -etcWave[index]*height/4096;
    this->drawWave(painter,data);

    this->index += 3;//隔三个取一个

    if(this->index >= sizeof(etcWave)/sizeof(int))//防止越界
            this->index = 0;


}

void QWidgetDraw::drawWave(QPainter *painter, int data)
{
//    int data = 0;
//    drawWave(painter,data);
    int width = this->width();
    int height = this->height();
    //创建画笔
    QPen *pen = new QPen();
    //参数配置
    pen->setWidth(20);
    pen->setColor(Qt::black);

    //保持配置
    painter->save();
    //西欧你的配种
    painter->setPen(*pen);

    //擦除
    painter->drawLine(this->x+10,0,this->x+10,height);
    //还原配置
    painter->restore();

//    painter->drawPoint(x,height - ecgWave[index]*height/4096);
    painter->drawLine(this->x-1,lastData,this->x,data);
    lastData = data;

    //下个点
    this->x += 1;

    if(x >= width)
        x = 0;
}
