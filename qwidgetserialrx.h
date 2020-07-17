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
    char pkgDataCnt;
    char pkgDataHead;
    char pkgData[7];
    char pkgDataCrc;

    int ecg1, ecg2, ecg3;
    char status = 0;
    QSerialPort *com;
    int serialInit();
    void serialRx();
    void rxDataHandle(unsigned char data);

signals:

};

#endif // QWIDGETSERIALRX_H
