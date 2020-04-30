#include "gamemain.h"
#include <ctime>
#include <QDebug>

#include <iostream>
using namespace std;

GameMain::GameMain(QWidget *parent)
    :TDWidget(":/img/game_main_with_logo.png",parent)
{
    //生成四个导航栏按钮
    TDPushButton * guideBtn1 = new TDPushButton(":/img/restart_normal.png",":/img/restart_hover.png",":/img/restart_press.png",this);
    guideBtn1->move(140,41);
    //重新开始
    guideBtn1->setCallback(this,my_selector(GameMain::restart));
    TDPushButton * guideBtn2 = new TDPushButton(":/img/reorder_normal.png",":/img/reorder_hover.png",":/img/reorder_press.png",this);
    guideBtn2->move(250,41);
    //重新排序
    guideBtn2->setCallback(this,my_selector(GameMain::reorder));
    TDPushButton * guideBtn3 = new TDPushButton(":/img/prompt_normal.png",":/img/prompt_hover.png",":/img/prompt_press.png",this);
    guideBtn3->move(360,41);
    //提示
    guideBtn3->setCallback(this,my_selector(GameMain::prompt));
    TDPushButton * guideBtn4 = new TDPushButton(":/img/exit_normal.png",":/img/exit_hover.png",":/img/exit_press.png",this);
    guideBtn4->move(470,41);
    //结束游戏
    guideBtn4->setCallback(this,my_selector(GameMain::exitGame));

    //初始化指针数组中所有都只想空
    for(int i = 0 ; i< 11 ; i++)
        for(int j = 0; j < 6 ; j++)
            items[i][j] = NULL;
    //初始化当前下标为0，代表没有选中的图片
    currentIndex = 0;
    //初始化当前选中的方块为空、代表没有选中
    curItem = NULL;
    //调用creatItems生成方块
    this->createItems();
    //游戏开始启动定时器
    timerId = this->startTimer(10000);

}
//生成方块
void GameMain::createItems()
{
    srand(time(NULL));
    int randIndex;
    //生成所有的方块。
    //给数组中一个个赋值。
    QString str1,str2,str3;
    for(int i = 0; i < 11 ; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(items[i][j] == NULL){
                //通过随机数指定按哪个图片进行生成
                randIndex = rand()%14+1;
                str1 =":/img/"+ QString("%1").arg(randIndex)+"_normal.png";
                str2 =":/img/"+ QString("%1").arg(randIndex)+"_hover.png";
                str3 =":/img/"+ QString("%1").arg(randIndex)+"_selected.png";

                items[i][j] = new MyItem(str1,str2,str3,this);
                items[i][j]->move(100+i*65,100+j*65);
                //每一个方块通过下标计算位置并移动
                items[i][j]->setIndex(randIndex);

                //绑定方块被点击的信号和本地槽函数
                connect(items[i][j],SIGNAL(clicked(MyItem*,int)),this,SLOT(itemClicked(MyItem*,int)));
                //每生成一个方块，就生成另一个对应的方块，保证每个方块都是偶数个
                creatAnotherItem(randIndex);
            }
        }
    }
    //方块的图片是随机的。
}
//判断可以连通的函数
bool GameMain::canConnect(MyItem *item1, MyItem *item2)
{
    //先校验指针不为空
    if(item1 == NULL || item2 == NULL)
        return false;
    //提取两个方块数组中所处的位置
    int x1 = (item1->x()-100)/65;
    int y1 = (item1->y()-100)/65;
    int x2 = (item2->x()-100)/65;
    int y2 = (item2->y()-100)/65;
    // bool ret = false;
    // ret = canConnect(x1,x2,y2,y2);
    // return ret;
    return canConnect(x1,y1,x2,y2);

}
//重载一个连通函数接口
bool GameMain::canConnect(int x1, int y1, int x2, int y2)
{
    //先判断横向可连通
    if(horizontalCheck(x1,y1,x2,y2))
        return true;
    //在判断纵向可连通
    if(verticalCheck(x1,y1,x2,y2))
        return true;
    //判断一个拐点的可连通情况
    if(turnOnceCheck(x1,y1,x2,y2))
        return true;
    //判断两个拐点的可连通情况
    if(turnTwiceCheck(x1,y1,x2,y2))
        return true;
    //都不可连通，返回false
    return false;
}

bool GameMain::horizontalCheck(int x1, int y1, int x2, int y2)
{
    //横向
    //判断两次点击的不是同一个方块
    if(x1 == x2 && y1 == y2)
        return false;
    //判断个的纵坐标相同
    if(y1 != y2)
        return false;
    int startX = min(x1,x2);
    int endX = max(x1,x2);
    //判断两个方块是否相邻
    if((endX - startX) == 1)
        return true;
    //判断两个方块通路上是否都是NULL，有一个不是，就说明不能联通，返回false
    for(int i = startX+1; i < endX; i++){
        if(items[i][y1] != NULL)
            return false;
    }
    return true;
}

