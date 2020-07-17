#include "qwidgetdrawsin.h"
#include "ainwave.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>

QWidgetDrawSin::QWidgetDrawSin(QWidget *parent) : QWidget(parent)
{
    this->resize(10000,10000);
    this->map = new QPixmap(this->width(),this->height());

    this->map->fill(Qt::black);

    this->timer = new QTimer(parent);
    this->timer->start(3);//单位毫秒

//    connect(timer,&QTimer::timeout,this,&QWidgetDraw::refresh);
    connect(timer,&QTimer::timeout,this,&QWidgetDrawSin::sendData);

    connect(this,&QWidgetDrawSin::rxDataSingalSin,this,&QWidgetDrawSin::refreshFormData);
}


void QWidgetDrawSin::sendData()
{
    int data = 0;
    int height = this->height();

    data = sinWave[index]*height / 160000 + height / 2;

    this->index += 40;//隔三个取一个

    if(this->index >= sizeof(sinWave)/sizeof(int))//防止越界
            this->index = 0;

    emit rxDataSingalSin(data);

}

void QWidgetDrawSin::refreshFormData(int data)
{
    //更新图片缓存
    QPainter *painter = new QPainter();
    painter->begin(this->map);

    //配置画笔
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::red);
    painter->setPen(*pen);

    //画图到map(缓存)
    this->drawWave(painter,data);
    painter->end();

    this->update();
}

void QWidgetDrawSin::refresh()
{
    //更新图片缓存
    QPainter *painter = new QPainter(this);
    painter->begin(this->map);

    //画图到map(缓存)
    this->draw(painter);
    painter->end();

    this->update();
}


void QWidgetDrawSin::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter();

    painter->begin(this);
//    this->draw(painter);
    //画图到界面
    painter->drawPixmap(0,0,*this->map);
    painter->end();
}


 void QWidgetDrawSin::draw(QPainter *painter)
 {
     //配置画笔
     QPen *pen = new QPen();
     pen->setWidth(2);
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



void QWidgetDrawSin::drawWaveFromArray(QPainter *painter)
{
    int data = 0;
    int height = this->height();

    data = height -sinWave[index]*height/4096;
    this->drawWave(painter,data);

    this->index += 3;//隔三个取一个

    if(this->index >= sizeof(sinWave)/sizeof(int))//防止越界
            this->index = 0;


}

void QWidgetDrawSin::drawWave(QPainter *painter, int data)
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
