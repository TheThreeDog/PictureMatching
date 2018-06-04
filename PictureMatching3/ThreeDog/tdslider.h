/**************************************************************
 * File Name   : tdslider.h
 * Author      : ThreeDog
 * Date        : Tue Jan 03 15:59:31 2017
 * Description : 自定义滑块窗体，参数传递底色，前景色和滑块颜色，采用绘图事件
 *          在鼠标松开时触发操作，接口和QSlider尽量保持一致。
 *
 **************************************************************/
#ifndef _TDSLIDER_H_ 
#define _TDSLIDER_H_ 
#include "tdwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

class TDSlider :public TDWidget
{
    Q_OBJECT

public:

    explicit TDSlider(TDWidget *parent = 0,Qt::Orientation ot = Qt::Horizontal);
    explicit TDSlider(const QColor col_bak
                      ,const QColor col_fro
                      ,const QColor col_btn
                      ,TDWidget *parent = 0
                      ,Qt::Orientation ot = Qt::Horizontal);
    //所有属性的外部接口
    int getMinimum() const;
    int getMaximum() const;
    int getSliderPosition() const ;
    int getValue() const;
    int getSliderWidth() const ;
    int getSliderRadius() const ;

    ~TDSlider();
public slots:
    //外部接口设置为槽函数，可以供接收槽函数使用
    void setMinimum(const int min);
    void setMaximum(const int max);
    void setRange(const int min,const int max);
    void setOrientation(Qt::Orientation ot);
    void setSliderPosition(const int position);
    void setValue(int v);
    void setSliderWidth(const int width);
    void setSliderRadius(const int radius);
    //设置滑动条的颜色
    void setBackgroundColor(const QColor &color);
    void setFrontColor(const QColor &color);
    void setButtonColor(const QColor &color);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:
    //发送数值改变信号和位置改变信号
    void valueChanged(double);
    void positionChanged(double);
    void valueChanging(double);
    void positionChanging(double);
private:
    QColor col_background;
    QColor col_front;
    QColor col_button;
    //滑块范围的最小值
    int minimum;
    //滑块范围的最大值
    int maximum;
    //滑块窗体的方向
    Qt::Orientation orientation;
    //滑块的位置
    int slider_position;
    //滑块当前位置所指定的值
    int value;
    //记录鼠标是否按下的状态
    bool ispress;
    //滑动条宽度
    int slider_width;
    //滑块半径
    int slider_radius;

};

#endif  //TDSLIDER
