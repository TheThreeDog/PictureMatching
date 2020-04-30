#include "widget.h"
#include <QDebug>
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : TDWidget(":/img/welcome.png",parent)
{
    //生成开始游戏的按钮
    //参数（三态图片路径 + 父控件指针）
    TDPushButton *beginBtn = new TDPushButton(
                ":/img/begin_normal.png",
                ":/img/begin_hover.png",
                ":/img/begin_press.png",this);
    //把按钮放置在指定位置
    beginBtn->move(330,450);
    //给按钮指定一个触发的函数
    beginBtn->setCallback \
   (this,my_selector(Widget::startGame));//回调
}

void Widget::startGame()
{
    //qDebug()<<"start game!";
    //在此函数中实现页面跳转
    //生成新的窗体  游戏主界面
    GameMain *gm = new GameMain();
    //显示主界面
    gm->show();
    this->close();

}

Widget::~Widget()
{

}
