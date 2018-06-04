/**************************************************************
 * File Name   : tdslider.cpp
 * Author      : ThreeDog
 * Date        : Tue Jan 03 15:59:31 2017
 * Description : 自定义滑块窗体，参数传递底色，前景色和滑块颜色，采用绘图事件
 *          在鼠标松开时触发操作，接口和QSlider尽量保持一致。
 *
 **************************************************************/

#include "tdslider.h"
#include <QDebug>
TDSlider::TDSlider(TDWidget *parent,Qt::Orientation ot)
    :TDWidget(parent)
{
    col_background = Qt::darkGray;
    col_front = Qt::lightGray;
    col_button = Qt::white;
    orientation = ot;
    minimum = 0;
    maximum = 100;
    slider_position = 0;
    slider_radius = 4;
    slider_width = 3;
    value = 0;
    ispress = false;

}

TDSlider::TDSlider(const QColor col_bak
                   , const QColor col_fro
                   , const QColor col_btn
                   , TDWidget *parent
                   , Qt::Orientation ot)
    :TDWidget(parent)
{
    col_background = col_bak;
    col_front = col_fro;
    col_button = col_btn;
    orientation = ot;
    minimum = 0;
    maximum = 100;
    slider_position = 0;
    slider_radius = 4;
    slider_width = 3;
    value = 0;
    ispress = false;
}

//私有属性的外部接口

void TDSlider::setMinimum(const int min)
{
    minimum = min;
}

void TDSlider::setMaximum(const int max)
{
    maximum = max;
}

void TDSlider::setRange(const int min, const int max)
{
    minimum = min;
    maximum = max;
}

void TDSlider::setOrientation(Qt::Orientation ot)
{
    if(ot != orientation){
        orientation = ot;
        //更换布局重绘
        update();
    }
}

void TDSlider::setSliderPosition(const int position)
{
    //以像素为参数设置位置，注意如果是纵向，slider_position值得是从顶部到滑块的距离
    if(Qt::Horizontal == orientation)
        slider_position = position;
    else if(Qt::Vertical == orientation){
        slider_position = this->height()-position;
    }
    //重绘
    update();
}

void TDSlider::setValue(int v)
{
    if(v < minimum)
        v = minimum;
    else if(v > maximum)
        v = maximum;
    this->value = v;
    //按照value的值在本窗体所占的比例改变位置
    double val = value;
    double min = minimum;
    double max = maximum;
    //必须要用double，否则会整形除法会得出0
    if(Qt::Horizontal == orientation){
        double position = (val - min)/(max-min)*this->width();
        slider_position = position;
    }else if(Qt::Vertical == orientation){
        double position = (val - min)/(max-min)*this->height();
        slider_position = this->height()-position;
        //垂直方向上用总高度减去position，得到距顶部的高度，才是需要的效果
    }
    update();

}

void TDSlider::setSliderWidth(const int width)
{
    this->slider_width = width;
    update();
}

void TDSlider::setSliderRadius(const int radius)
{
    this->slider_radius = radius;
    update();
}

void TDSlider::setBackgroundColor(const QColor &color)
{
    this->col_background = color;
}

void TDSlider::setFrontColor(const QColor &color)
{
    this->col_front = color;
}

void TDSlider::setButtonColor(const QColor &color)
{
    this->col_button = color;
}

int TDSlider::getMinimum() const
{
    return minimum;
}

int TDSlider::getMaximum() const
{
    return maximum;
}

int TDSlider::getSliderPosition() const
{
    if(Qt::Horizontal == orientation)
        return slider_position;
    else if(Qt::Vertical == orientation)
        return this->height() - slider_position;
    //注意如果是纵向的话，获取到的slider_position应该是从底部开始的
    return -1;
}

int TDSlider::getValue() const
{
    return this->value;
}

int TDSlider::getSliderWidth() const
{
    return slider_width;
}

int TDSlider::getSliderRadius() const
{
    return slider_radius;
}

TDSlider::~TDSlider()
{

}

void TDSlider::paintEvent(QPaintEvent *)
{
    //QRect四个参数    //left top width height!!!!
    QPainter p(this);

    //如果方向是水平方向
    if(Qt::Horizontal ==  orientation){
        //先更正滑块位置，如果位置小于半径，则设置为半径，如果位置大于宽度，设置为宽度-半径
        if(slider_position < slider_radius/*/2+1*/)
            slider_position = slider_radius/*/2+2*/;
        if(slider_position > this->width()-slider_radius*5/4)
            slider_position = this->width()-slider_radius*5/4;

        QRect rect(0,slider_radius,this->width(),slider_width);
        //先绘制一个与窗体等长的背景色矩形
        p.fillRect(rect,col_background);
        QRect rect2(0,slider_radius,slider_position,slider_width);
        //然后绘制一个从0到当前滑块位置的前景色矩形
        p.fillRect(rect2,col_front);
        //圆心坐标
        QPoint center(slider_position,slider_radius+slider_width/2);
        p.setBrush(col_button);
        p.setPen(col_button);
        //在的滑块的位置画一个半径为4的小圆，作为滑块
        p.drawEllipse(center,slider_radius,slider_radius);
    }//如果方向是垂直方向
    else if(Qt::Vertical == orientation){
        //先更正滑块位置，如果位置大于高度，则设置为高度-5，如果位置小于3，设置为4
        if(slider_position<slider_radius/*/2+1*/)
            slider_position = slider_radius/*/2+2*/;
        if(slider_position>this->height()-slider_radius*5/4)
            slider_position = this->height()-slider_radius*5/4;
        //注意此时的sliderposition位置是从上到下的距离

        QRect rect(slider_radius,0,slider_width,this->height());
        //注意竖着的矩形是从上往下画的，所以跟刚才反过来
        //先用前景色画一个等高的矩形
        p.fillRect(rect,col_front);
        QRect rect2(slider_radius,0,slider_width,slider_position);
        //再用背景色画一个从最高点到指定位置的矩形
        p.fillRect(rect2,col_background);
        if(slider_position < slider_radius)
            slider_position = slider_radius;
        QPoint center(slider_radius+slider_width/2,slider_position);
        p.setBrush(col_button);
        p.setPen(col_button);
        //在滑块的位置画一个小圆作为滑块
        p.drawEllipse(center,slider_radius,slider_radius);
    }

}

