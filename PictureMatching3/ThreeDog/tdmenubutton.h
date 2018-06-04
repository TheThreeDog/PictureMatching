/**************************************************************
 * File Name   : tdmenubutton.h
 * Author      : ThreeDog
 * Date        : Tue Jan 03 11:25:01 2017
 * Description : 自定义菜单按钮，相当于菜单，与按钮不同的是点击将其置
 *          于被选中的状态，而不是一松开图片就切换回来。
 *
 **************************************************************/
#ifndef _TDMENUBUTTON_H_ 
#define _TDMENUBUTTON_H_ 
#include "tdpushbutton.h"
#include <QMouseEvent>
#include <QFocusEvent>
class TDMenuButton :public TDPushButton
{
public:
    explicit TDMenuButton(QWidget* parent = 0);
    explicit TDMenuButton(const QString &text,QWidget *parent = 0);
    explicit TDMenuButton(const QString pic_nor,const QString pic_hov,const QString pic_sel,QWidget *parent = 0);
    void setColor(const QColor &col_nor,const QColor &col_hov,const QColor &col_sel);
    bool isSelected() const ;
    ~TDMenuButton();
protected:
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    //记录当前的选中状态
    bool is_selected;
};

#endif  //TDMENUBUTTON
