/***************************************************
* Program Assigment : 自定义复选框按钮类
* File Name: tdcheckbox.h
* Author : ThreeDog
* Date : 2016/12/24
* Description: 自定义复选框类，通过点击事件传递信号，接收信号后通过
*           原来的属性判断，改变属性设置。
*
* **************************************************/
#include "tdcheckbox.h"
#include <QDebug>
#include <QBitmap>
#include <QPixmap>
//按默认方式初始化控件
TDCheckbox::TDCheckbox( QWidget *parent,bool *boolean)
    :TDAbstractButton(parent)
{
    initDefault(boolean);
}


TDCheckbox::TDCheckbox(const QString &text,QWidget *parent, bool *boolean)
    :TDAbstractButton(parent)
{
    initDefault(boolean);
    right->setText(text);
}

TDCheckbox::TDCheckbox(const QString pic_che,const QString pic_non, QWidget *parent, bool *boolean)
    :TDAbstractButton(parent)
{
    //加载图片设置
    pic_checked.load(pic_che);
    pic_non_checked.load(pic_non);
    //设置为非默认状态
    is_default = false;
    is_selected = false;

    //在此关联复选框对应的变量,若指针为空，就会用NULL初始化
    this->con_bool = boolean;
    if(NULL != con_bool)
        is_selected = *con_bool;

    //初始化左右控件，设置控件的大小，统统以图片为标准
    left = new QLabel(this);
    left->setPixmap(pic_checked);
    left->setMinimumSize(pic_checked.size());
    left->resize(pic_checked.size());
    right = new QLabel(this);
    right->setMinimumSize(80,left->height());
    right->resize(80,left->height());
    this->setMinimumSize(left->width()+right->width(),left->height());
    this->resize(left->width()+right->width(),left->height());

    if(!is_selected)//按选中状态来选择显示的图片或颜色
        left->setPixmap(pic_non_checked);
    else
        left->setPixmap(pic_checked);

    //设置右控件位置属性和文字
    right->setAlignment(Qt::AlignCenter);
    right->setText("TDCheckBox");//唯一和普通构造函数有区别的地方
    right->move(left->width(),0);

}

void TDCheckbox::initDefault(bool * boolean)
{
    //如果颜色是无效的，用默认颜色初始化颜色
    if(!col_checked.isValid()&&!col_non_checked.isValid()){
        //初始化为默认颜色显示选中和被选中的状态
        col_checked = Qt::red;
        col_non_checked = Qt::darkRed;
    }
    //初始化状态为未选中，初始化方式为默认
    is_default = true;
    is_selected = false;
    //在此关联复选框对应的变量,若指针为空，就会用NULL初始化
    this->con_bool = boolean;
    if(NULL != con_bool)
        is_selected = *con_bool;

    this->setMinimumSize(100,20);
    this->resize(100,20);
    left = new QLabel(this);
    left->setAutoFillBackground(true);
    right= new QLabel(this);
    //设置左侧图标属性和位置
    left->resize(20,20);
    left->move(0,0);
    QPalette palette;
    if(!is_selected)//按选中状态来选择显示的图片或颜色
        palette.setColor(QPalette::Background,col_non_checked);
    else
        palette.setColor(QPalette::Background,col_checked);
    left->setPalette(palette);
    //设置右侧文字的属性和位置
    right->setMinimumSize(80,20);
    right->resize(80,20);
    right->setAlignment(Qt::AlignCenter);
    right->setText("TDCheckBox");//唯一和普通构造函数有区别的地方
    right->move(20,0);

}
//设置控件的自动遮罩
void TDCheckbox::setAutoMask()
{   //如果pic_checked加载图片，设置他的遮罩为左图片遮罩
    if(!pic_checked.isNull()){
        left->setMask(pic_checked.mask());
        this->setMask(left->mask());
    }
}

