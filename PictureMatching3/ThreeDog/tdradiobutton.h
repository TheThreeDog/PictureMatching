/**************************************************************
 * File Name   : tdradiobutton.h
 * Author      : ThreeDog
 * Date        : Mon Jan 02 17:22:08 2017
 * Description : 自定义单选按钮，继承自自定义复选框类，扩展了单选的功能
 *         在被点击时发送radioClicked()信号，由父控件的槽函数实现单选
 *         并增加ID属性，用于记录按钮当前的ID。
 *
 **************************************************************/
#ifndef _TDRADIOBUTTON_H_ 
#define _TDRADIOBUTTON_H_ 
#include"tdcheckbox.h"

class TDRadioButton : public TDCheckbox
{
    Q_OBJECT

public:
    explicit TDRadioButton(QWidget *parent = 0);
    explicit TDRadioButton(const QString &text,QWidget *parent = 0);
    explicit TDRadioButton(const QString pic_che,const QString pic_non,QWidget *parent = 0,bool * boolean = NULL);
    void setColor(const QColor col_che,const QColor col_non);
    void setId(const int i);
    void setText(const QString & text);
    int getId() const;
    ~TDRadioButton();
protected:
    void mousePressEvent(QMouseEvent *);
signals:
    void radioClicked(int id);
private:
    int id;
};

#endif  //TDRADIOBUTTON
