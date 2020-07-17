#include "qwidgetserialtx.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

QWidgetSerialTx::QWidgetSerialTx(QWidget *parent) : QWidget(parent)
{
    this->serialInit();
}

void QWidgetSerialTx::serialInit()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
    }
}
