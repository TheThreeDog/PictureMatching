/**************************************************************
 * File Name   : tdscrollarea.h
 * Author      : ThreeDog
 * Date        : Mon Jan 09 15:13:51 2017
 * Description : 滚动区域，内部放置一个透明的子窗体，在子窗体中添加控件，如果子窗体
 *          大小超过外部窗体，就显示出来滚动条，滚动条大小规格由主窗体占子窗体比例调控
 *              滚动条的类也封装在这个文件中
 *
 **************************************************************/
#ifndef _TDSCROLLAREA_H_ 
#define _TDSCROLLAREA_H_ 
#include "tdwidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QEvent>
#include <QResizeEvent>
#include <QWheelEvent>
//滚动窗体中的滚动条类
class TDScrollBar : public TDWidget
{
    Q_OBJECT

public :
    //初始化接口，背景色，前景色，父控件
    explicit TDScrollBar(const QColor back_col ,const QColor fron_col,TDWidget *parent,Qt::Orientation ot = Qt::Vertical);
    double getPosition() const ;
    double getRadius() const ;
    double getWidth() const ;
    int getOpacityShow() const;
    int getOpacityHide() const;
    ~TDScrollBar();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
public slots:
    //设置滑块的位置和长度
    void setSliderPosition(const double pos);
    void setSliderLength(const double length);
    //设置圆角矩形滑块的圆角半径
    void setRadius(const double radius);
    void setWidth(const double wid);
    //关联窗体
    void connectToWidget(QWidget *w);
    //设置滑块颜色
    void setSliderColor(const QColor &col_back,const QColor &col_front);

    void setOpacityShow(const int opacity);
    void setOpacityHide(const int opacity);
private :
    //滑槽的方向：水平还是竖直
    Qt::Orientation orientation;
    //鼠标在滑槽是显示的颜色
    QColor col_back_show;
    QColor col_front_show;
    //鼠标离开状态下的颜色
    QColor col_back_hide;
    QColor col_front_hide;
    //正在显示的颜色
    QColor back_on_show;
    QColor front_on_show;
    //鼠标是否按下
    bool is_press ;
    double length;          //滑槽总长度
    double slider_length;   //滑动条长度
    double position;
    double radius;
    //滑条的宽度
    double width;
    //滑槽所关联的窗体，滑槽移动，控制哪个窗体移动相应的位置。

    //滑槽的透明度
    int opacity_show;
    int opacity_hide;
    QWidget * connect_widget;
};

class TDScrollArea :public TDWidget
{
    Q_OBJECT

public:

    explicit TDScrollArea(QWidget *parent = 0);
    QWidget * widget();
    void setWidget(QWidget * w);
    void removeWidget();
    //设置和获取滑轮步长
    int wheelStep() const;
    void setWheelStep(const int step);

    int getVerticalSliderWidth() const ;
    int getHorizontalSliderWidth() const;
    int getVerticalSliderRadius() const ;
    int getHorizontalSliderRadius() const;
    TDScrollBar * getHorizontalScroll();
    TDScrollBar * getVerticalScroll();

    ~TDScrollArea();
public slots:
    void setSliderWidth(const int width);
    void setSliderRadius(const int radius);
    void setSliderColor(const QColor &col_back,const QColor &col_front);
    void setSliderOpacity(const int show_opacity,const int hide_opacity);
    void setVerticalSliderWidth(const int width);
    void setVerticalSliderRadius(const int radius);
    void setVerticalSliderColor(const QColor &col_back,const QColor &col_front);
    void setVerticalSliderOpacity(const int show_opacity,const int hide_opacity);
    void setHorizontalSliderWidth(const int width);
    void setHorizontalSliderRadius(const int radius);
    void setHorizontalSliderColor(const QColor &col_back,const QColor &col_front);
    void setHorizontalSliderOpacity(const int show_opacity,const int hide_opacity);

protected:
    //大小改变的时候，滚动槽的大小也要改变
    void resizeEvent(QResizeEvent *);
    void wheelEvent(QWheelEvent *);
    //子窗体，子类还要需要继承操作此窗体，所以设为保护。
    QWidget * sub_widget;
private:
    TDScrollBar * scroll_h;
    TDScrollBar * scroll_v;
    int wheel_step;
};

#endif  //TDSCROLLAREA
