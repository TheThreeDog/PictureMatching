/***************************************************
* Program Assigment : 自定义抽象按钮类
* File Name: tdabstructbutton.cpp
* Author : ThreeDog
* Date : 2016/12/2
* Description: 自定义抽象按钮类，所有的自定义按钮都继承自这个类，通过
*       函数指针和调用者的指针实现回调函数。也可以用信号和槽。
*
* **************************************************/

#include "tdabstractbutton.h"
#include <QDebug>
TDAbstractButton::TDAbstractButton(QWidget *parent) :QLabel (parent)
{
    //在构造函数中初始化为NULL，如果没有传参，这两个指针无效，不发生调用
    caller = NULL;
    func_ptr = NULL;
    this->setWordWrap(true);//设置自动换行
    move_enable = false;
    is_press = false;
    this->show();
}

void TDAbstractButton::setCallback(QObject *obj, FUNC_PTR func)
{
    //设置回调，参数是函数的调用者，和调用的函数指针
    caller = obj;
    func_ptr = func;
}

TDAbstractButton::~TDAbstractButton()
{

}

void TDAbstractButton::mousePressEvent(QMouseEvent *e)
{
    //在可用状态下才触发
    if(this->isEnabled()){
        //旧的鼠标相对于本窗体的位置
        if(move_enable){
            old_pos = e->pos();
            is_press = true;
        }
    }
}

void TDAbstractButton::mouseMoveEvent(QMouseEvent *e)
{
    if(is_press && move_enable && this->isEnabled()){
        //窗体之前的位置，加上鼠标相对于本窗体的位置，再减去鼠标按下之前相对于本窗体的位置。
        this->move(this->pos() + e->pos() - old_pos);
    }
}

void TDAbstractButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->isEnabled()){
        //在鼠标抬起事件中实现调用（caller 和 func_ptr不能为空）
        if(Qt::LeftButton == e->button() ){
            if(caller && func_ptr)
                (caller->*func_ptr)();
            emit clicked();
            if(move_enable){
                is_press = false;
            }
        }
    }
}

void TDAbstractButton::setAutoMask()
{
}

void TDAbstractButton::setMoveEnable(const bool can_move)
{
    move_enable = can_move;
}

bool TDAbstractButton::moveEnable() const
{
    return move_enable;
}

