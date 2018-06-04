/***************************************************
* Program Assigment : 自定义窗体类
* File Name: tdwidget.cpp
* Author : ThreeDog
* Date : 2016/11/30
* Description: 自定义窗体类，实现用图片代替不规则窗体，可拖动。
*
* **************************************************/
#include "tdwidget.h"
#include <QPainter>
#include <QBitmap>
#include <QDebug>
TDWidget::TDWidget(QWidget *parent) : QWidget(parent)
{
    //一定初始化为false，否则默认会赋值true，mouseMoveEvent会在点击别的控件时触发！
    this->is_press = false;
    move_enable = false;
}

TDWidget::TDWidget(QString img_path,QWidget *parent,bool show_window) : QWidget(parent)
{
    //如果不显示窗体，默认情况
    if(!show_window){
        this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
        this->setAttribute(Qt::WA_TranslucentBackground);
        bg_pic.load(img_path);
        this->resize(bg_pic.size());
        //this->setMask(bg_pic.mask());
        //一定听初始化为false，否则默认会赋值true，mouseMoveEvent会在点击别的控件时触发！
        this->is_press = false;
        move_enable = true;
    }else{
        //2017,1,9日修改
        //显示窗体，传入参数作为背景图片
        this->setAutoFillBackground(true);    //Widget增加背景图片时，这句一定要。
        QPixmap pixmap(img_path);
        QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(pixmap));
        this->setPalette(palette);
        this->is_press = false;
        move_enable = false;
    }
    this->show();
}

void TDWidget::setMoveEnable(const bool can_move)
{
    this->move_enable = can_move;
}

bool TDWidget::moveEnable() const
{
    return this->move_enable;
}

void TDWidget::setAutoMask()
{
    if(!bg_pic.isNull())
        this->setMask(bg_pic.mask());
}

void TDWidget::paintEvent(QPaintEvent *)
{
    if(!bg_pic.isNull()){
        QPainter p(this);
        p.drawPixmap(0,0,bg_pic);
    }
}

TDWidget::~TDWidget()
{

}

void TDWidget::mousePressEvent(QMouseEvent *e)
{
    if(Qt::LeftButton == e->button()&&move_enable){
        //旧的鼠标相对于本窗体的位置
        old_pos = e->pos();
        is_press = true;
    }
}

void TDWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(is_press && move_enable){
        //窗体之前的位置，加上鼠标相对于本窗体的位置，再减去鼠标按下之前相对于本窗体的位置。
        this->move(this->pos() + e->pos() - old_pos);
    }
}

void TDWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(move_enable)
        is_press = false;
}

