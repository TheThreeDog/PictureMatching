/**************************************************************
 * File Name   : tdlistwidget.cpp
 * Author      : ThreeDog
 * Date        : Mon Jan 16 17:02:17 2017
 * Description : 自定义列表窗体，包含TDListWidget和TDListWidgetItem类
 *          TDListWidgetItem有默认的初始化方式，子窗体自适应大小，继承自
 *          TDSCrollArea类。子控件必须继承TDListWidgetItem类。另外子控件
 *          必须重新实现setText()函数，如果使用图片，就用空方法体代替。
 *
 **************************************************************/

#include "tdlistwidget.h"

TDListWidgetItem::TDListWidgetItem(QWidget *parent, Qt::Orientation ot)
    :TDMenuButton(parent)
{
    init(ot);
}

TDListWidgetItem::TDListWidgetItem(const QString text, QWidget *parent, Qt::Orientation ot)
    :TDMenuButton(text,parent)
{
    init(ot);
}

TDListWidgetItem::TDListWidgetItem(const QString &pic_nor, const QString &pic_hov, const QString &pic_sel, QWidget *parent)
    :TDMenuButton(pic_nor,pic_hov,pic_sel,parent)
{
    this->show();
}

void TDListWidgetItem::setColor(const QColor &col_nor, const QColor &col_hov, const QColor &col_pre)
{
    TDMenuButton::setColor(col_nor,col_hov,col_pre);
}

void TDListWidgetItem::setText(const QString &text)
{
    if(this->isDefault())
        TDMenuButton::setText(text);
    else
        return ;
}

void TDListWidgetItem::init(Qt::Orientation ot)
{
    if(Qt::Horizontal == ot){
        this->setMaximumSize(30,100);
        //设置文字纵向显示
        this->setWordWrap(true);
        this->setAlignment(Qt::AlignTop);
        //this->setMinimumHeight(30);
    }else if(Qt::Vertical == ot){
        this->resize(100,30);
        //this->setMinimumWidth(30);
    }
    this->setAlignment(Qt::AlignCenter);

}

int TDListWidgetItem::getIndex() const
{
    return this->index;
}

void TDListWidgetItem::setIndex(const int i)
{
    this->index = i;
}

TDListWidgetItem::~TDListWidgetItem()
{

}

void TDListWidgetItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClicked(index);
}

void TDListWidgetItem::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked(index);
    TDMenuButton::mouseReleaseEvent(e);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

TDListWidget::TDListWidget(QWidget *parent, Qt::Orientation ot)
    :TDScrollArea(parent)
{
    orientation = ot;
    QWidget *w = new QWidget;
    w->resize(100,100);
    this->setWidget(w);
    spacing = 5;
    current_index = 0;
}
//添加新条目，设置条目上的文字，以默认的非图片形式添加
void TDListWidget::addItem(const QString &text)
{
    //生成条目
    TDListWidgetItem *item = new TDListWidgetItem(text,sub_widget,orientation);
    if(Qt::Horizontal ==  orientation){//横向
        if( 0 != item_list.count())//将条目移动到相应位置//记得加上spacing
            item->move(item_list.last()->x()+item->width()+spacing,item_list.last()->y());
        else{
            item->move(0,0);
        }
        //重设子窗体的大小 //注意加上spacing
        sub_widget->resize((item->width()+spacing)*(item_list.count()+1),item->height());
        this->resize(this->width(),this->height());
    }else if(Qt::Vertical == orientation){ //纵向
        if( 0 != item_list.count())//将条目移动到相应位置
            item->move(item_list.last()->x(),item_list.last()->y()+item->height()+spacing);
        else
            item->move(0,0);
        sub_widget->resize(item->width(),(item->height()+spacing)*(item_list.count()+1));
        this->resize(this->width(),this->height());
    }
    //设置条目的数字标识
    item->setIndex(item_list.count());
    if(1 == item->getIndex())//第一个条目，设置为被选中，并且设置当前index为1
        this->current_index = 1;
    item_list.append(item);
    //连接条目的信号和本窗体的槽，监控点击的条目的效果。
    connect(item,SIGNAL(clicked(int)),this,SLOT(itemClick(int)));
    connect(item,SIGNAL(doubleClicked(int)),this,SLOT(itemDoubleClick(int)));
}

