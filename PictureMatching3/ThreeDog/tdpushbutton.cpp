/***************************************************
* Program Assigment : 自定义按钮类
* File Name: tdpushbutton.cpp
* Author : ThreeDog
* Date : 2016/12/1
* Description: 自定义按钮类，实现按钮的三态和点击效果，没有传图片参数时
*       用默认的背景色和文字，传递参数时，用图片替换三态效果。
*
* **************************************************/

#include "tdpushbutton.h"
#include <QPalette>
#include <QBitmap>
//默认无参或传递父控件指针的构造函数
TDPushButton::TDPushButton(QWidget *parent)
    :TDAbstractButton(parent)
{
    this->setAutoFillBackground(true);
    this->setMinimumSize(100,30);
    QPalette palette;
    col_normal = Qt::gray;
    col_hover = Qt::lightGray;
    col_press = Qt::darkGray;
    palette.setColor(QPalette::Background,col_normal);
    this->setPalette(palette);
    this->setText("TDPushButton");
    this->setAlignment(Qt::AlignCenter);
    is_default = true;
}

void TDPushButton::setColor(const QColor &col_nor, const QColor &col_hov, const QColor &col_pre)
{
    //在为默认形式初始化时才可以执行图片替换
    if(true == is_default){
        this->setAutoFillBackground(true);
        this->setMinimumSize(100,30);
        QPalette palette;
        col_normal = col_nor;
        col_hover = col_hov;
        col_press = col_pre;
        palette.setColor(QPalette::Background,col_normal);
        this->setPalette(palette);
        this->setAlignment(Qt::AlignCenter);
    }

}

//传递文字和父控件参数，构造函数
TDPushButton::TDPushButton(const QString text, QWidget *parent)
    :TDAbstractButton(parent)
{
    this->setAutoFillBackground(true);
    this->setMinimumSize(100,30);
    QPalette palette;
    col_normal = Qt::gray;
    col_hover = Qt::lightGray;
    col_press = Qt::darkGray;
    palette.setColor(QPalette::Background,col_normal);
    this->setPalette(palette);
    this->setText(text);
    this->setAlignment(Qt::AlignCenter);
    is_default = true;
}

//传递三态图片实现初始化 bool变量为了区别函数重载，无实际意义
TDPushButton::TDPushButton(const QString pic_nor,
                           const QString pic_hov,
                           const QString pic_pre,
                           QWidget *parent):TDAbstractButton(parent)
{
    col_normal = Qt::gray;
    col_hover = Qt::lightGray;
    col_press = Qt::darkGray;
    pic_normal.load(pic_nor);
    pic_hover.load(pic_hov);
    pic_press.load(pic_pre);
    this->setMinimumSize(pic_normal.size());
    this->setPixmap(pic_normal);
    is_default = false;
}

//设置自动遮罩，以鼠标经过图片遮罩为按钮的遮罩区域。
void TDPushButton::setAutoMask()
{
    if(!pic_normal.isNull())
        this->setMask(pic_hover.mask());
}

bool TDPushButton::isDefault() const
{
    return this->is_default;
}
TDPushButton::~TDPushButton()
{

}

//鼠标经过进入到控件的事件
void TDPushButton::enterEvent(QEvent *)
{
    if(is_default){
        QPalette palette;
        palette.setColor(QPalette::Background, col_hover);
        this->setPalette(palette);
    }else {
        this->setPixmap(pic_hover);
    }

}

//鼠标离开控件时触发事件
void TDPushButton::leaveEvent(QEvent *)
{
    if(is_default){
        QPalette palette;
        palette.setColor(QPalette::Background,col_normal);
        this->setPalette(palette);
    }else {
        this->setPixmap(pic_normal);
    }
}

void TDPushButton::mousePressEvent(QMouseEvent *e)
{
    if(is_default && Qt::LeftButton == e->button()){
        QPalette palette;
        palette.setColor(QPalette::Background,col_press);
        this->setPalette(palette);
    }else if(!is_default&& Qt::LeftButton == e->button()){
        this->setPixmap(pic_press);
    }
    //2017/1/6  添加
    TDAbstractButton::mousePressEvent(e);

}

void TDPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(is_default && Qt::LeftButton == e->button()){
        QPalette palette;
        palette.setColor(QPalette::Background,col_hover);
        this->setPalette(palette);
    }else if(!is_default&& Qt::LeftButton == e->button()){
        this->setPixmap(pic_hover);
    }
    //执行父类的事件，完成按钮点击的效果。
    TDAbstractButton::mouseReleaseEvent(e);
}
