#include <iostream>
#include <windows.h> 
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define HIGH 20                     //地图高度 
#define WIDTH 30                    //地图的宽度
#define SNAKE_MAX 200               //蛇的最大长度
int SNAKE_X[SNAKE_MAX],SNAKE_Y[SNAKE_MAX];  //蛇的坐标
int SNAKE_LEN;                         //蛇的长度
int MAP[HIGH][WIDTH]={};            //初始化地图
int FOOD_X,FOOD_Y;                  //食物的坐标
int SCORE;                          //本局得分
char input;                         //读入符号 
char primeinput=' ';                //用来存储input 

void SetData();                     //数据初始化 
void Gotoxy(int,int);               //清屏并重新打印 
void NUM(int );                     //switch(num)
void Show();                        //打印画面 
void UpdateWithoutInput();
void UpdateWithInput();



void SetData()
{
	SNAKE_X[0] = HIGH/2;SNAKE_Y[0] = WIDTH/3;  //初始化蛇头 
	SNAKE_X[1] = HIGH/2;SNAKE_Y[1] = WIDTH/3+1; //初始化蛇身 
	SNAKE_LEN = 2;
	FOOD_X = HIGH/3,FOOD_Y = WIDTH/3;//初始化食物
	SCORE=0;
	//0代表空格，1代表蛇身，2代表食物，3代表墙，4代表蛇头 
	MAP[SNAKE_X[0]][SNAKE_Y[0]]=4; 
	MAP[SNAKE_X[1]][SNAKE_Y[1]]=1;
	MAP[FOOD_X][FOOD_Y]=2;
	for(int i=0;i<HIGH;i++){
		for(int j=0;j<WIDTH;j++){
			if(i==0||j==0||i==HIGH-1||j==WIDTH-1)
				MAP[i][j]=3;
		}
	} 
}

void Gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
} 

void Show()
{
	Gotoxy(0,0);
	std::cout<<"w向上，a向左，s向下，d向右，p暂停，空格结束~"<<std::endl;
	for(int i=0;i<HIGH;i++){ 
		for(int j=0;j<WIDTH;j++)
			NUM(MAP[i][j]);
		std::cout<<std::endl;	
	}
	std::cout<<"得分："<<SCORE;	
}

void NUM(int num)
{
	switch(num)
	{
		case 0:std::cout<<" ";break;//空格 
		case 1:std::cout<<"+";break;//蛇身 
		case 2:std::cout<<"*";break;//食物 
		case 3:std::cout<<"~";break;//墙 
		case 4:std::cout<<"@";break;//蛇头 
	}
}

void UpdateWithoutInput()
{
	Sleep(500);    //等待0.5s 
	if(SNAKE_X[0]==FOOD_X && SNAKE_Y[0]==FOOD_Y)
	{
		SCORE++;
		srand((unsigned)time(nullptr));  //产生随机数
		FOOD_X=rand()%(HIGH-3)+1;
		FOOD_Y=rand()%(WIDTH-3)+1;
		MAP[FOOD_X][FOOD_Y]=2;
		SNAKE_LEN++; 
	}
	if(SNAKE_X[0]==0||SNAKE_X[0]==HIGH-1||SNAKE_Y[0]==0||SNAKE_Y[0]==WIDTH-1)
	{
		std::cout<<"游戏结束！"<<std::endl;
		getch();
		exit(1);
	}	
	for(int i=1;i<SNAKE_LEN;i++){
		if(SNAKE_X[0]==SNAKE_X[i] && SNAKE_Y[0]==SNAKE_Y[i])
		{
			std::cout<<"游戏结束！"<<std::endl;
			getch();
			exit(1); 
		}
	}
}

void UpdateWithInput()
{
	if(kbhit())     //kbhit()用来判读是否有输入；有，则return 1 
		input=getch();
	if(input!='\0')	{   //当有输入的时候变动图像 
		if(input=='w'||input=='a'||input=='s'||input=='d')
			primeinput=input;
		else if(primeinput==' ')
			primeinput='w';	 //表示游戏开始 
		else if(input=='p')
		{
			while(1) {
				char tmp;
				tmp = getch();
				if(tmp=='p')
				{input=' ';break;}
			}
		}	
			//每前进一格，蛇尾变为空格 
			MAP[SNAKE_X[SNAKE_LEN-1]][SNAKE_Y[SNAKE_LEN-1]]=0;
			for(int i=SNAKE_LEN-1;i>0;i--)
			{
				SNAKE_X[i]=SNAKE_X[i-1];
				SNAKE_Y[i]=SNAKE_Y[i-1];
				MAP[SNAKE_X[i]][SNAKE_Y[i]]=1;
			} 	
	}
	switch(input)
	{//已左上角为坐标原点,
		case 'w':SNAKE_X[0]--;break;
		case 's':SNAKE_X[0]++;break;
		case 'a':SNAKE_Y[0]--;break; 
		case 'd':SNAKE_Y[0]++;break;
	}
	MAP[SNAKE_X[0]][SNAKE_Y[0]]=4;
}

