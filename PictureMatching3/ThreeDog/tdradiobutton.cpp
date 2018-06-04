/**************************************************************
 * File Name   : tdradiobutton.cpp
 * Author      : ThreeDog
 * Date        : Mon Jan 02 17:22:08 2017
 * Description : 自定义单选按钮，继承自自定义复选框类，扩展了单选的功能
 *         在被点击时发送radioClicked()信号，由父控件的槽函数实现单选
 *         并增加ID属性，用于记录按钮当前的ID。
 *
 **************************************************************/

#include "tdradiobutton.h"

TDRadioButton::TDRadioButton(QWidget *parent)
    :TDCheckbox("TDRadioButton",parent)
{

}

TDRadioButton::TDRadioButton(const QString &text, QWidget *parent)
    :TDCheckbox(text,parent)
{

}

TDRadioButton::TDRadioButton(const QString pic_che, const QString pic_non, QWidget *parent,bool * boolean)
    :TDCheckbox(pic_che,pic_non,parent,boolean)
{
    this->setText("TDRadioButton");

}

void TDRadioButton::setColor(const QColor col_che, const QColor col_non)
{
    TDCheckbox::setColor(col_che,col_non);
}

void TDRadioButton::setId(const int i)
{
    id = i;
}


void TDRadioButton::setText(const QString &text)
{
    TDCheckbox::setText(text);
}

int TDRadioButton::getId() const
{
    return id;

}

TDRadioButton::~TDRadioButton()
{

}

void TDRadioButton::mousePressEvent(QMouseEvent *e)
{
    //执行父类的按钮按下事件，并且发送单选按钮点击的信号（包含按钮ID参数）
    TDCheckbox::mousePressEvent(e);
    emit radioClicked(id);
}
