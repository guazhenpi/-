#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include"qwidgetdemo.h"

void layoutDemo2(void)
{
    QWidget *demoWidgetMain = new QWidget();
    demoWidgetMain->resize(150,400);

    QWidgetDemo *demoWidget1 = new QWidgetDemo();
    QWidgetDemo *demoWidget2 = new QWidgetDemo();
    QWidgetDemo *demoWidget3 = new QWidgetDemo();

    //创建垂直布局器
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(demoWidget1);
    layout->addWidget(demoWidget2);
    layout->addWidget(demoWidget3);

    demoWidgetMain->setLayout(layout);
    demoWidgetMain->show();
}

void layoutDemo1(void)
{
    //创建界面
    QWidget *winMain = new QWidget();

    //设计截面尺寸
    winMain->resize(800,400);

    //创建按钮
    QPushButton *btn1 = new QPushButton("财富+1");
    QPushButton *btn2 = new QPushButton("财富+10");
    QPushButton *btn3 = new QPushButton("财富+99999999");
# if 0
    //参数按钮打印
    qDebug()<<btn1->sizeHint();
    qDebug()<<btn1->size();
    qDebug()<<btn1->minimumSizeHint();
    qDebug()<<btn1->minimumSize();

    //配置按钮尺寸
//    btn1->setMinimumSize(500,100);
//    btn1->setMaximumSize(500,100);
//    btn2->setMinimumSize(500,100);
//    btn2->setMaximumSize(500,100);
//    btn3->setMinimumSize(500,100);
//    btn3->setMaximumSize(500,100);
# endif

    //配置策略参数
    btn1->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    btn2->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    btn3->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
//    btn3->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);

    //创建布局器
    QHBoxLayout *layoutMain = new QHBoxLayout();
    //根据添加顺序排序
    layoutMain->addWidget(btn1);
    layoutMain->addWidget(btn2);
    layoutMain->addWidget(btn3);

    //拉伸因子
//    layoutMain->setStretch(0,2);
//    layoutMain->setStretch(1,2);
//    layoutMain->setStretch(2,2);
    layoutMain->setStretchFactor(btn1,2);
    layoutMain->setStretchFactor(btn2,2);
    layoutMain->setStretchFactor(btn3,2);
//    layoutMain->insertSpacing(1,100);
    layoutMain->insertStretch(3,1);
    layoutMain->insertStretch(2,1);
    layoutMain->insertStretch(1,1);
    layoutMain->insertStretch(0,1);

    //创建垂直布局器
    QVBoxLayout *layout = new QVBoxLayout();

    //拉伸因子
    layout->addLayout(layoutMain);
    layout->setStretchFactor(layoutMain,1);
    layout->insertStretch(1,1);
    layout->insertStretch(0,1);

    //吧布局器应用到窗口
    winMain->setLayout(layout);
    winMain->show();

}


void layoutDemo0(void)
{

    //创建界面
    QWidget *winMain = new QWidget();

    //设计截面尺寸
    winMain->resize(800,400);
    //创建水平箱式布局器
    QHBoxLayout *hlayoutMain = new QHBoxLayout();

    //布局器添加按钮
    hlayoutMain->addWidget(new QPushButton("财富+1"));

    hlayoutMain->addWidget(new QPushButton("财富+100"));
    hlayoutMain->addWidget(new QPushButton("财富+9999999"));

    //创建垂直箱式布局器
    QVBoxLayout *vlayoutMain = new QVBoxLayout();

    //布局器添加按钮
    vlayoutMain->addWidget(new QPushButton("寿命+1"));
    vlayoutMain->addWidget(new QPushButton("寿命+100"));
    vlayoutMain->addWidget(new QPushButton("寿命+9999999"));

    //创建布局器
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(vlayoutMain);
    layoutMain->addLayout(hlayoutMain);

    //吧布局器应用到窗口
    winMain->setLayout(layoutMain);
    winMain->show();


}
