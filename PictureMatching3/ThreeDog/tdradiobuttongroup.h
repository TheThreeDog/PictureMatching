/***************************************************
* Program Assigment : 自定义单选按钮组类
* File Name: tdradiobuttongroup.h
* Author : ThreeDog
* Date : 2016/12/29
* Description: 自定义单选按钮组类，在需要单选按钮的地方创建一个单选按钮组
*           同一个组内，只能有一个按钮被选择。单个的按钮用自定义复选框实现
*
* **************************************************/
#ifndef TDRADIOBUTTONGROUP_H
#define TDRADIOBUTTONGROUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "tdradiobutton.h"
#include "tdwidget.h"

class TDRadioButtonGroup : public TDWidget
{
    Q_OBJECT
public:
    explicit TDRadioButtonGroup(TDWidget *parent = 0);
    explicit TDRadioButtonGroup(const Qt::Orientation,TDWidget* parent = 0);
    explicit TDRadioButtonGroup(const int num,const Qt::Orientation,TDWidget* parent = 0 );
    //以图片为参数初始化单选按钮组
    explicit TDRadioButtonGroup(const QString pic_che
                                ,const QString pic_non
                                ,TDWidget *parent = 0
                                ,Qt::Orientation ot = Qt::Horizontal);
    //添加指定数量的按钮
    void addButton(const int num);
    //添加一个按钮
    void addButton();
    //讲一个现有的按钮添加到组中 并指定ID
    void addButton(TDRadioButton *btn,int id);
    void removeButton(const int index);
    void removeAll();
    //返回被选中的按钮的
    TDRadioButton* getClickedButton();
    //获取按钮在容器中的位置
    int getClickedButtonLocation() const;
    //获取选中的按钮的id；
    int getClickedButtonId() const ;
    //移除所有按钮的文字
    void removeText();
    //初始化函数，传递方向参数，决定是水平还是垂直布局
    void initDefault(Qt::Orientation ot);
    //返回保存按钮的容器的指针
    QVector<TDRadioButton *> * radioButtons();

    ~TDRadioButtonGroup();
//signals:2017/3/7添加，Threedog
signals:
    void radioButtonClicked(int id);
    void radioButtonChanged(int id);
public slots:
    void buttonClicked(int id );
private :
    //用于显示选中和未选中状态的图片
    QString pic_checked;
    QString pic_non_checked;

    QVector<TDRadioButton *> radio_buttons;//用一个按钮容器存放
    TDRadioButton * radio_btn;//用于指向当前正在操作的按钮
    QBoxLayout *main_layout;//页面的主要布局，根据用户参数决定是水平还是垂直

};

#endif // TDRADIOBUTTONGROUP_H
