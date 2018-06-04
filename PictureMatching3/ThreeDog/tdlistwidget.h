/**************************************************************
 * File Name   : tdlistwidget.h
 * Author      : ThreeDog
 * Date        : Mon Jan 16 17:02:17 2017
 * Description : 自定义列表窗体，包含TDListWidget和TDListWidgetItem类
 *          TDListWidgetItem有默认的初始化方式，子窗体自适应大小，继承自
 *          TDSCrollArea类。子控件必须继承TDListWidgetItem类。另外子控件
 *          必须重新实现setText()函数，如果使用图片，就用空方法体代替。
 *
 **************************************************************/
#ifndef _TDLISTWIDGET_H_ 
#define _TDLISTWIDGET_H_ 
#include <QLabel>
#include "tdscrollarea.h"
#include "tdmenubutton.h"
#include <QMouseEvent>
class TDListWidgetItem : public TDMenuButton
{
    Q_OBJECT

public :
    explicit TDListWidgetItem(QWidget *parent = 0,Qt::Orientation ot = Qt::Vertical);
    explicit TDListWidgetItem(const QString text,QWidget *parent = 0,Qt::Orientation ot = Qt::Vertical);
    explicit TDListWidgetItem(const QString &pic_nor,const QString &pic_hov,const QString &pic_sel,QWidget *parent = 0);
    void setColor(const QColor &col_nor,const QColor &col_hov,const QColor &col_pre);
    //设置文字，所有的子类必须实现(为了配合TDListWidget中的接口)
    virtual void setText(const QString &text);
    //以默认方式对变量进行初始化
    void init(Qt::Orientation ot);
    int getIndex() const;
    void setIndex(const int i);
    ~TDListWidgetItem();
signals:
    void doubleClicked(int index);
    void clicked(int index);
protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private :
    //每一个条目的唯一标识
    int index;
};

class TDListWidget : public TDScrollArea
{
    Q_OBJECT

public:
    explicit TDListWidget(QWidget *parent = 0,Qt::Orientation ot = Qt::Vertical);
    //添加组件
    void addItem(const QString &text);
    void addItem(TDListWidgetItem *item);
    void insertItem(int index,const QString &text);
    void insertItem(int index,TDListWidgetItem *item);
    //获取总数
    int getCount() const;
    //获取当前条目或下标
    TDListWidgetItem* getCurrentItem();
    int getCurrentIndex() const;
    //获取组件||下标
    int getIndex(TDListWidgetItem* ) const;
    TDListWidgetItem* getItem(const int index);
    //删除(2017/2/4尚未实现)
    bool removeItem(const int index);
    bool removeItem(TDListWidgetItem* item);
    //获取、设置 spacing
    void setSpacing(const int spac);
    int getSpacing () const;
    ~TDListWidget();
signals:
    void currentItemChanged(TDListWidgetItem * previous, TDListWidgetItem * current);
    void currentIndexChanged(int current);
    void itemChanged(TDListWidgetItem * item);
    void itemClicked(TDListWidgetItem * item);
    void itemDoubleClicked(TDListWidgetItem * item);
private slots:
    //私有的槽函数
    void itemDoubleClick(int index);
    void itemClick(int index);
private:
    //垂直or水平
    Qt::Orientation orientation;
    QVector<TDListWidgetItem *> item_list;
    int spacing;
    int current_index;
};

#endif  //TDLISTWIDGET