//添加条目
void TDListWidget::addItem(TDListWidgetItem *item)
{
    if(NULL == item)
        return ;
    item->setParent(sub_widget);
    if(Qt::Horizontal ==  orientation){
        if( 0 != item_list.count())
            item->move(item_list.last()->x()+item->width()+spacing,item_list.last()->y());
        else{
            item->move(0,0);
        }
        //重设子窗体的大小
        sub_widget->resize((item->width()+spacing)*(item_list.count()+1),item->height());
        this->resize(this->width(),this->height());
    }else if(Qt::Vertical == orientation){
        if( 0 != item_list.count())
            item->move(item_list.last()->x(),item_list.last()->y()+item->height()+spacing);
        else
            item->move(0,0);
        //重设子窗体的大小
        sub_widget->resize(item->width(),(item->height()+spacing)*(item_list.count()+1));
        this->resize(this->width(),this->height());
    }
    //设置条目的数字标识
    item->setIndex(item_list.count());
    if(1 == item->getIndex())//第一个条目，设置为被选中，并且设置当前index为1
        this->current_index = 1;
    item_list.append(item);
    //连接条目的信号和本窗体的槽，监控点击的条目的效果。
    connect(item,SIGNAL(clicked(int)),this,SLOT(itemClick(int)));
    connect(item,SIGNAL(doubleClicked(int)),this,SLOT(itemDoubleClick(int)));

}
//插入一个文字条目，在index的位置插入。
void TDListWidget::insertItem(int index, const QString &text)
{
    if(index >= item_list.count())
        return ;
    //生成条目
    TDListWidgetItem *item = new TDListWidgetItem(text,this,orientation);
    if(Qt::Horizontal ==  orientation){
        if( 0 != item_list.count()){
            //将标识位置之后的所有条目后移并设置下标+1
            for(int i = item_list.count()-1;i >= index-1; i--)
            {
                TDListWidgetItem *t = item_list.at(i);
                t->setIndex(i+1);
                t->move(t->x()+t->width()+spacing,t->y());
            }
            item->move(item_list.at(index-2)->x()+item->width()+spacing,item_list.last()->y());
            //重设子窗体的大小
            sub_widget->resize((item->width()+spacing)*(item_list.count()+1),item->height());
            this->resize(this->width(),this->height());
        }
        else{
            item->move(0,0);
        }
    }else if(Qt::Vertical == orientation){
        if( 0 != item_list.count()){
            //将标识位置之后的所有条目后移并设置下标+1
            for(int i = item_list.count()-1;i >= index-1; i--)
            {
                TDListWidgetItem *t = item_list.at(i);
                t->setIndex(i+1);
                t->move(t->x(),t->y()+t->height()+spacing);
            }
            item->move(item_list.last()->x(),item_list.at(index-2)->y()+item->height()+spacing);
            //重设子窗体的大小
            sub_widget->resize(item->width(),(item->height()+spacing)*(item_list.count()+1));
            this->resize(this->width(),this->height());
        }
        else
            item->move(0,0);
    }
    //设置条目的数字标识
    item->setIndex(index-1);
    item_list.insert(index,item);///////////////////////////////////////////////////////////////////////////////
    //连接条目的信号和本窗体的槽，监控点击的条目的效果。
    connect(item,SIGNAL(clicked(int)),this,SLOT(itemClick(int)));
    connect(item,SIGNAL(doubleClicked(int)),this,SLOT(itemDoubleClick(int)));

}

//在index的位置插入item条目
void TDListWidget::insertItem(int index, TDListWidgetItem *item)
{
    if(index >= item_list.count())
        return ;
    //生成条目
    if(Qt::Horizontal ==  orientation){
        if( 0 != item_list.count()){
            //将标识位置之后的所有条目后移并设置下标+1
            for(int i = item_list.count()-1;i >= index-1; i--)
            {
                TDListWidgetItem *t = item_list.at(i);
                t->setIndex(i+1);
                t->move(t->x()+t->width()+spacing,t->y());
            }
            item->move(item_list.at(index-2)->x()+item->width()+spacing,item_list.last()->y());
            //重设子窗体的大小
            sub_widget->resize((item->width()+spacing)*(item_list.count()+1),item->height());
            this->resize(this->width(),this->height());
        }
        else{
            item->move(0,0);
        }
    }else if(Qt::Vertical == orientation){
        if( 0 != item_list.count()){
            //将标识位置之后的所有条目后移并设置下标+1
            for(int i = item_list.count()-1;i >= index-1; i--)
            {
                TDListWidgetItem *t = item_list.at(i);
                t->setIndex(i+1);
                t->move(t->x(),t->y()+t->height()+spacing);
            }
            item->move(item_list.last()->x(),item_list.at(index-2)->y()+item->height()+spacing);
            //重设子窗体的大小
            sub_widget->resize(item->width(),(item->height()+spacing)*(item_list.count()+1));
            this->resize(this->width(),this->height());
        }
        else
            item->move(0,0);
    }
    //设置条目的数字标识
    item->setIndex(index-1);
    item_list.insert(index,item);///////////////////////////////////////////////////////////////////////////////////
    //连接条目的信号和本窗体的槽，监控点击的条目的效果。
    connect(item,SIGNAL(clicked(int)),this,SLOT(itemClick(int)));
    connect(item,SIGNAL(doubleClicked(int)),this,SLOT(itemDoubleClick(int)));

}

int TDListWidget::getCount() const
{
    //获取条目总数
    return this->item_list.count();
}

//获取当前条目的指针
TDListWidgetItem *TDListWidget::getCurrentItem()
{
    if(0 != this->getCurrentIndex())
        return getItem(getCurrentIndex());
    return NULL;
}

//获取当前条目的下标
int TDListWidget::getCurrentIndex() const
{
    for(int i = 0; i < this->getCount();i++){
        if(item_list.at(i)->isSelected())
            return item_list.at(i)->getIndex();
    }
    return 0;
}

//通过指针获取下标
int TDListWidget::getIndex(TDListWidgetItem *item) const
{
    for(int i = 0; i < this->getCount();i++){
        if(item_list.at(i) == item)
            return item_list.at(i)->getIndex();
    }
    return 0;
}

//通过下标获取下标指针
TDListWidgetItem *TDListWidget::getItem(const int index)
{
    if(index >= item_list.count())
        return NULL;
    else
        return item_list.at(index);
}

void TDListWidget::setSpacing(const int spac)
{
    this->spacing = spac;
}

int TDListWidget::getSpacing() const
{
    return this->spacing;
}

TDListWidget::~TDListWidget()
{

}

void TDListWidget::itemDoubleClick(int index)
{
    if(current_index != index){
        emit currentItemChanged(getItem(current_index),getItem(index));
        current_index = index;
        emit currentIndexChanged(index);
        emit itemChanged(getItem(index));
    }
    emit itemDoubleClicked(getItem(index));
}

void TDListWidget::itemClick(int index)
{
    if(current_index != index){
        emit currentItemChanged(getItem(current_index),getItem(index));
        current_index = index;
        emit currentIndexChanged(index);
        emit itemChanged(getItem(index));
    }
    emit itemClicked(getItem(index));

}



