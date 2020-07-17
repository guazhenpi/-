#ifndef QWIDGETSERIALRX_H
#define QWIDGETSERIALRX_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>

class QWidgetSerialRx : public QObject
{
    Q_OBJECT
public:
    explicit QWidgetSerialRx(QObject *parent = nullptr);

    QSerialPort *com;
    int serialInit();
    void serialRx();

signals:

};

#endif // QWIDGETSERIALRX_H
