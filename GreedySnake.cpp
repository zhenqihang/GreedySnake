#include "GreedySnake.h"

int main()
{
	SetData();                      //���ݳ�ʼ��
	while(1)
	{
		Show();                     //�����ӡ
		UpdateWithoutInput();       //�߳Ե�ʳ���ײǽupdate
		UpdateWithInput();          //�ߵ�ת��update 
	} 
	std::cin.get();
	return 0;
}