bool GameMain::verticalCheck(int x1, int y1, int x2, int y2)
{
    //纵向校验
    //判断两次点击不是同一个方块
    if(x1 == x2 && y1 == y2)
        return false;
    //判断两个横坐标相同
    if(x1 != x2)
        return false;
    int startY = min(y1,y2);
    int endY = max(y1,y2);
    //判断两个方块是否相邻
    if((endY - startY) == 1)
        return true;
    //判断两方块儿通路上是否可连。
    for(int i = startY+1;i < endY; i++){
        if(items[x1][i] != NULL)
            return false;
    }
    return true;

}

bool GameMain::turnOnceCheck(int x1, int y1, int x2, int y2)
{
    //实现单拐点校验。
    if(x1 == x2 && y1 == y2)
        return false;
    //一个拐点，说明两个方块必须在不同行不同列！
    if(x1 != x2 && y1 != y2){
        //cx cy dx dy 记录两个拐点的坐标
        int cx = x1;
        int cy = y2;
        int dx = x2;
        int dy = y1;
        //拐点为空，从第一个点到拐点并且从拐点到第二个点可通，则整条路可通。
        if(items[cx][cy] == NULL){
            if(verticalCheck(x1,y1,cx,cy) && horizontalCheck(cx,cy,x2,y2))
                return true;
        }
        if(items[dx][dy] == NULL){
            if(horizontalCheck(x1,y1,dx,dy) && verticalCheck(dx,dy,x2,y2))
                return true;
        }
        return false;
    }
    return false;

}

/*
最麻烦的，有两个拐角的情况
两个拐角检测可分解为一个拐角检测和水平检测或垂直检测。即：

两个拐角检测 = 一个拐角检测 && (水平检测 || 垂直检测)

水平、垂直分别穿过 A B 共有四条直线，扫描直线上所有不包含 A B 的点，看是否存在一点 C ，满足以下任意一项：

    A 点至 C 点通过水平或垂直检测，C 点至 B 点可通过一个拐角连接。（图中用 C 表示）
    A 点至 C 点可通过一个拐角连接，C 点至 B 点通过水平或垂直连接。（图中用 C 下划线表示）
*/
bool GameMain::turnTwiceCheck(int x1, int y1, int x2, int y2)
{
    if(x1 == x2 && y1 == y2)
        return false;
    //遍历整个数组找合适的拐点
    for(int i = 0 ; i < 11; i++){
        for(int j = 0; j < 6; j++){
            //不为空不能作为拐点
            if(items[i][j] != NULL)
                continue;
            //不和被选方块在同一行列的  不能作为拐点
            if(i != x1 && i != x2 && j != y1 && j != y2)
                continue;
            //作为焦点的部分也要过滤掉
            if((i == x1 && j == y2)||( i==x2 && j == y1))
                continue;
            if(turnOnceCheck(x1,y1,i,j)&& (horizontalCheck(i,j,x2,y2)||verticalCheck(i,j,x2,y2)))
                return true;
            if(turnOnceCheck(i,j,x2,y2)&&(horizontalCheck(x1,y1,i,j)||verticalCheck(x1,y1,i,j)))
                return true;
        }
    }
    return false ;
}
//生成另一个同图片的方块，保证所有方块是偶数个
void GameMain::creatAnotherItem(int index)
{
    //构建创造方块的图片
    QString str1 =":/img/"+ QString("%1").arg(index)+"_normal.png";
    QString str2 =":/img/"+ QString("%1").arg(index)+"_hover.png";
    QString str3 =":/img/"+ QString("%1").arg(index)+"_selected.png";
    //生成两个随机数，确定新方块的位置
    int i = rand()%11 ;
    int j = rand()%6  ;
    //确定新随机的位置不能有方块
    while(items[i][j] != NULL){
        i = rand()%11 ;
        j = rand()%6  ;
        //一直随机，直到随机到为空的位置
    }
    //通过新位置，生成新方块
    items[i][j] = new MyItem(str1,str2,str3,this);
    items[i][j]->setIndex(index);
    items[i][j]->move(i*65+100,j*65+100);
    connect(items[i][j],SIGNAL(clicked(MyItem*,int)),this,SLOT(itemClicked(MyItem*,int)));
}

bool GameMain::isVictory()
{
    //遍历所有数组，判断数组不为空，直接返回否
    for(int i = 0;i < 11; i++)
        for(int j = 0; j < 6; j++)
            if(items[i][j] != NULL)
                return false;

    //所有节点都是空，游戏胜利，返回true
    return true;
}

void GameMain::restart()
{
    //重新开始游戏，关闭本窗体进入欢迎界面。
    Widget * w = new Widget();
    w->show();
    this->close();
}

