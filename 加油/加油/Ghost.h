#pragma once
#include"system.h"
#include"BackArray.h"	
#include"PacMan.h"
class CPacManApp;//����໥�����İ취
class CGhost
{
public :
	struct Point
{
	int x;
	int y;
}tmp,tmp2;
	
public :
	HBITMAP m_ghost;
	HBITMAP m_Wghost;
	HBITMAP m_ghost1;
	HBITMAP m_Wghost1;
	CPacMan m_pacman;
	CBackArray m_Back;

	CPacManApp *m_pacHwnd;

    bool move;//��Ϊ���ﲻ��ͬʱ���ֵ�
	int x;
	int y;
	int GhostMoveId;
	int flag;
	bool changShow;
	int GhostMoveNum;
	int aaaa ;
	int initX;//���ڼ�¼ 
	int initY;
	
	 queue<Point >que;
	 Point pre[24][21];
     int vis[24][21];
     int c[4][2];
     int a[24][21];
     Point ans[45];         //���ڼ�¼����·��
	 Point s,t;             //vector<Point>ans;// �����������˵���Ƕ�̬�ģ����̶���С
	 
public:
	CGhost(void);
	CGhost(CPacManApp*pApp);
	virtual ~CGhost(void);
	void GhostInit(HINSTANCE hiatance);
    void GhostMove(int x,int y);
	virtual void GhostShow(HDC hdc )=0;
	virtual void bfs(CBackArray &arr,int x,int y,int lastx,int lasty)=0;
	virtual void OperGhostMove()=0;
	bool meetPacMan(CPacMan *p_pacman);
	virtual void startMove(CPacManApp *papp)=0;
	virtual void comeHome()=0;
};

