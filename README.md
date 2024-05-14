# 2024project


高级语言程序设计大作业实验报告

南开大学 计算机大类

姓名 马英昊

学号 2312252

班级 0927

2024年5月14日

一.	作业题目	

二.	开发软件	

三.	主要流程	

1． 整体流程	

2．算法或公式

四.	收获	


一. 	作业题目
基于C++及easyx的简单平面射击游戏

二. 	开发软件
Visual Studio 2022，easyx


三. 	主要流程

1.总体流程：大体分为三部分：menu(开始菜单)，setting(设置)，游戏主循环

Menu：
menu中，使用鼠标点击进行操作，可选择进入setting或进入游戏主循环，在游戏主循环中可以通过单击esc键、死亡后进入menu，在setting中可通过单击”返回”进入menu

Setting：
设置中，使用鼠标点击进行操作，可对于游戏主循环中部分参数进行修改；在menu中可鼠标点击进入setting，在游戏主循环中可以通过单击“S”键进入setting， 
设置界面中有如下选项，敌人血量会增长，会出现boss，无敌，右键秒杀，敌人血量显示。
第一个，敌人血量会增长，开启时敌人血量会随着敌人被消灭数量而增长，取消后，我们发现敌人血量不再增长。值得一提的是，敌人血量会在一定范围内浮动，最低等级会分别出现10，20，30血量的敌人。
第二个，会出现boss。取消后不会出现boss。
第三个，无敌。开启后玩家保持无敌状态。
第四个，右键秒杀。开启后，在游戏内点击右键可以击杀场上所有敌人和boss。
第五个，敌人血量显示，关闭后敌人血量不再显示。

游戏主循环：

在游戏主循环中，使用鼠标及键盘进行操作,用一系列Move()函数来调整各类对象的位置，用一系列函数来判定各类对象的接触及后续事件，用cleardevice();FlushBatchDraw();Print()函数来进行各类对象的打印，用delay_fps(_tick);函数来调整游戏主循环运行帧率；
界面：左上角心的个数表示player的生命值，正上方的分数代表被击败的enemy数量(enemyDeadNum)

player(玩家)对象，可有以下操作：A键向左移动，D键向右移动，W键进行跳跃，可进行二段跳，鼠标的位置进行瞄准，鼠标左键单击进行子弹发射，初始有3生命值，子弹伤害为10，可拾取(本体碰触)enemy被击败后概率掉落的HeartAdd回复1生命值，可拾取(本体碰触)enemy被击败后概率掉落的toKillBoss加10子弹伤害,并击败Boss。本体碰触到enemy和Boss时会扣除1生命值，同时进入1秒的无敌状态(God)，无敌状态下会让碰触到的enemy立刻被击败。

Enemy对象，每2秒刷新一次新enemy,刷新位置随机在左、上、右边界的随机位置,随着分数的提高会由一次刷新一个到一次刷新两个,,有一定生命值(生命值会随着游戏分数增长而提高)，会被子弹和无敌状态下的player击败，有一定概率掉落HeartAdd和toKillBoss，两者都采用了伪随机(PseudoRandom)来调整掉落概率,会实时检测player的位置，以恒定平面速度进行向player移动。 

Boss对象。刷新enemy时,若当前分数是3的倍数时会同时刷新一个Boss。当player拾取toKillBoss时会被击败,无其他正常方式被击败。会实时检测player的位置，以恒定平面速度进行向player移动。 

gun对象 在player对象附近,用以指示player发射子弹的方向

2．算法或公式
(1).player,enemy,Boss,gun,HeartAdd,toKillBoss对象均是在obj类中定义，obj类中包括了int potx;int poty;MOTION motion;int life;来表示对象的位置,运动情况,生命值(是否存在)，其中,MOTION类包括了int v_x;int v_y;int a_x;int a_y; 来表示对象的运动的水平(x)、竖直(y)方向速度和加速度。在每次游戏主循环中处理一次运动计算，

(2).对于enemy、Boss向player的移动方向和gun的朝向，使用以下思路：得到两个位置的坐标，通过atan2();函数得到角度，继而处理方向

(3) 游戏主循环的帧率控制，在主循环中使用delay_fps();函数，传入要求得到的帧率来得到其中delay_fps();如下定义

void delay_ms(unsigned int milliseconds) 
{

	clock_t start_time = clock(); // 获取当前时钟时间
 
	while (clock() < start_time + milliseconds); // 等待指定的毫秒数
 
}

void delay_fps(unsigned int fps) 
{

	unsigned int frame_time = 1000 / fps; // 计算每帧的时间间隔（毫秒）
 
	delay_ms(frame_time); // 调用延迟函数
 
}

(4)游戏主循环中的各类接触情况的判断，核心由以下函数计算

bool IfTouch(int x, int y, int W, int H, int _x, int _y, int _R) 
{

	if (_x<x - _R || _x>x + W + _R || _y<y - _R || _y>y + H + _R) 
 
 	{
  
		return 0;
  
	}
 
	else
 
		return 1;
  
}

(5)游戏主循环中对于player的运动操控,会出现由于每次循环中计算时间不一出现的卡顿解决方法使用bool isUp;等bool类型的变量来控制移动，对于键盘按键的按下和弹起分别修改对应bool变量的真假。


四. 	收获

1.	完成了一个大体完整项目，对于函数声明和定义有了更深刻的认识

2.	大量应用了函数引用，深刻认识到模块化的作用。

3.	切实体会到类和对象的使用方便性