//重新排序，
/*
 * 思路，选中一个方块，然后再随机选择一个不同的方块进行位置交换。
 * 把所有的方块都执行这样一次操作
 * 可以保证每种方块总数不会变，也可以保证已经消除的地方不会受影响，并实现了随机重新排列
*/
void GameMain::reorder()
{
    int randX,randY;
    //先确认交换的第一个方块
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 6; j++){
            if(items[i][j] != NULL){
                //随机生成另一个方块的坐标
                randX = rand()%11;
                randY = rand()%6;
                while(items[randX][randY] == NULL ||(randX == i && randY == j)){
                    //一直随机知道符合条件的方块
                    randX = rand()%11;
                    randY = rand()%6;
                }
                //位置交换
                swapItem(i,j,randX,randY);
            }
        }
    }
}

//交换两个方块的位置
void GameMain::swapItem(int x1,int y1,int x2,int y2)
{
    //交换两个方块的函数
    //保证两个方块不能一样
    if(x1 == x2 && y1 == y2)
        return ;
    //保证两个方块不能为空
    if(items[x1][y1] == NULL || items[x2][y2] == NULL)
        return ;
    //记录第一个交换点的原坐标
    int tempX = items[x1][y1]->x();
    int tempY = items[x1][y1]->y();
    //把交换点一移动到交换点二的位置上
    items[x1][y1]->move(items[x2][y2]->x(),items[x2][y2]->y());
    //把坐标点二移动到坐标点一的位置上
    items[x2][y2]->move(tempX,tempY);
    //交换回指针的指向
    MyItem * tempPtr = items[x1][y1];
    items[x1][y1] = items[x2][y2];
    items[x2][y2] = tempPtr;

}

//提示  让计算机进行消除
/*
 * 核心思想：把现存的每两个方块都进行一次判断，
 * 如果可以连通就执行消除的操作，如果过不是，就不执行，继续循环校验下一组
 *
 *
 */
void GameMain::prompt()
{
    //计算机执行连连看算法
    for(int i = 0; i < 11; i++){
        for( int j = 0; j < 6; j++){
            //以上两个for循环，定位第一个选中点
            if(items[i][j] != NULL){
                for(int m = 0; m < 11 ; m++){
                    for(int n = j; n < 6; n++){
                        if(items[m][n] != NULL ){
                            //后俩个for循环定位第二个选中点
                            if(items[i][j]->getIndex() == items[m][n]->getIndex()){
                                if(i != m || j != n){//如果两个点图片相同并且不是同一个点  执行消除
                                    if(eraser(i,j,m,n))//如果消除成功  直接返回
                                        return;
                                    else//如果没有，则继续循环
                                        continue;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//计算机自动消除
bool GameMain::eraser(int x1, int y1, int x2, int y2)
{
    if(x1 == x2 && y1 == y2)
        return false;
    //判断可连通的话，才进行消除
    if(canConnect(x1,y1,x2,y2)){
        delete items[x1][y1];
        delete items[x2][y2];
        items[x1][y1] = NULL;
        items[x2][y2] = NULL;
        this->killTimer(timerId);
        //判断胜负逻辑
        if(isVictory()){
            TDWidget * victory = new TDWidget(":/img/victory.png",this);
            victory->setMoveEnable(false);
            victory->move(0,0);
            return true;
        }
        //执行刷新定时器的操作
        timerId = this->startTimer(10000);
        return true;
    }
    return false;
}

void GameMain::exitGame()
{
    this->close();
}

//定时器的触发函数
void GameMain::timerEvent(QTimerEvent *e)
{
    //超时，显示游戏失败的图片
    TDWidget * defeat= new TDWidget(":/img/defeat.png",this);
    defeat->setMoveEnable(false);
    defeat->move(0,0);
    //游戏已经结束，就停止定时器。
    this->killTimer(timerId);
}

void GameMain::itemClicked(MyItem *item, int i)
{
    //判断如果两个记录值相等，进行相关操作
    if(i == currentIndex){
        if(curItem != NULL && canConnect(curItem,item)){
            //如果记录值相等并且不为空，可以进行消除
            delete curItem;
            delete item;
            //把数组中记录的指针置空
            for(int i = 0; i < 11; i++){
                for(int j = 0; j < 6 ; j++ ){
                    if(items[i][j] == item||items[i][j] == curItem)
                        items[i][j] = NULL;
                }
            }
            curItem = NULL;
            item = NULL;
            this->killTimer(timerId);
            //判断胜负逻辑
            if(isVictory()){
                TDWidget * victory = new TDWidget(":/img/victory.png",this);
                victory->setMoveEnable(false);
                victory->move(0,0);
                return ;
            }
            //执行刷新定时器的操作
            timerId = this->startTimer(10000);

            return ;
        }
    }
    //如果没有消除，赋值保留记录值
    curItem = item;
    currentIndex = i;

}