void TDCheckbox::connectToBool(bool *boolean)
{
    this->con_bool = boolean;
    if(NULL != con_bool)
        is_selected = *con_bool;
    if(is_default){//默认情况下，执行颜色替换
        QPalette palette;
        if(!is_selected)//按选中状态来选择显示的图片或颜色
            palette.setColor(QPalette::Background,col_non_checked);
        else
            palette.setColor(QPalette::Background,col_checked);
        left->setPalette(palette);
    }else{//非默认情况下执行图片的替换
        if(!is_selected){
            left->setPixmap(pic_non_checked);
        }
        else{
            left->setPixmap(pic_checked);
        }

    }
}

TDCheckbox::~TDCheckbox()
{

}

void TDCheckbox::mousePressEvent(QMouseEvent *e)
{
    if(Qt::LeftButton == e->button()){//左键触发
        //通过改变状态的接口改变状态，传参为当前选中状态的非值(即现在被选中，则切换成没选中，反之一样)
        setChecked(!is_selected);
        //在鼠标离开事件里调用父类的鼠标按下事件。
        TDAbstractButton::mouseReleaseEvent(e);
    }
    //2017/1/6  添加
    TDAbstractButton::mousePressEvent(e);
}

void TDCheckbox::mouseReleaseEvent(QMouseEvent *)
{
    //无效化复选框类的鼠标离开事件，因为要在鼠标按下事件里触发。
}

void TDCheckbox::setText(const QString &text)
{
    //如果用空文本，则说明不想有右控件，则去除右控件的部分
    //并不再执行right.setText();
    if("" == text){
        //把右控件释放掉
        delete right;
        right = NULL;
        this->setMinimumSize(left->size());
        this->resize(left->size());
        //this->setAutoMask();
        return ;
    }
    if(NULL != right){
        right->setText(text);
    }

}
//返回是否被选中的状态
bool TDCheckbox::isChecked() const
{
    return is_selected;
}
//改变选中状态的外部接口
void TDCheckbox::setChecked(bool check)
{
    if(is_default){//如果是默认情况，改变左控件颜色
        if(!check){//如果传入的是false，则执行这一段代码，设置选中状态为假，并切换颜色
            is_selected = false;
            if(NULL != con_bool)//只有在不为空时才改变其值
                *con_bool = false;//改变关联变量的值为false
            QPalette palette;
            palette.setColor(QPalette::Background,col_non_checked);
            left->setPalette(palette);
        }else {//反之亦然
            is_selected = true;
            if(NULL != con_bool)//只有在不为空时才改变其值
                *con_bool = true;//改变关联变量的值为false
            QPalette palette;
            palette.setColor(QPalette::Background,col_checked);
            left->setPalette(palette);
        }
    }else {//非默认情况，需要执行图片的替换
        if(!check){//同样如果传入的是false，则执行这一段代码，设置选中状态为假，并切换图片
            is_selected = false;
            if(NULL != con_bool)//只有在不为空时才改变其值
                *con_bool = false;//改变关联变量的值为false
            left->setPixmap(pic_non_checked);
        }
        else{
            is_selected = true;
            if(NULL != con_bool)//只有在不为空时才改变其值
                *con_bool = true;//改变关联变量的值为false
            left->setPixmap(pic_checked);
        }

    }
}

void TDCheckbox::setColor(const QColor &col_che, const QColor &col_non)
{
    //默认方式才有效
    if(is_default){
        //用自定义颜色初始化,用用户指定颜色初始化
        col_checked = col_che;
        col_non_checked = col_non;

        //如果颜色是无效的，用默认颜色初始化颜色
        if(!col_checked.isValid()&&!col_non_checked.isValid()){
            //初始化为默认颜色显示选中和被选中的状态
            col_checked = Qt::red;
            col_non_checked = Qt::darkRed;
        }
        if(NULL != con_bool)
            is_selected = *con_bool;

        QPalette palette;
        if(!is_selected)//按选中状态来选择显示的图片或颜色
            palette.setColor(QPalette::Background,col_non_checked);
        else
            palette.setColor(QPalette::Background,col_checked);
        left->setPalette(palette);
    }

}

QLabel *TDCheckbox::getLeftLabel()
{
    return this->left;
}

QLabel *TDCheckbox::getRightLabel()
{
    return this->right;
}
