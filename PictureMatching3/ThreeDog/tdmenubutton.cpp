/**************************************************************
 * File Name   : tdmenubutton.cpp
 * Author      : ThreeDog
 * Date        : Tue Jan 03 11:25:01 2017
 * Description : 自定义菜单按钮，相当于菜单，与按钮不同的是点击将其置
 *          于被选中的状态，而不是一松开图片就切换回来。
 *
 **************************************************************/

#include "tdmenubutton.h"

TDMenuButton::TDMenuButton(QWidget *parent)
    :TDPushButton("TDMenuButton",parent)
{
    //设置此类的焦点触发方式为点击触发
    this->setFocusPolicy(Qt::ClickFocus);
    is_selected = false;
}

TDMenuButton::TDMenuButton(const QString &text, QWidget *parent)
    :TDPushButton(text,parent)
{
    //设置此类的焦点触发方式为点击触发
    this->setFocusPolicy(Qt::ClickFocus);
    is_selected = false;
}

TDMenuButton::TDMenuButton(const QString pic_nor, const QString pic_hov, const QString pic_sel, QWidget *parent)
    :TDPushButton(pic_nor,pic_hov,pic_sel,parent)
{
    //设置此类的焦点触发方式为点击触发
    this->setFocusPolicy(Qt::ClickFocus);
    is_selected = false;
}

void TDMenuButton::setColor(const QColor &col_nor, const QColor &col_hov, const QColor &col_sel)
{
    TDPushButton::setColor(col_nor,col_hov,col_sel);
}

bool TDMenuButton::isSelected() const
{
    return this->is_selected;
}

TDMenuButton::~TDMenuButton()
{

}

void TDMenuButton::focusInEvent(QFocusEvent *)
{
    //获取到焦点，将图片或者颜色替换为选中时的状态
    if(is_default){
        QPalette palette;
        palette.setColor(QPalette::Background,col_press);
        this->setPalette(palette);
    }else{
        this->setPixmap(pic_press);
    }
}

void TDMenuButton::focusOutEvent(QFocusEvent *)
{
    //失去焦点，将图片或者颜色替换为正常的状态
    if(is_default){
        QPalette palette;
        palette.setColor(QPalette::Background,col_normal);
        this->setPalette(palette);
    }else{
        this->setPixmap(pic_normal);
    }
    is_selected = false;
}

void TDMenuButton::leaveEvent(QEvent *e)
{
    //重写鼠标离开事件，在被选中的状态下不再执行操作
    if(is_selected)
        e->ignore();
    else
        TDPushButton::leaveEvent(e);
}

void TDMenuButton::enterEvent(QEvent *e)
{
    //重写鼠标进入事件，在被选中的状态下不再执行操作
    if(is_selected)
        e->ignore();
    else
        TDPushButton::enterEvent(e);
}

void TDMenuButton::mousePressEvent(QMouseEvent *e)
{
    //保证焦点不变的情况下只触发一次，
    if(!is_selected){
        //无效化鼠标按下事件，改为在焦点事件中执行图片替换
        //执行“爷爷类”的鼠标离开事件，完成信号的发送和回调函数的调用
        TDAbstractButton::mouseReleaseEvent(e);
            is_selected = true;
    }
    //2017/1/6  添加
    TDAbstractButton::mousePressEvent(e);

}

void TDMenuButton::mouseReleaseEvent(QMouseEvent *)
{
    //用空方法体无效化父类的鼠标松开事件
}
