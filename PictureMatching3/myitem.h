#ifndef MYITEM_H
#define MYITEM_H
#include "ThreeDog/tdmenubutton.h"

class MyItem : public TDMenuButton
{
    Q_OBJECT
public:
    explicit MyItem(const QString pic_n,const QString pic_h,const QString pic_s,QWidget *parent = 0);
    //设置此条目的标号
    void setIndex(const int i);
    //获取此条目的标号
    int getIndex();
signals:
    void clicked(MyItem * item, int index);

private :
    //捕获点击信号进行转发
    void itemClicked();
    int index ;//标识不同图片的变量
};

#endif // MYITEM_H





