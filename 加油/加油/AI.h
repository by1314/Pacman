//#pragma once
//#include"system.h"
//#include"BackArray.h"
//typedef struct NODE
//{
//	int x;
//	int y;
//	int f;
//	int g;
//	int h;
//	int bflag;//�Ƿ�����  1 ������
//	struct NODE*parent;
//}Node;
//class AI{
//public :
//	AI();
//	~AI();
//public :
//	void setStartNode(int x,int y);
//	void setEndNode(int x,int y);
//    void search();
//	bool isInOpen(Node*node);
//	bool isInClose(Node*node);
//	bool isBlocked(Node*node);
//	void calH(Node*node);
//	void calF(Node*node);
//	void calG(Node*node);
//	bool isPath();
//	Node*getBestNode();
//	void checkNode(Node*findNode,int x,int y);
//    bool isendNode(Node *node);
//	void InitMap(CBackArray &arr);//row
//public :
//	Node*m_pstartNode;//��ʼ�ڵ�
//	Node*m_pendNode;//�����ڵ�
//	Node*isEndNode;//��ǰ�ڵ�
//	static const int m_cost=10;
//	int row;
//	int col;
//	int sz[24][21];
//	list<Node*>m_openList;
//    list<Node*>m_closeList; 
//};
