#ifndef WIDGET_H
#define WIDGET_H
//游戏开始界面
#include <QWidget>
#include "ThreeDog/tdwidget.h"
#include "ThreeDog/tdpushbutton.h"
#include "gamemain.h"

class Widget : public TDWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    //开始按钮点击触发的函数
    void startGame();
    ~Widget();
};

#endif // WIDGET_H




