/***************************************************
* Program Assigment : 自定义抽象按钮类
* File Name: tdabstructbutton.cpp
* Author : ThreeDog
* Date : 2016/12/2
* Description: 自定义抽象按钮类，所有的自定义按钮都继承自这个类，通过
*       函数指针和调用者的指针实现回调函数。也可以用信号和槽。
*
****************************************************/
/****************************************************
 * 修改日志
 * 时间：2017/1/6
 * 修改内容:增加鼠标按住拖动移动的功能
 * 改动者:ThreeDog
 * 注意：在实现了mousePressEvent的子类中，此类的此事件不再调用，则
 *      无法实现相应功能，方法是在子类此方法中调用父类的此事件函数。
 *      包括其他事件也有可能出现此种情况，应注意。
 *
 * *************************************************/


#ifndef TDABSTRACTBUTTON_H
#define TDABSTRACTBUTTON_H
#include <QLabel>
#include <QMouseEvent>

//回调函数的函数指针。
typedef void (QObject::*FUNC_PTR )();
//函数指针的强制类型转换的宏，函数指针不能自动转换，需要自己转换一下。
#define my_selector(_SELECTOR) (FUNC_PTR)(&_SELECTOR)

class TDAbstractButton : public QLabel
{
    Q_OBJECT

public:
    explicit TDAbstractButton(QWidget *parent);
    //设置回调，参数是函数的调用者，和调用的函数指针
    void setCallback(QObject * obj,FUNC_PTR func);
    //设置自动遮罩，在子类中自己实现，本类中只有空方法体
    virtual void setAutoMask();
    void setMoveEnable(const bool can_move);
    bool moveEnable() const;
    ~TDAbstractButton();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    //在鼠标抬起事件中实现调用
    void mouseReleaseEvent(QMouseEvent *e);
signals:
    void clicked();
private:
    FUNC_PTR func_ptr;
    QObject* caller;

    QPoint old_pos;
    bool move_enable;
    bool is_press;

};

#endif // TDABSTRACTBUTTON_H
