#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "qwidgetdraw.h"
#include "qwidgetdrawsin.h"
#include "qwidgetserialtx.h"
#include "qwidgetserialrx.h"

int main(int argc, char * argv[])
{
    QApplication a(argc,argv);
#if 0
    QWidget *winMain = new QWidget();
    winMain->setWindowTitle("实习起飞组");
    winMain->resize(1000,500);

    QPushButton *name = new QPushButton("实习起飞组:2017011301陈元臻");
    QWidgetDraw *drawWidget = new QWidgetDraw(winMain);
    QWidgetDrawSin *drawWidgetSin = new QWidgetDrawSin(winMain);

    QVBoxLayout *layoutMain = new QVBoxLayout();\
    layoutMain->addWidget(name);
    layoutMain->addWidget(drawWidget);
    layoutMain->addWidget(drawWidgetSin);

    layoutMain->setStretchFactor(name,3);
    layoutMain->setStretchFactor(drawWidget,20);
    layoutMain->setStretchFactor(drawWidgetSin,20);
     layoutMain->insertStretch(3,1);
    layoutMain->insertStretch(2,1);
    layoutMain->insertStretch(1,1);
    layoutMain->insertStretch(0,1);

    QHBoxLayout *layout = new QHBoxLayout();

    layout->addLayout(layoutMain);
    layout->setStretchFactor(layoutMain,40);
    layout->insertStretch(1,1);
    layout->insertStretch(0,1);

    winMain->setLayout(layout);
    winMain->show();
#endif

    QWidget *mainWin = new QWidget();
    QWidgetSerialTx *serialTx = new QWidgetSerialTx(mainWin);
    QWidgetSerialRx *serialRx = new QWidgetSerialRx(mainWin);
    mainWin->resize(300, 300);
    mainWin->show();

    return a.exec();
}
