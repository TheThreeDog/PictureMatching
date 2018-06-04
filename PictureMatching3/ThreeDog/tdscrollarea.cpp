/**************************************************************
 * File Name   : tdscrollarea.cpp
 * Author      : ThreeDog
 * Date        : Mon Jan 09 15:13:51 2017
 * Description : 滚动区域，内部放置一个透明的子窗体，在子窗体中添加控件，如果子窗体
 *          大小超过外部窗体，就显示出来滚动条，滚动条大小规格由主窗体占子窗体比例调控
 *
 **************************************************************/

#include "tdscrollarea.h"
#include <QDebug>
#include <QPalette>
#include <QVBoxLayout>
TDScrollBar::TDScrollBar(const QColor back_col, const QColor fron_col, TDWidget *parent, Qt::Orientation ot)
    :TDWidget(parent)
{
    //初始化透明度
    opacity_show = 255;
    opacity_hide = 180;

    this->setSliderColor(back_col,fron_col);
    //以上初始化颜色 、、、、、、、、、、、、、、、、、、、
    this->orientation = ot;
    is_press = false;
    //滑条的宽度
    width = 10;
    //滑块半径
    radius = width/2;
    //设置长度
    if(Qt::Horizontal == ot){
        this->resize(parent->width(),width);
    }
    else if(Qt::Vertical == ot){
        this->resize(width,parent->height());
    }

}

//获取滑块的位置（左，上）
double TDScrollBar::getPosition() const
{
    return this->position;
}

//获取滑块半径
double TDScrollBar::getRadius() const
{
    return this->radius;
}

//获取滑槽的宽度
double TDScrollBar::getWidth() const
{
    return this->width;
}

int TDScrollBar::getOpacityShow() const
{
    return this->opacity_show;
}

int TDScrollBar::getOpacityHide() const
{
    return this->opacity_hide;
}

TDScrollBar::~TDScrollBar()
{

}

void TDScrollBar::mousePressEvent(QMouseEvent *e)
{
    //竖直方向
    if(Qt::Vertical == orientation){
        if(e->y() - slider_length/2 < 0)
            position = 0;
        else if(e->y() + slider_length/2 > parentWidget()->height() ){
            position = this->height()-slider_length;
        }
        else {
            position = e->y()-slider_length/2;
        }
        //        //注意这里是负的
        //        connect_widget->move(connect_widget->x(),
        //                             -connect_widget->height()*position/parentWidget()->height());

    }
    //水平方向
    else if(Qt::Horizontal == orientation){
        if(e->x()-slider_length/2 < 0)
            position = 0;
        else if(e->x() + slider_length/2 > parentWidget()->width()){
            position = parentWidget()->width()-slider_length;
        }
        else {
            position = e->x()-slider_length/2;
        }
        //        //注意这里是负的
        //        connect_widget->move(-connect_widget->width()*position/parentWidget()->width(),
        //                             connect_widget->y());

    }
    is_press = true;
    update();
}

void TDScrollBar::mouseMoveEvent(QMouseEvent *e)
{
    if(is_press){
        //竖直方向
        if(Qt::Vertical == orientation){
            if(e->y()-slider_length/2 < 0)
                position = 0;
            else if(e->y() + slider_length/2 > parentWidget()->height() ){
                position = this->height()-slider_length+1;
            }
            else {
                position = e->y()-slider_length/2;
            }
            //            //注意这里是负的
            //            connect_widget->move(connect_widget->x(),
            //                                 -connect_widget->height()*position/parentWidget()->height());
        }
        //水平方向
        else if(Qt::Horizontal == orientation){
            if(e->x()-slider_length/2 < 0)
                position = 0;
            else if(e->x() + slider_length/2 > parentWidget()->width()){
                position = parentWidget()->width()-slider_length;
            }
            else {
                position = e->x()-slider_length/2;
            }
            //            //注意这里是负的
            //            connect_widget->move(-connect_widget->width()*position/parentWidget()->width(),
            //                                 connect_widget->y());

        }
        update();
    }
}

void TDScrollBar::mouseReleaseEvent(QMouseEvent *)
{
    is_press = false;

}

void TDScrollBar::enterEvent(QEvent *)
{
    back_on_show = col_back_show;
    front_on_show = col_front_show;
    update();
}

void TDScrollBar::leaveEvent(QEvent *)
{
    back_on_show = col_back_hide;
    front_on_show = col_front_hide;
    update();
}

