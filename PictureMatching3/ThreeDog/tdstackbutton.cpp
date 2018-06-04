/**************************************************************
 * File Name   : tdstackbutton.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 05 10:19:40 2017
 * Description : 自定义堆叠按钮，利用一个内置的StackWidget实现，效果是点击
 *          一个按钮触发效果后切换为另一个按钮。例如音乐播放器中播放模式的按钮
 *
 **************************************************************/

#include "tdstackbutton.h"
#include <QPushButton>
TDStackButton::TDStackButton(TDWidget *parent)
    :TDWidget(parent)
{
    stack_layout = new QStackedLayout;
    this->setLayout(stack_layout);

}

//添加按钮
void TDStackButton::addButton(TDAbstractButton *button)
{
    stack_layout->addWidget(button);
    stack_layout->setCurrentWidget(button);
    connect(button,SIGNAL(clicked()),this,SLOT(toNextButton()));
}

//移除按钮
void TDStackButton::removeButton(QWidget *button)
{
    emit buttonRemoved(stack_layout->indexOf(button));
    stack_layout->removeWidget(button);
    //发送移除信号并移除此按钮
}

//按下标移除按钮
void TDStackButton::removeButton(const int index)
{
    if(index >= stack_layout->count())
        return ;
    emit buttonRemoved(index);
    stack_layout->removeWidget((QWidget * )stack_layout->itemAt(index));
}

//移除所有按钮
void TDStackButton::removeAllButton()
{
    for(int i = 0; i< stack_layout->count();i++){
        removeButton(i);
    }
}

//获取当前下标
int TDStackButton::getCurrentIndex() const
{
    return stack_layout->currentIndex();
}

//获取当前的按钮
TDAbstractButton *TDStackButton::getCurrentButton() const
{
    return (TDAbstractButton*)stack_layout->currentWidget();
}

TDStackButton::~TDStackButton()
{

}

//设置按下标当前按钮
void TDStackButton::setCurrentIndex(const int index)
{
    if(index >= stack_layout->count())
        return ;
    if(index != stack_layout->currentIndex()){
        emit buttonChanged(index);
        stack_layout->setCurrentIndex(index);
    }
}

//设置当前按钮
void TDStackButton::setCurrentButton(TDAbstractButton *button)
{
    if(button != stack_layout->currentWidget()){
        emit buttonChanged(stack_layout->indexOf(button));
        stack_layout->setCurrentWidget(button);
    }
}

//切换到下一个按钮
void TDStackButton::toNextButton()
{
    if(stack_layout->currentIndex()+1 == stack_layout->count())
        stack_layout->setCurrentIndex(0);
    else
        stack_layout->setCurrentIndex(stack_layout->currentIndex()+1);
}