void TDSlider::mousePressEvent(QMouseEvent *e)
{
    if(Qt::Horizontal == orientation){
        //如果要是落在了范围之外，要把位置校准回来
        if(e->x()>slider_radius && e->x()<this->width()-slider_radius*5/4)
            this->slider_position = e->pos().x();
        else if(e->x() <= slider_radius)
            this->slider_position = slider_radius;
        else if(e->x() >= this->width()-slider_radius*5/4)
            this->slider_position = this->width()-slider_radius*5/4;

        update();
        ispress = true;
    }else if(Qt::Vertical == orientation){
        if(e->y() > slider_radius && e->y()<this->height()-slider_radius*5/4){
            this->slider_position = e->pos().y();
        }else if(e->y() < slider_radius){
            this->slider_position = slider_radius;
        }else if(e->y() > this->height()-slider_radius*5/4){
            this->slider_position = this->height()-slider_radius*5/4;
        }
        update();
        ispress = true;
    }
}

void TDSlider::mouseReleaseEvent(QMouseEvent *e)
{
    if(Qt::Horizontal == orientation){
        if(e->x() > slider_radius && e->y()<this->width()-slider_radius*5/4)
            slider_position = e->pos().x();
        //如果超出边界y就不再等于e.y()
        double x = e->pos().x();
        if(e->x() < 0)
            x = 0;
        if(e->x() > this->width())
            x = this->width();
        double w = this->width();
        //发送数值改变信号,通过相对位置计算得到数值大小
        double value = x/w*(maximum-minimum)+minimum;
        emit valueChanged(value);
        emit positionChanged(x);
    }else if(Qt::Vertical == orientation){
        if(e->y()>slider_radius && e->y()<this->height()-slider_radius*5/4)
            slider_position = e->pos().y();
        //如果超出边界y就不再等于e.y()
        double y = e->y();
        if(e->y()< 0)
            y = 0;
        else if(e->y()>this->height())
            y = this->height();
        double w = this->height();
        //发送数值改变信号,通过相对位置计算得到数值大小
        //而垂直方向的是从顶部到滑槽点的距离，所以value要减一下
        double value = maximum - y/w*(maximum-minimum);
        //注意锁定范围
        emit valueChanged(value);
        emit positionChanged(this->height()-y);//同样这里要用高度减一下
    }
    update();
    ispress = false;

}

void TDSlider::mouseMoveEvent(QMouseEvent *e)
{
    if(Qt::Horizontal == orientation){
        if(e->x()>slider_radius && e->x()<this->width()-slider_radius*5/4){
            this->slider_position = e->pos().x();
        }else if(e->x() <= slider_radius){
            this->slider_position = slider_radius;
        }else if(e->x() >= this->width()-slider_radius*5/4){
            this->slider_position = this->width()-slider_radius*5/4;
        }
        //以上校准滑块位置
        //以下校准发送的数据
        double x = e->pos().x();
        if(x < 0)
            x = 0;
        if(x > this->width())
            x = this->width();
        double w = this->width();
        double value = x/w*(maximum-minimum)+minimum;
        emit valueChanging(value);
        emit positionChanging(x);
    }else if(Qt::Vertical == orientation){
        if(e->y()> slider_radius &&e->y()<this->height()-slider_radius*5/4){
            this->slider_position = e->pos().y();
        }else if(e->y() < slider_radius){
            this->slider_position = slider_radius;
        }else if(e->y() > this->height()-slider_radius*5/4){
            this->slider_position = this->height()-slider_radius*5/4;
        }
        //以上校准滑块位置
        //以下校准发送的数据
        double y = e->y();
        if(e->y()< 0)
            y = 0;
        else if(e->y()>this->height())
            y = this->height();

        double w = this->height();

        //发送数值改变信号,通过相对位置计算得到数值大小
        //而垂直方向的是从顶部到滑槽点的距离，所以value要减一下
        double value = maximum - y/w*(maximum-minimum);
        emit valueChanging(value);
        emit positionChanging(this->height() - y);//同样这里要用高度减一下
    }
    update();
}