//绘图事件，绘制这个滑动槽
void TDScrollBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //注意参数 x,y,width,height
    if(Qt::Vertical == orientation){
        //竖直方向
        QRect back_rect(0,0,this->width,parentWidget()->height());
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(back_on_show));
        painter.drawRoundedRect(back_rect,radius,radius);
        QRect slider_rect(0,position,this->width,this->slider_length);
        painter.setPen(Qt::NoPen);
        painter.setBrush(front_on_show);
        painter.drawRoundedRect(slider_rect,radius,radius);
        //注意这里是负的
        connect_widget->move(connect_widget->x(),
                             -connect_widget->height()*position/parentWidget()->height());

    }else if(Qt::Horizontal == orientation){
        QRect back_rect(0,0,parentWidget()->width(),this->width);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(back_on_show));
        painter.drawRoundedRect(back_rect,radius,radius);
        QRect slider_rect(position,0,this->slider_length,this->width);
        painter.setPen(Qt::NoPen);
        painter.setBrush(front_on_show);
        painter.drawRoundedRect(slider_rect,radius,radius);
        //注意这里是负的
        connect_widget->move(-connect_widget->width()*position/parentWidget()->width(),
                             connect_widget->y());

    }

}

//设置位置
void TDScrollBar::setSliderPosition(const double pos)
{

    this->position = pos;
    update();
}

//设置滑条长度
void TDScrollBar::setSliderLength(const double length)
{
    this->slider_length  = length;
    update();
}

//设置半径
void TDScrollBar::setRadius(const double radius)
{
    this->radius = radius;
    update();
}

//设置滑条宽度
void TDScrollBar::setWidth(const double wid)
{
    this->width = wid;
    this->radius = wid/2;
    update();
}

//关联一个窗体，控制关联的窗体的移动
void TDScrollBar::connectToWidget(QWidget *w)
{
    connect_widget = w;
    //设置位置
    //纵向  //横向相反
    //关联窗体的位置纵坐标(负数)/关联窗体的总高度 * 滑槽总长度
    if(Qt::Vertical == orientation){
        double cwy = connect_widget->y();
        double cwh = connect_widget->height();
        double pwh = parentWidget()->height();
        position = cwy/cwh*pwh;
        this->resize(width,parentWidget()->height());
    }
    else if(Qt::Horizontal == orientation){
        double cwx = connect_widget->x();
        double cww = connect_widget->width();
        double pww = parentWidget()->width();
        position = cwx/cww*pww;
        this->resize(parentWidget()->width(),width);
    }
    //此时位置position如果为负数，则取绝对值即可
    //如果是负数，说明窗体在右或下部分，超出了则位置设为0
    if(position < 0)
        position = -position;
    else
        position = 0;
    //设置滑条长度
    if(Qt::Vertical == orientation){
        //主窗体长度 >= 子窗体长度 则不需要滑动条，隐藏此窗体
        if(parentWidget()->height() >= connect_widget->height()){
            slider_length = 0;
            this->hide();
        }else {
            //如果窗体是隐藏的要显示出来
            if(this->isHidden())
                this->show();
            //滑块长度 = 主窗体长度/关联窗体长度*滑条长度
            //注意这里的计算方式：要用double，不能用int，否则的结果为零
            double ph = parentWidget()->height();
            double ch = connect_widget->height();
            slider_length = ph/ch*ph;
        }
    }
    else if(Qt::Horizontal == orientation){
        //主窗体长度 >= 子窗体长度 则不需要滑动条，隐藏此窗体
        if(parentWidget()->width() >= connect_widget->width()){
            slider_length = 0;
            this->hide();
        }else{
            //如果窗体是隐藏的要显示出来
            if(this->isHidden())
                this->show();
            //滑块长度 = 主窗体长度/关联窗体长度*滑条长度
            //注意这里的计算方式：要用double，不能用int，否则的结果为零
            double pw = parentWidget()->width();
            double cw = connect_widget->width();
            slider_length = pw/cw*pw;

        }
    }
}

void TDScrollBar::setSliderColor(const QColor &col_back, const QColor &col_front)
{
    //鼠标在滑槽时显示的颜色
    col_back_show = QColor(col_back.red(),col_back.green(),col_back.blue(),opacity_show);
    col_front_show = QColor(col_front.red(),col_front.green(),col_front.blue(),opacity_show);

    //如果不在滑槽时，显示减opacity透明度的颜色
    int hide_r = col_back_show.red();
    int hide_g = col_back_show.green();
    int hide_b = col_back_show.blue();
    col_back_hide = QColor(hide_r,hide_g,hide_b,opacity_hide);
    hide_r = col_front_show.red();
    hide_g = col_front_show.green();
    hide_b = col_front_show.blue();
    col_front_hide = QColor(hide_r,hide_g,hide_b,opacity_hide);

    back_on_show = col_back_hide;
    front_on_show = col_front_hide;

}

