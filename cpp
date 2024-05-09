//#include<iostream>
//读取数据
//处理数据
//绘制画面
#include<cmath>
#include<graphics.h>
#include<iostream>

#define win_Width 1920//输出窗口宽度
#define win_Height 1080//输出窗口高度
#define JumpAcc 40//跳跃能力
#define X_V 20//horizontal velocity水平速度
#define X_Af 3//水平阻力
#define _Floor 700
#define _tick 45//游戏帧率
#define _Gravity 40
#define playerH 100
#define playerW 50
#define enemyV 10
#define GunPlayerDistance 30

using namespace std;


struct MOTION {
	int v_x=0;
	int v_y=0;
	int a_x=0;
	int a_y=2;
};


struct obj {//移动物
	//POINT a;
	int potx=400;
	int poty=400;
	int _potx;
	int _poty;
	MOTION motion;
	int life;

}player,//玩家
enemy[10],
gun;
int enemyNum=0;
double gunD;

class event {
public:
	int time = 0;
	int num = 0;
};

struct Image {
	IMAGE background;
	IMAGE player;
	//IMAGE bullet;
	IMAGE gun;
	IMAGE gun_;
}image;

class Wall {
public:
	
	int a_x;//
	int a_y;//       a        b
	int b_x;//        +------+
	int b_y;//        |      |
	int c_x;//        +------+
	int c_y;//       d        c
	int d_x;//
	int d_y;//
	int W, H;
		//       a        b
		// a_y--  +------+
		//        |      |
		// c_y--  +------+
		//       d        c
		//        |      |
		//       a_x    c_x
	static int num;
	//Wall() { ; };
	Wall(int q, int w, int e, int r) {
		a_x = q; a_y = w;
		c_x = e; c_y = r;
		b_x = c_x; b_y = a_y;
		d_x = a_x; d_y = c_y;
		W = e - q;
		H = r - w;
		Wall::num++;
	}
}Floor(0,1000,1920,1080);
Wall *wall[10];
int Wall::num=0;

bool isUp = false;
bool isDown = false;
bool isLeft = false;
bool isRight = false;
bool UpinAir = 0;




int onFloor() {//判断是否踩在实体上
	if (player.poty >= win_Height-playerH) {//判断最底部1080
		UpinAir = 0;
		return 1;
	}
	//       a        b
	// a_y--  +------+
	//        |      |
	// c_y--  +------+
	//       d        c
	//        |      |
	//       a_x    c_x
	//
	/*for (int i = 0; i < Wall::num; i++) {
		if (player.potx < wall[i]->c_x || wall[i]->a_x - player.potx < playerW) {
			if (wall[i]->a_y - player.poty <= playerH&&wall[i]->a_y-player._poty>=playerH) {
				player.motion.v_y = 0;
				player.poty = wall[i]->a_y - playerH;
				break;
			}
		}
	}*/
		
	//for (int i = 0; i < Wall::num; i++) {//判断墙体
	//	//wall[i],player
	//	if (wall[i].a_x - player.potx < playerW&& wall[i].a_x > player.potx) {//墙体左侧
	//		player.potx = wall[i].a_x + playerW;
	//		player.motion.v_x = 0;
	//	}
	//	else if ( player.potx -wall[i].c_x&&wall[i].a_x < player.potx) {//墙体右侧
	//		player.potx = wall[i].a_x;
	//		player.motion.v_x = 0;
	//	}
		//if ( player.poty -wall[i].c_y < playerH && wall[i].c_y > player.poty) {//墙体底部
		//	player.potx = wall[i].a_x;
		//	player.motion.v_x = 0;
		//}
		//else if (wall[i].a_y - player.poty < playerH && wall[i].a_y > player.poty) {//墙体顶部

		//}
	

	return 0;
}

//void gravity(int G) {//重力影响
//	//if(!onFloor)
//	player.motion.a_y = G;
//	return;
//}

//移动优化

//void GameControl() {             //游戏控制GetAnsyncKey方案
//	//_getch();GetAnsyncKey();
//	if (onFloor() && GetAsyncKeyState(VK_UP)) {
//		player.motion.v_y -=JumpAcc;
//		
//	}
//	else if(!onFloor() && !UpinAir && GetAsyncKeyState(VK_UP)) {
//		player.motion.v_y -= JumpAcc;
//		UpinAir = 1;
//	}
//	if (GetAsyncKeyState(VK_DOWN)) {
//		player.poty = _Floor;
//	}
//	if (GetAsyncKeyState(VK_LEFT)) {
//		player.motion.v_x = -X_V;
//	}
//	if (GetAsyncKeyState(VK_RIGHT)) {
//		player.motion.v_x = X_V;
//	}
//}

//DWORD uptime;

void GameControl() {//游戏控制ExMessage方案
	ExMessage msg;
	while (peekmessage(&msg)) {
		/*if (msg.vkcode == VK_UP && onFloor()) { player.motion.v_y -= JumpAcc; }
		if (msg.vkcode == VK_DOWN){ player.poty = _Floor; }
		if (msg.vkcode == VK_LEFT){ player.motion.v_x = -X_V; }
		if (msg.vkcode == VK_RIGHT) { player.motion.v_x = X_V; }
	}*/
		if (msg.message == WM_KEYDOWN)
		{
			if (msg.vkcode == VK_UP && onFloor()){isUp = 1;}
			if (msg.vkcode == VK_UP && !onFloor()&& UpinAir == 0&&player.motion.v_y>-10) {//空中二段跳
				isUp = 1; UpinAir = 1; }
			if (msg.vkcode == VK_DOWN){isDown = 1;}
			if (msg.vkcode == VK_LEFT){isLeft = 1;}
			if (msg.vkcode == VK_RIGHT){isRight = 1;}
		}
		else if (msg.message == WM_KEYUP) {
			//if (msg.vkcode == VK_UP /*&& onFloor()*/){isUp = 0;}
			if (msg.vkcode == VK_DOWN){isDown = 0;}
			if (msg.vkcode == VK_LEFT){isLeft = 0;}
			if (msg.vkcode == VK_RIGHT){isRight = 0;}
		}
		
	}
}

