#pragma once
#include"system.h"
typedef struct Node
{
		int x;
		int y;
}node;
class CBackArray
{
public:
	int arr[24][21];//���������ֵ
	node m_node;//��ȡ����λ��
	int row;
	int col;
public:
	CBackArray(void);
	~CBackArray(void);
public :
	void BackArrayInit();
	void BackArrayUpDate();
	int  GetNode(int i);
};

