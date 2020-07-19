#include "GreedySnake.h"

int main()
{
	SetData();                      //数据初始化
	while(1)
	{
		Show();                     //画面打印
		UpdateWithoutInput();       //蛇吃到食物或撞墙update
		UpdateWithInput();          //蛇的转向update 
	} 
	std::cin.get();
	return 0;
}