bool direction = 1;
//void CameraMove(int speed=10) {
//	if (player.potx > 1500 || player.potx < 0)direction *= -1;
//	player.potx += speed*direction;
//	for (int i = 0; i < enemyNum+1; i++) {
//		enemy[i].potx -= enemy->motion.v_x;
//		if (enemy[i].potx > 1500 || enemy[0].potx < 0)enemy[i].motion.v_x *= -1;
//	}
//}
//


void Move() {//玩家移动计算
	if (isUp) { player.motion.v_y = -JumpAcc; isUp = 0; }
	if (isDown)player.poty = _Floor;
	if (isLeft)player.motion.v_x = -X_V;
	if (isRight)player.motion.v_x = X_V;

	//竖直方向
	//gravity(1);
	if (onFloor()) {
		player.poty = win_Height - playerH;
	}
	player.motion.v_y += player.motion.a_y;
	player.poty += player.motion.v_y;
	
	if (onFloor() && player.motion.v_y >= 0) {
		player.poty = win_Height - playerH;
		player.motion.v_y = 0;
		//player.motion.a_y = 0;
	}
	
	////水平方向
	//水平速度处理
	if (abs(player.motion.v_x) < X_Af) {
		player.motion.v_x = 0;
	}
	else if (player.motion.v_x > 0) {
		player.motion.v_x -= X_Af;
	}
	else player.motion.v_x += X_Af;
	//水平位置处理
	player.potx += player.motion.v_x;
}

//敌人
void enemyMove() {//向心聚拢
	for (int i = 0; i < enemyNum; i++) {
		if (enemy[i].poty - player.poty == 0) {
			enemy[i].motion.v_x = enemyV;
			enemy[i].motion.v_y = 0;
			
		}
		else if (enemy[i].potx - player.potx == 0) {
			enemy[i].motion.v_x = 0;
			enemy[i].motion.v_y = enemyV;
		}
		else {
			double direction = abs((enemy[i].potx - player.potx) / (enemy[i].poty - player.poty));
			enemy[i].motion.v_y = enemyV / pow((1 + direction * direction), 0.5);
			enemy[i].motion.v_x = enemyV / pow((1 + 1/(direction * direction)), 0.5);
		}
		if (enemy[i].potx - player.potx > 0)enemy[i].motion.v_x *= -1;
		if (enemy[i].poty - player.poty > 0)enemy[i].motion.v_y *= -1;

		enemy[i].potx += enemy[i].motion.v_x;
		enemy[i].poty += enemy[i].motion.v_y;
	}


}

void gunDirection() {
	MOUSEMSG mouseMsg;
	mouseMsg = GetMouseMsg();
	/*int centerX = player.potx + playerW / 2;
	int dX = mouseMsg.x - centerX;
	int dY = mouseMsg.y - player.poty;
	gunD=atan2(dY, dX);
	gun.potx = player.potx;
	gun.poty = player.poty;*/
	
	
}

bool playerDeath() {
	/*for (int i = 0; i < othersNum; i++) {
		if (abs(player.potx - others[i].potx)<100 && abs(player.poty - others[i].poty) < 100)return 1;
	}*/
	return 0;
}

void Print() {
	COLORREF redColor = RGB(255, 0, 0);
	setfillcolor(redColor);
	for (int i = 0; i < enemyNum; i++) {//敌人
		fillrectangle(enemy[0].potx, enemy[0].poty, enemy[0].potx + 100, enemy[0].poty + 100);
	}
	
	setfillcolor(WHITE);//player
	fillrectangle(player.potx, player.poty, player.potx + playerW, player.poty + playerH);
	
	//setfillcolor(YELLOW);//画地面
	//fillrectangle(Floor.a_x,Floor.a_y,Floor.c_x,Floor.c_y);
	
////画枪
	// 将图像旋转一定角度后打印
	//rotateimage(&image.gun_,&image.gun,gunD ); 
	//putimage(gun.potx, gun.poty, &image.gun_); 
}


int main() {
	initgraph(win_Width,win_Height/*,SHOWCONSOLE*/);
	loadimage(&image.gun,_T("images/gun.png"));
	BeginBatchDraw();
	
	DWORD static timep = GetTickCount();
		
	enemyNum = 0;
	enemy[0].potx = 500;
	enemy[0].poty = 500;
	
	while (1) {
		DWORD time = GetTickCount();
		cleardevice();
		/*if (playerDeath()) {
			MessageBox(GetHWnd(), _T("dead"), _T("s"), MB_OK);
			break;
		}*/
		//读取数据
		GameControl();
		gunDirection();
		
		//gravity((time-timep)/_Gravity);
		//timep = GetTickCount();
		//static int GravityCounter = 0;//重力计数器
		//static int GravityTick = 5;
		//if (++GravityCounter % GravityTick == 0)//每 GravityTick 个游戏帧进行一次重力
		//{
		//	GravityCounter = 0;
		//	gravity(1);
		//}
		
		//CameraMove();
		
		//处理数据
		Move();
		enemyMove();
		//绘制画面
		Print();
	
		//游戏帧率控制
		FlushBatchDraw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - time;
		if (delta_time < 1000/_tick ) {
			Sleep(1000 /_tick  - delta_time);
		}
	}
	
	
	EndBatchDraw();

	return 0;
}


