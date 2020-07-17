#ifndef QWIDGETDRAWSIN_H
#define QWIDGETDRAWSIN_H

#include <QWidget>

class QWidgetDrawSin : public QWidget
{
    Q_OBJECT
public:
    QTimer *timer;
    QPixmap *map;
    int x = 0;
    int y = 0;
    int dir = 0;
    int cnt = 0;
    unsigned int index = 0;
    int lastData = 0;

    explicit QWidgetDrawSin(QWidget *parent = nullptr);

    void draw(QPainter *painter);
    void drawDemo(QPainter *painter);
    void drawTriangle(QPainter *painter);
    void drawTriangleNew(QPainter *painter);
    void drawWaveFromArray(QPainter *painter);
    void drawWave(QPainter *painter,int data);
    void sendData();
    void refresh();
    void refreshFormData(int data);
    void testRx(int data);

private:
    void paintEvent(QPaintEvent *event) override;

signals:
    void rxDataSingalSin(int data);
};

#endif // QWIDGETDRAW_H
