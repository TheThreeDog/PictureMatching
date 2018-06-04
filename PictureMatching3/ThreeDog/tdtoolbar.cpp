/***************************************************
* Program Assigment : 自定义工具栏按钮类
* File Name: tdtoolbar.cpp
* Author : ThreeDog
* Date : 2016/12/28
* Description: 自定义工具栏类，继承自自定义复选框，几乎没有改动，只是
*           去除了复选框的右控件，可以通过信号和槽或者回调函数实现功能。
*
* **************************************************/
#include "tdtoolbar.h"
#include <QMainWindow>
TDToolbar::TDToolbar(QWidget *parent)
    :TDCheckbox(parent,NULL)
{
    this->setText("");
}

TDToolbar::TDToolbar(const QString pic_che,const QString pic_non, QWidget *parent)
    :TDCheckbox(pic_che,pic_non,parent,NULL)
{
    this->setText("");
}

void TDToolbar::resize(int w, int h)
{
    this->getLeftLabel()->resize(w,h);
}

void TDToolbar::setColor(const QColor &col_che, const QColor &col_non)
{
    TDCheckbox::setColor(col_che,col_non);
}

TDToolbar::~TDToolbar()
{

}

