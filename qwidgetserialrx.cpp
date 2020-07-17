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
    //定义数据接收缓存
    QByteArray data;
    //    qDebug()<<"rx:"<<com->readAll();
    //循环读全部数
    while(!com->atEnd())
    {
        //从串口读数
        QByteArray data = this->com->read(1);
        //数据处理
        this->rxDataHandle(data[0]);
    }

}

void QWidgetSerialRx::rxDataHandle(unsigned char data)
{
    char tmpData;
    //数据包格式：ID + 数据头 + 数据 + 校验
    //状态0.空闲时，判断进来的数据是不是ID，如果是进入下一步
    //状态1.接收数据头，进入下一步
    //状态2.接收数据，并还原数据，达到指定数据长度进入下一步
    //状态3.数据校验，如果校验正确，下一步

    //如果接收到最高位为0的数据复位状态机
    if(data < 0x80)
        this->status = 0;

    //状态机数据处理
    switch(this->status)
    {
    case 0://状态0，接收数据ID
    {
        if (0x08 == data)
        {
            this->status = 1;
            this->pkgDataCnt = 0;
        }else
            qDebug("unknown ID %x", data);
    }break;
    case 1: //状态1，接收数据头
    {
        this->pkgDataHead = data;
        //        this->pkgDataCnt += 1;
        this->status = 2;
    }break;
    case 2:
    {
        tmpData = data&0x7F;
        tmpData = tmpData | (((this->pkgDataHead >> (this->pkgDataCnt))&0x01) << 7);
        this->pkgData[this->pkgDataCnt] = tmpData;
        this->pkgDataCnt += 1;
        if(this->pkgDataCnt >= 7)
            this->status = 3;
    }break;
    case 3: //状态3，接收校验值
    {
        //得到ECG数据
        ecg1 = this->pkgData[0];
        ecg1 = ecg1<<8;
        ecg1 = ecg1 + this-> pkgData[1];

        ecg2 = this->pkgData[2];
        ecg2 = ecg2<<8;
        ecg2 = ecg2 + this-> pkgData[3];

        ecg3 = this->pkgData[4];
        ecg3 = ecg3<<8;
        ecg3 = ecg3 + this-> pkgData[5];

        //数据打印
        qDebug()<<"ecg1"<<ecg1<<"ecg2"<<ecg2<<"ecg3"<<ecg3;

    }break;
    }
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
