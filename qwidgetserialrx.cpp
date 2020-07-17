#include "qwidgetserialrx.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

QWidgetSerialRx::QWidgetSerialRx(QObject *parent) : QObject(parent)
{
    if(-1 == this->serialInit())
        return;

    //绑定串口有数信号和串口接收函数
    connect(this->com, &QSerialPort::readyRead, this, &QWidgetSerialRx::serialRx);
}

void  QWidgetSerialRx::serialRx()
{
    qDebug()<<"rx:"<<com->readAll();
}

int QWidgetSerialRx::serialInit()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
    }

    //创建串口对象
    this->com = new QSerialPort();
    //打开串口
    this->com->setPortName("COM10");
    //尝试打开
    if(!this->com->open(QIODevice::ReadWrite))
    {
        qDebug()<<"open serial error"<<this->com->portName();
        return -1;
    }
    else
        qDebug()<<"open serial sucess";

    //串口参数配置
    this->com->setBaudRate(QSerialPort::Baud115200);
    this->com->setDataBits(QSerialPort::Data8);
    this->com->setFlowControl(QSerialPort::NoFlowControl);
    this->com->setParity(QSerialPort::NoParity);
    this->com->setStopBits(QSerialPort::OneStop);

    return 0;

}
