#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "ThreeDog/tdwidget.h"
#include "ThreeDog/tdpushbutton.h"
#include "ThreeDog/tdmenubutton.h"
#include "myitem.h"
#include <QTimerEvent>
#include "widget.h"

class GameMain : public TDWidget
{
    Q_OBJECT

public:
    explicit GameMain(QWidget *parent = 0);
    //生成所有的方块
    void createItems();
    //判断可以连通的函数
    bool canConnect(MyItem *item1,MyItem *item2);
    //重载一个连通函数接口
    bool canConnect(int x1,int y1,int x2,int y2);
    //判断不同请况下  可以连通的函数
    bool horizontalCheck(int x1,int y1,int x2,int y2);//横向校验
    bool verticalCheck(int x1,int y1,int x2,int y2);//纵向校验
    bool turnOnceCheck(int x1,int y1,int x2,int y2);//一个拐点的校验
    bool turnTwiceCheck(int x1,int y1, int x2,int y2);//两个拐点的校验
    //创建对应的另一个方块
    void creatAnotherItem(int index);
    //判断是否胜利
    bool isVictory();

    //重新开始
    void restart();
    //重新排列
    void reorder();
    //交换方块的函数
    void swapItem(int x1,int y1,int x2,int y2);
    //提示
    void prompt();
    //自动消除方块的函数
    bool eraser(int x1,int y1,int x2,int y2);
    //退出
    void exitGame();


protected:
    void timerEvent(QTimerEvent *e);

public slots:
    //获取被点击方块信息的槽函数
    void itemClicked(MyItem *item ,int i);
private:
    //存放所有方块的数组
    MyItem * items[11][6];
    //保存上一次点击的index
    int currentIndex;
    MyItem * curItem;
    //定时器ID
    int timerId;
};

#endif // GAMEMAIN_H








