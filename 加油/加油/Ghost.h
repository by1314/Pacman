#pragma once
#include"system.h"
#include"BackArray.h"	
#include"PacMan.h"
class CPacManApp;//解决相互包含的办法
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

    bool move;//因为怪物不是同时出现的
	int x;
	int y;
	int GhostMoveId;
	int flag;
	bool changShow;
	int GhostMoveNum;
	int aaaa ;
	int initX;//用于记录 
	int initY;
	
	 queue<Point >que;
	 Point pre[24][21];
     int vis[24][21];
     int c[4][2];
     int a[24][21];
     Point ans[45];         //用于记录回溯路径
	 Point s,t;             //vector<Point>ans;// 相比于数组来说它是动态的，不固定大小
	 
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

