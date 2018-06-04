/***************************************************
* Program Assigment : 自定义按钮类
* File Name: tdpushbutton.h
* Author : ThreeDog
* Date : 2016/12/1
* Description: 自定义按钮类，实现按钮的三态和点击效果，没有传图片参数时
*       用默认的背景色和文字，传递参数时，用图片替换三态效果。
*
* **************************************************/

#ifndef TDPUSHBUTTON_H
#define TDPUSHBUTTON_H
#include "tdabstractbutton.h"
#include <QMouseEvent>
#include <QEvent>
#include <QColor>
class TDPushButton : public TDAbstractButton
{
public:
    explicit TDPushButton(QWidget *parent = 0);
    TDPushButton(const QString text,QWidget *parent = 0);
    TDPushButton(const QString pic_nor,const QString pic_hov,const QString pic_pre,QWidget *parent = 0);
    //移除QColor初始化接口，改为使用接口设置
    void setColor(const QColor & col_nor,const QColor & col_hov,const QColor & col_pre);
    virtual void setAutoMask();
    //判断当前控件是否为默认形式初始化（如果为默认，则可以使用setText()等函数，否则调用该函数无效并输出报错信息）
    bool isDefault() const;
    ~TDPushButton();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    //子类要用到这些变量，所以声明为保护成员
    bool is_default;
    QPixmap pic_normal;
    QPixmap pic_hover;
    QPixmap pic_press;
    QColor col_normal;
    QColor col_hover;
    QColor col_press;

private:

};

#endif // TDPUSHBUTTON_H
