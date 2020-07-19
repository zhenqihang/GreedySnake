#include <iostream>
#include <windows.h> 
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define HIGH 20                     //��ͼ�߶� 
#define WIDTH 30                    //��ͼ�Ŀ��
#define SNAKE_MAX 200               //�ߵ���󳤶�
int SNAKE_X[SNAKE_MAX],SNAKE_Y[SNAKE_MAX];  //�ߵ�����
int SNAKE_LEN;                         //�ߵĳ���
int MAP[HIGH][WIDTH]={};            //��ʼ����ͼ
int FOOD_X,FOOD_Y;                  //ʳ�������
int SCORE;                          //���ֵ÷�
char input;                         //������� 
char primeinput=' ';                //�����洢input 

void SetData();                     //���ݳ�ʼ�� 
void Gotoxy(int,int);               //���������´�ӡ 
void NUM(int );                     //switch(num)
void Show();                        //��ӡ���� 
void UpdateWithoutInput();
void UpdateWithInput();



void SetData()
{
	SNAKE_X[0] = HIGH/2;SNAKE_Y[0] = WIDTH/3;  //��ʼ����ͷ 
	SNAKE_X[1] = HIGH/2;SNAKE_Y[1] = WIDTH/3+1; //��ʼ������ 
	SNAKE_LEN = 2;
	FOOD_X = HIGH/3,FOOD_Y = WIDTH/3;//��ʼ��ʳ��
	SCORE=0;
	//0����ո�1��������2����ʳ�3����ǽ��4������ͷ 
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
	std::cout<<"w���ϣ�a����s���£�d���ң�p��ͣ���ո����~"<<std::endl;
	for(int i=0;i<HIGH;i++){ 
		for(int j=0;j<WIDTH;j++)
			NUM(MAP[i][j]);
		std::cout<<std::endl;	
	}
	std::cout<<"�÷֣�"<<SCORE;	
}

void NUM(int num)
{
	switch(num)
	{
		case 0:std::cout<<" ";break;//�ո� 
		case 1:std::cout<<"+";break;//���� 
		case 2:std::cout<<"*";break;//ʳ�� 
		case 3:std::cout<<"~";break;//ǽ 
		case 4:std::cout<<"@";break;//��ͷ 
	}
}

void UpdateWithoutInput()
{
	Sleep(500);    //�ȴ�0.5s 
	if(SNAKE_X[0]==FOOD_X && SNAKE_Y[0]==FOOD_Y)
	{
		SCORE++;
		srand((unsigned)time(nullptr));  //���������
		FOOD_X=rand()%(HIGH-3)+1;
		FOOD_Y=rand()%(WIDTH-3)+1;
		MAP[FOOD_X][FOOD_Y]=2;
		SNAKE_LEN++; 
	}
	if(SNAKE_X[0]==0||SNAKE_X[0]==HIGH-1||SNAKE_Y[0]==0||SNAKE_Y[0]==WIDTH-1)
	{
		std::cout<<"��Ϸ������"<<std::endl;
		getch();
		exit(1);
	}	
	for(int i=1;i<SNAKE_LEN;i++){
		if(SNAKE_X[0]==SNAKE_X[i] && SNAKE_Y[0]==SNAKE_Y[i])
		{
			std::cout<<"��Ϸ������"<<std::endl;
			getch();
			exit(1); 
		}
	}
}

void UpdateWithInput()
{
	if(kbhit())     //kbhit()�����ж��Ƿ������룻�У���return 1 
		input=getch();
	if(input!='\0')	{   //���������ʱ��䶯ͼ�� 
		if(input=='w'||input=='a'||input=='s'||input=='d')
			primeinput=input;
		else if(primeinput==' ')
			primeinput='w';	 //��ʾ��Ϸ��ʼ 
		else if(input=='p')
		{
			while(1) {
				char tmp;
				tmp = getch();
				if(tmp=='p')
				{input=' ';break;}
			}
		}	
			//ÿǰ��һ����β��Ϊ�ո� 
			MAP[SNAKE_X[SNAKE_LEN-1]][SNAKE_Y[SNAKE_LEN-1]]=0;
			for(int i=SNAKE_LEN-1;i>0;i--)
			{
				SNAKE_X[i]=SNAKE_X[i-1];
				SNAKE_Y[i]=SNAKE_Y[i-1];
				MAP[SNAKE_X[i]][SNAKE_Y[i]]=1;
			} 	
	}
	switch(input)
	{//�����Ͻ�Ϊ����ԭ��,
		case 'w':SNAKE_X[0]--;break;
		case 's':SNAKE_X[0]++;break;
		case 'a':SNAKE_Y[0]--;break; 
		case 'd':SNAKE_Y[0]++;break;
	}
	MAP[SNAKE_X[0]][SNAKE_Y[0]]=4;
}

