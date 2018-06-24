/*游戏中需要用到的宏定义*/

#ifndef __APPMACROS_H__
#define __APPMACROS_H__


#define MAP_WIDTH 3820		//地图宽度，单位像素
#define MAP_HEIGHT 2160			//地图高度，单位像素

#define DESIGN_SCREEN_WIDTH 1280			//设计屏幕分辨率，宽度
#define DESIGN_SCREEN_HEIGHT 720			//设计屏幕分辨率，高度

//#define MAX_BEAN_NUM 4800			//地图中最大食物数量
#define INIT_PRICK_NUM 15           //初始刺球数量

#define MAP_DIVISION_X 6			//地图横向划分，6个屏幕宽大小
#define MAP_DIVISIOIN_Y 8			//地图纵向划分，8个屏幕高大小
#define MAP_DIVISION_BEAN_NUM 100			//每个划分区域的豆子数量

#define BEAN_SCORE 1			//每个豆子分值
#define BEAN_RADIUS 8			//豆子半径，单位像素

#define PLAYER_INITIAL_RADIUS 19			//玩家初始半径，单位像素
#define PLAYER_INITIAL_SCORE 10			//玩家初始分值
#define PLAYER_INITIAL_SPEED 6			//玩家初始速度
#define PLAYER_INITIAL_VECTOR 0.5	        //玩家位移最小量
#define RIVAL_INITIAL_VECTOR 0.5	        //敌人位移最小量
#define PLAYER_MIN_SPEED 1			        //玩家最小速度
#define PLAYER_MAX_DIVISION_NUM 30			//玩家最大分身数量
#define PLAYER_MIN_DIVIDE_SCORE 38			//玩家最低分身需要的分值
#define PLAYER_MIN_DIVIDE_DISTANCE 200			//玩家最小分身距离
#define PLAYER_MIN_SHOW_VESTMENT_SCORE 200	  //显示圣衣需要的分值
#define PLAYER_CONCENTRATE_SPEED 1			//玩家中和速度

#define MAX_RIVAL_NUM 15			//地图中最大敌人数量

#define MAX_EAT_PRICK_DIVISION_NUM 6			//碰到刺最大分身数量
#define MAX_EAT_PRICK_SCORE 46			//碰到刺分裂出分身的最大分值

#define PRICK_INITIAL_SCORE 100			//绿刺初始分值
#define PRICK_INITIAL_RADIUS 62			//绿刺初始半径，单位像素
#define PRICK_SPLIT_DISTANCE 128			//碰到绿刺分裂出分身的距离

#define MIN_EAT_MULTIPLE 1.25			//游戏中吃的最小倍数
#define MIN_CHASE_MULTIPLE 1.25         //最小追逐倍数
//#define GAME_TOTAL_TIME 100			//游戏总时间


#define PI 3.14f			//PI的定义

#endif