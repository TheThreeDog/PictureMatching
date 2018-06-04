/**************************************************************
 * File Name   : tdfadeoutwidget.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 05 15:16:32 2017
 * Description : 渐隐渐显窗体，利用timer定时器事件设置窗体的透明度来实现
 *          淡入淡出的效果，定时器时间可由用户指定。
 *
 **************************************************************/
//2017/1/6
//存在问题，只能在单独窗体状态时实现透明渐变，如果是子窗体，则渐变失效

#include "tdfadeoutwidget.h"

#include <QDebug>

TDFadeoutWidget::TDFadeoutWidget(TDWidget *parent)
    :TDWidget(parent)
{
    init();
}

TDFadeoutWidget::TDFadeoutWidget(const QString &img_path, TDWidget *parent)
    :TDWidget(img_path,parent)
{
    init();
}

TDFadeoutWidget::TDFadeoutWidget(const QString &img_path, TDWidget *parent, bool show_window)
    :TDWidget(img_path,parent,show_window)
{
    init();
}

void TDFadeoutWidget::init()
{
    timer = new QTimer(this);
    is_hide = false;
    is_close = true;
    this->setWindowOpacity(0.0); //设置初始的透明度为全透明
    opacity_inc = 0.01;          //透明度增长值
    max_opacity = 1.0;           //最大透明度
    setFadeoutTime(0.2);            //通过秒数来设置定时器间隔
    is_display = false;          //是否显示着
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

double TDFadeoutWidget::getFadeoutTime()
{
    //获取所用的全部时间 = 透明度从零增长到1增长的次数*每次增长需要的秒数
    return (1/opacity_inc)*(timer_interval/1000);
}

void TDFadeoutWidget::setFadeoutTime(double second)
{
    //间隔时间 = 变化的总秒数/(透明度从零增长到1增长的次数) *1000换算成毫秒
    timer_interval = second/(1/opacity_inc)*1000;
}

TDFadeoutWidget::~TDFadeoutWidget()
{

}

void TDFadeoutWidget::timeout()
{
    //就是在定时器时间里按照设置好的间隔来进行
    if(is_display == true){
        if(this->windowOpacity() < 1.0)
            this->setWindowOpacity(this->windowOpacity()+opacity_inc);
        else
            timer->stop();
    }else{
        if(this->windowOpacity() > 0.0)
            this->setWindowOpacity(this->windowOpacity()-opacity_inc);
        else{
            //这里透明度已经为0了，在这里判断是否需要隐藏或者关闭窗体
            if(is_hide)
                TDWidget::hide();
            if(is_close)
                TDWidget::close();
            timer->stop();
        }

    }
}

void TDFadeoutWidget::hide()
{
    //因为隐藏事件不可用，所以重写只好hide槽函数，跟close原理一样。
    is_hide = true;
    timer->start(timer_interval);
    is_display = false;
}
//在外部调用close函数可以实现效果，主动点击关闭按钮无效
void TDFadeoutWidget::close()
{
    is_close = true;
    timer->start(timer_interval);
    is_display = false;
}

void TDFadeoutWidget::showEvent(QShowEvent *)
{
    timer->start(timer_interval);
    is_display = true;
}

void TDFadeoutWidget::closeEvent(QCloseEvent *e)
{
    //在关闭事件的时候无法实现渐隐效果，因为事件和定时器一起被触发
    //定时器还没执行完，窗体就关闭了
    is_close = true;
    timer->start(timer_interval);
    is_display = false;
}
