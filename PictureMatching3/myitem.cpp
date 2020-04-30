#include "myitem.h"

MyItem::MyItem(const QString pic_n, const QString pic_h, const QString pic_s, QWidget *parent)
    :TDMenuButton(pic_n,pic_h,pic_s,parent)
{
    //鼠标一点击，就执行回调函数
    this->setCallback(this,my_selector(MyItem::itemClicked));
}

void MyItem::setIndex(const int i)
{
    this->index = i;
}

int MyItem::getIndex()
{
    return this->index;
}

void MyItem::itemClicked()
{
    //在此发送信号，包含本对象的数据
    emit clicked(this,this->index);
}






