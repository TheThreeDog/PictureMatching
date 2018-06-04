/**************************************************************
 * File Name   : tdstackbutton.h
 * Author      : ThreeDog
 * Date        : Thu Jan 05 10:19:40 2017
 * Description : 自定义堆叠按钮，利用一个内置的StackWidget实现，效果是点击
 *          一个按钮触发效果后切换为另一个按钮。例如音乐播放器中播放模式的按钮
 *
 **************************************************************/
#ifndef _TDSTACKBUTTON_H_ 
#define _TDSTACKBUTTON_H_ 
#include "tdwidget.h"
#include "tdabstractbutton.h"
#include <QStackedLayout>
class TDStackButton : public TDWidget
{
    Q_OBJECT

public:
    explicit TDStackButton(TDWidget *parent = 0);
    //添加一个按钮
    void addButton(TDAbstractButton * button);
    //移除按钮
    void removeButton(QWidget * button);
    void removeButton(const int index);
    void removeAllButton();
    //获取当前按钮或下标
    int getCurrentIndex() const ;
    TDAbstractButton * getCurrentButton() const ;
    ~TDStackButton();
signals:
    void buttonChanged(int index);
    void buttonRemoved(int index);
public slots:
    //设置当前按钮
    void setCurrentIndex(const int index);
    void setCurrentButton(TDAbstractButton *button);
    //切换至下一个按钮
    void toNextButton();

private:
    QStackedLayout * stack_layout;

};

#endif  //TDSTACKBUTTON
