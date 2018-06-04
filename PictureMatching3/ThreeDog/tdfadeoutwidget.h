/**************************************************************
 * File Name   : tdfadeoutwidget.h
 * Author      : ThreeDog
 * Date        : Thu Jan 05 15:16:32 2017
 * Description : 渐隐渐显窗体，利用timer定时器事件设置窗体的透明度来实现
 *          淡入淡出的效果，定时器时间可由用户指定。
 *
 **************************************************************/
//2017/1/6
//存在问题，只能在单独窗体状态时实现透明渐变，如果是子窗体，则渐变失效
#ifndef _TDFADEOUTWIDGET_H_ 
#define _TDFADEOUTWIDGET_H_ 
#include "tdwidget.h"
#include <QTimer>
#include <QCloseEvent>
#include <QHideEvent>
#include <QThread>

class TDFadeoutWidget : public TDWidget
{
    Q_OBJECT

public:
    explicit TDFadeoutWidget(TDWidget* parent = 0);
    explicit TDFadeoutWidget(const QString &img_path,TDWidget *parent = 0);
    explicit TDFadeoutWidget(const QString &img_path,TDWidget *parent,bool show_window);
    void init();
    double getFadeoutTime();         //获取当前从不透明到全透明所用的时间
    void setFadeoutTime(const double second);//设置从不透明到全透明需要用的时间
    ~TDFadeoutWidget();
public slots:
    void timeout();
    void hide();
    void close();
protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    //void hideEvent(QHideEvent *);//在这里写是无效的，因为hide事件在窗体隐藏之后触发
private :
    double opacity_inc;//透明度增长值
    double max_opacity;//最大透明度
    bool is_display;   //是否显示着
    double timer_interval;//定时器间隔
    bool is_hide;      //是否隐藏此窗体？
    bool is_close;     //是否关闭此窗体？
    QTimer *timer;
};

#endif  //TDFADEOUTWIDGET
