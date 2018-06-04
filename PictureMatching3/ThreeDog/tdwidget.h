/***************************************************
* Program Assigment : 自定义窗体类
* File Name: tdwidget.h
* Author : ThreeDog
* Date : 2016/11/30
* Description: 自定义窗体类，实现用图片代替不规则窗体，可拖动。
*
* **************************************************/
#ifndef TDWIDGET_H
#define TDWIDGET_H
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
class TDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TDWidget(QWidget *parent = 0);
    //2017、1、9 修改构造函数，增加一个bool变量，是否显示边框,默认不显示
    TDWidget(QString img_path,QWidget *parent = 0,bool show_window = false);
    void setMoveEnable(const bool can_move);
    bool moveEnable() const;
    void setAutoMask();

    ~TDWidget();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private :
    bool is_press;
    bool move_enable;
    QPoint old_pos;
    QPixmap bg_pic;
};

#endif // TDWIDGET_H
