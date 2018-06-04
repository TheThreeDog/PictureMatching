/***************************************************
* Program Assigment : 自定义单选按钮组类
* File Name: tdradiobuttongroup.cpp
* Author : ThreeDog
* Date : 2016/12/29
* Description: 自定义单选按钮组类，在需要单选按钮的地方创建一个单选按钮组
*           同一个组内，只能有一个按钮被选择。单个的按钮用自定义复选框实现
*
* **************************************************/
#include "tdradiobuttongroup.h"
#include <QBitmap>
#include <QDebug>
//默认情况下的初始化，添加两个复选框按钮，并且保证只能有一个被选中。
TDRadioButtonGroup::TDRadioButtonGroup(TDWidget *parent) : TDWidget(parent)
{

    initDefault(Qt::Horizontal);
}
//指定了方向的初始化
TDRadioButtonGroup::TDRadioButtonGroup(const Qt::Orientation ot, TDWidget *parent)
    :TDWidget(parent)
{
    initDefault(ot);
}
//指定方向，并在开始就指定了按钮的个数。
TDRadioButtonGroup::TDRadioButtonGroup(const int num, const Qt::Orientation ot, TDWidget *parent)
    :TDWidget(parent)
{
    initDefault(ot);
    if(num > 2)
        addButton(num - 2);
}

TDRadioButtonGroup::TDRadioButtonGroup(const QString pic_che,
                                       const QString pic_non,
                                       TDWidget *parent,
                                       Qt::Orientation ot)
    :TDWidget(parent)
{
    pic_checked = pic_che;
    pic_non_checked = pic_non;
    initDefault(ot);
}

//添加num个按钮
void TDRadioButtonGroup::addButton(const int num)
{
    for(int i = 0;i < num; i++ )
        addButton();

}

void TDRadioButtonGroup::addButton(TDRadioButton *btn,int id)
{
    radio_buttons.append(btn);
    btn->setId(id);
    //设置当前按钮被选中，也就是默认情况永远是最后一个按钮被选中
    this->buttonClicked(id);
    //连接单选按钮被点击的信号和槽
    connect(btn,SIGNAL(radioClicked(int)),this,SLOT(buttonClicked(int)));
}

//单独添加一个按钮
void TDRadioButtonGroup::addButton()
{
    //如果图片没有被初始化赋值，就按默认情况初始化
    if(pic_checked.isEmpty() && pic_non_checked.isEmpty())
        radio_btn = new TDRadioButton("TDRadioButton",this);
    else
        radio_btn = new TDRadioButton(pic_checked,pic_non_checked,this);
    //分别在容器和布局中添加
    radio_buttons.append(radio_btn);
    //设置添加的按钮的ID，当前容器的大小，即添加的按钮的ID。 -1即从0开始计算
    radio_btn->setId(radio_buttons.count()-1);
    main_layout->addWidget(radio_btn);
    radio_btn->show();
    //设置当前按钮被选中，也就是默认情况永远是最后一个按钮被选中
    this->buttonClicked(radio_buttons.count()-1);
    //连接单选按钮被点击的信号和槽
    connect(radio_btn,SIGNAL(radioClicked(int)),this,SLOT(buttonClicked(int)));
}

//删除一个按钮
void TDRadioButtonGroup::removeButton(const int index)
{
    //如果下标大于等于按钮的数量，直接返回，内存溢出
    if(index >= radio_buttons.count())
        return ;
    radio_btn = radio_buttons.at(index);
    //删除之前，在其之后的所有按钮的ID都要-1（相当于前移一位）
    for(int i = index+1 ; i < radio_buttons.count();i++){
        radio_buttons.at(i)->setId(radio_buttons.at(i)->getId()-1);
    }//以此来保证按钮ID的连续一致
    main_layout->removeWidget(radio_btn);
    radio_buttons.remove(index);
    //在布局和容器删除掉之后，销毁掉这个按钮的内存
    delete radio_btn;
    radio_btn = NULL;
}
//删除掉全部的按钮
void TDRadioButtonGroup::removeAll()
{
    for(int i = 0; i < radio_buttons.count(); i++){
        removeButton(i);
    }

}
//返回当前选中的按钮
TDRadioButton* TDRadioButtonGroup::getClickedButton()
{
    //遍历所有按钮，如果遇到被选中的就直接返回。
    for(int i = 0;i < radio_buttons.count();i++){
        if(radio_buttons.at(i)->isChecked())
            return radio_buttons.at(i);
    }
    return NULL;

}

int TDRadioButtonGroup::getClickedButtonLocation() const
{
    //遍历所有按钮，如果遇到被选中的就直接返回。
    for(int i = 0;i < radio_buttons.count();i++){
        if(radio_buttons.at(i)->isChecked())
            return i;
    }
    return 0;
}

int TDRadioButtonGroup::getClickedButtonId() const
{
    //遍历所有按钮，如果遇到被选中的就直接返回。
    for(int i = 0;i < radio_buttons.count();i++){
        if(radio_buttons.at(i)->isChecked())
            return radio_buttons.at(i)->getId();
    }
    return 0;
}
//移除所有按钮的文字
void TDRadioButtonGroup::removeText()
{
    //////////////////////////////////////
    //现存BUG，默认情况下移除文字，重绘遮罩无效。
    for(int i = 0;i < radio_buttons.count();i++){
        radio_buttons.at(i)->setText("");
    }
}
//按默认方式初始化
void TDRadioButtonGroup::initDefault(Qt::Orientation ot)
{
    this->adjustSize();
    this->setMoveEnable(false);
    //判断方向，决定水平还是垂直布局
    if(Qt::Vertical == ot)
        main_layout = new QVBoxLayout;
    else if(Qt::Horizontal == ot)
        main_layout = new QHBoxLayout;
    //设定完布局方向，添加两个按钮（默认情况）
    //addButton(2);
    this->setLayout(main_layout);

}

QVector<TDRadioButton *> *TDRadioButtonGroup::radioButtons()
{
    //返回的是指针，所以这里要对容器取地址。
    return &radio_buttons;

}

TDRadioButtonGroup::~TDRadioButtonGroup()
{

}
//组中的单选按钮点击的槽函数
void TDRadioButtonGroup::buttonClicked(int id)
{
    if(id != this->getClickedButtonId())
        emit radioButtonChanged(id);
    //将被点击的按钮设置为真，其余的都设置成假，则达到了单选的效果。
    for(int i = 0;i < radio_buttons.count();i++){
        radio_buttons.at(i)->setChecked(false);
        if(id == radio_buttons.at(i)->getId())
            radio_buttons.at(i)->setChecked(true);
    }
    emit radioButtonClicked(id);
    //不是第ID个按钮，是ID等于id的按钮
    //radio_buttons.at(id)->setChecked(true);

}

