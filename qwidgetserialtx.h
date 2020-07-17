#ifndef QWIDGETSERIALTX_H
#define QWIDGETSERIALTX_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>

class QWidgetSerialTx : public QWidget
{
    Q_OBJECT
public:
    QTimer *timer;
    QSerialPort *com;

    unsigned int index = 0;
    explicit QWidgetSerialTx(QWidget *parent = nullptr);
    void sendEcgPkg();
    int serialInit();
    unsigned int getEcg2Data();


signals:

};

#endif // QWIDGETSERIALTX_H