void TDScrollBar::setOpacityShow(const int opacity)
{
    this->opacity_show = opacity;
    this->setSliderColor(col_back_show,col_front_show);
}

void TDScrollBar::setOpacityHide(const int opacity)
{
    this->opacity_hide = opacity;
    this->setSliderColor(col_back_hide,col_front_hide);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~``

TDScrollArea::TDScrollArea(QWidget *parent)
    :TDWidget(parent)
{
    sub_widget = NULL;
    scroll_h = NULL;
    scroll_v = NULL;
    this->setMoveEnable(false);
}

QWidget *TDScrollArea::widget()
{
    return sub_widget;

}

void TDScrollArea::setWidget(QWidget *w)
{
    //如果不为空相当于重设子窗体，需要释放之前的资源
    removeWidget();

    //加入子窗体并重设其父控件
    sub_widget = w;
    if(sub_widget == NULL)
        return ;
    sub_widget->setParent(this);
    sub_widget->move(0,0);
    sub_widget->show();

    scroll_h = new TDScrollBar(QColor(75,75,75),QColor(200,200,200),this,Qt::Horizontal);
    scroll_h->move(0,this->height()-scroll_h->getWidth());
    scroll_h->connectToWidget(sub_widget);

    scroll_v = new TDScrollBar(QColor(75,75,75),QColor(200,200,200),this,Qt::Vertical);
    scroll_v->move(this->width()-scroll_v->getWidth(),0);
    scroll_v->connectToWidget(sub_widget);
    this->wheel_step = 30;
}

//移除窗体，清理内存
void TDScrollArea::removeWidget()
{
    if(sub_widget != NULL){
        sub_widget->close();
        delete sub_widget;
        sub_widget = NULL;

        if(NULL != scroll_h ){
            scroll_h->close();
            delete scroll_h;
            scroll_h = NULL;
        }
        if(NULL != scroll_v){
            scroll_v->close();
            delete scroll_v;
            scroll_v = NULL;
        }
    }
}

int TDScrollArea::wheelStep() const
{
    return wheel_step;
}

void TDScrollArea::setWheelStep(const int step)
{
    wheel_step = step;
}

int TDScrollArea::getVerticalSliderWidth() const
{
    return this->scroll_v->getWidth();
}

int TDScrollArea::getHorizontalSliderWidth() const
{
    return this->scroll_h->getWidth();
}

int TDScrollArea::getVerticalSliderRadius() const
{
    return this->scroll_v->getRadius();
}

int TDScrollArea::getHorizontalSliderRadius() const
{
    return this->scroll_h->getRadius();
}

TDScrollBar *TDScrollArea::getHorizontalScroll()
{
    return this->scroll_h;
}

TDScrollBar *TDScrollArea::getVerticalScroll()
{
    return this->scroll_v;
}

TDScrollArea::~TDScrollArea()
{

}

void TDScrollArea::setSliderWidth(const int width)
{
    scroll_v->setWidth((double)width);
    scroll_h->setWidth((double)width);
}

void TDScrollArea::setSliderRadius(const int radius)
{
    scroll_v->setRadius((double)radius);
    scroll_h->setRadius((double)radius);
}

void TDScrollArea::setSliderColor(const QColor &col_back, const QColor &col_front)
{
    scroll_v->setSliderColor(col_back,col_front);
    scroll_h->setSliderColor(col_back,col_front);
}

void TDScrollArea::setSliderOpacity(const int show_opacity, const int hide_opacity)
{
    scroll_v->setOpacityShow(show_opacity);
    scroll_v->setOpacityHide(hide_opacity);
    scroll_h->setOpacityShow(show_opacity);
    scroll_h->setOpacityHide(hide_opacity);
}

void TDScrollArea::setVerticalSliderWidth(const int width)
{
    scroll_v->setWidth((double)width);
}

void TDScrollArea::setVerticalSliderRadius(const int radius)
{
    scroll_v->setRadius((double)radius);
}

void TDScrollArea::setVerticalSliderColor(const QColor &col_back, const QColor &col_front)
{
    scroll_v->setSliderColor(col_back,col_front);
}

void TDScrollArea::setVerticalSliderOpacity(const int show_opacity, const int hide_opacity)
{
    scroll_v->setOpacityShow(show_opacity);
    scroll_v->setOpacityHide(hide_opacity);
}

void TDScrollArea::setHorizontalSliderWidth(const int width)
{
    scroll_h->setWidth((double)width);
}

void TDScrollArea::setHorizontalSliderRadius(const int radius)
{
    scroll_h->setRadius((double)radius);
}

void TDScrollArea::setHorizontalSliderColor(const QColor &col_back, const QColor &col_front)
{
    scroll_h->setSliderColor(col_back,col_front);
}

void TDScrollArea::setHorizontalSliderOpacity(const int show_opacity, const int hide_opacity)
{
    scroll_h->setOpacityShow(show_opacity);
    scroll_h->setOpacityHide(hide_opacity);
}

void TDScrollArea::resizeEvent(QResizeEvent *)
{
    //子窗体不为空的时候才执行对应代码
    if(sub_widget != NULL){
        double w = this->width();
        double sw = sub_widget->width();
        double h = this->height();
        double sh = sub_widget->height();

        scroll_h->connectToWidget(sub_widget);
        scroll_v->connectToWidget(sub_widget);
        scroll_h->move(0,this->height()-scroll_h->getWidth());
        scroll_v->move(this->width()-scroll_v->getWidth(),0);
        //如果变化过程中，大小超过了子窗体的下或右边界，
        //而这时主窗体大小还没有超过子窗体大小，会出现超出子窗体但滑槽还显示 的情况。
        //先解决竖直方向，水平方向同理
        if(this->height() >= sub_widget->y()+sub_widget->height()
                && this->height() < sub_widget->height()){

            //出现了这种情况就移动子窗体的位置到下边界-子窗体高度。

            //但是因为在子控件的paintEvent()中使用了move，所以现在要移动sub_widget只能使用setSliderPosition();
            //sub_widget->move(sub_widget->x(),this->height()-sub_widget->height());
            scroll_v->setSliderPosition(-(h-sh)/sh*h);
        }
        if(this->width() >= sub_widget->x()+sub_widget->width()
                && this->width() < sub_widget->width()){

            //出现了这种情况就移动子窗体的位置到右边界-子窗体宽度。

            //但是因为在子控件的paintEvent()中使用了move，所以现在要移动sub_widget只能使用setSliderPosition();
            //sub_widget->move(this->width()-sub_widget->width(),sub_widget->y());
            scroll_h->setSliderPosition(-(w-sw)/sw * w);
        }
    }
}

//滚轮事件，这段算法把我折腾死了~
void TDScrollArea::wheelEvent(QWheelEvent *e)
{
    //大前提是子窗体被设置过！
    if(sub_widget != NULL)
    {
        double w = this->width();
        double sw = sub_widget->width();
        double h = this->height();
        double sh = sub_widget->height();
        double temp = wheel_step;
        //优先竖直方向的滚轮
        if(scroll_v->isVisible()){
            if(e->delta() > 0){//滚动角度大于0，向上滚动
                //子窗体向下移动一个步长
                //滑块的位置向上移动一小段距离（按比例计算）
                if( sub_widget->y() + temp <= 0)
                    scroll_v->setSliderPosition(scroll_v->getPosition()-temp/sh*h);
                else
                    scroll_v->setSliderPosition(0);
            }else{
                if(sub_widget->y()+sub_widget->height() - temp >= this->height())
                    scroll_v->setSliderPosition(scroll_v->getPosition()+temp/sh*h);
                else
                    scroll_v->setSliderPosition(-(h-sh)/sh*h+1);
            }
        }else if(scroll_h->isVisible()){
            if(e->delta() > 0 ){//滚动角度大于0，向左滚动
                if(sub_widget->x() + temp <= 0)
                    scroll_h->setSliderPosition(scroll_h->getPosition()-temp/sw*w);
                else
                    scroll_h->setSliderPosition(0);
            }else{
                if( sub_widget->x()+sub_widget->width() - temp >= this->width())
                    scroll_h->setSliderPosition(scroll_h->getPosition()+temp/sw*w);
                else
                    scroll_h->setSliderPosition(-(w-sw)/sw * w);
            }
        }else {
            e->ignore();
        }
        e->accept();

    }
}

