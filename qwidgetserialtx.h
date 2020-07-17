#ifndef QWIDGETSERIALTX_H
#define QWIDGETSERIALTX_H

#include <QWidget>

class QWidgetSerialTx : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetSerialTx(QWidget *parent = nullptr);

    void serialInit();
signals:

};

#endif // QWIDGETSERIALTX_H
