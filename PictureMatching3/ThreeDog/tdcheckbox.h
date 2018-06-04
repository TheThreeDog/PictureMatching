/***************************************************
* Program Assigment : 自定义复选框按钮类
* File Name: tdcheckbox.h
* Author : ThreeDog
* Date : 2016/12/24
* Description: 自定义复选框类，通过点击事件传递信号，接收信号后通过
*           原来的属性判断，改变属性设置。
*
* **************************************************/

#ifndef TDCHECKBOX_H
#define TDCHECKBOX_H
#include "QLabel"
#include "tdabstractbutton.h"
#include <QMouseEvent>
#include <QPixmap>

//继承自抽象按钮类，复用信号和槽和鼠标离开事件代码
class TDCheckbox : public TDAbstractButton
{
    Q_OBJECT

public:
    explicit TDCheckbox(QWidget *parent = 0,bool* boolean = NULL);
    explicit TDCheckbox(const QString &text,QWidget *parent = 0,bool* boolean= NULL);
    explicit TDCheckbox(const QString pic_che,const QString pic_non,QWidget *parent = 0,bool* boolean = NULL);
    //按图片形式设置自动遮罩
    void setAutoMask();
    //关联这个复选框所控制的布尔变量 传递一个bool变量的指针
    void connectToBool(bool* boolean);
    //重写setText，改变右控件文字
    void setText(const QString &);
    //返回是否被选中的状态
    bool isChecked() const;
    //改变选中状态的外部接口
    void setChecked(bool check);
    //使用设置接口的方式改变颜色，而不是初始化函数
    void setColor(const QColor &col_che,const QColor &col_non);
    QLabel * getLeftLabel();
    QLabel * getRightLabel();

    ~TDCheckbox();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private :
    //按默认方式初始化控件
    void initDefault(bool* boolean);

    bool is_default;
    bool is_selected;
    bool *con_bool;//关联的bool变量的指针
    QLabel *left;
    QLabel *right;
    QColor col_checked;
    QColor col_non_checked;
    QPixmap pic_checked;
    QPixmap pic_non_checked;
};

#endif // TDCHECKBOX_H
