#pragma once
#include "cgamectrl.h"
#include"Back.h"
#include"PacMan.h"
#include"Boom.h"
#include"BackArray.h"
#include"cherry.h"
#include"orange.h"
#include"Bean.h"
#include"RedGhost.h"
#include"YellowGhost.h"
#include"GreenGhost.h"
#include"PinkGhost.h"
#include"cake.h"
#include"berry.h"


#include <process.h>
#include <Windows.h>
class CPacManApp :
	public CGameCtrl
{
public :
	DECLARE()
public :
	CBack  m_map;
	CPacMan m_player;
	Boom m_boom;
	Boom *m_pboom; 
	CBean*m_pbean;
	HDC hdc;
	HDC tempdc;
	int beanNum;
	//int GhostMoveNum;
	bool changefengMain;
	//CGhost *m_redghost;
	CGhost *m_ghost;
	
	CFruit*m_fruit;
	cherry m_cherry;
	BigBean *m_pbigBean;
	int FX;//方向
	bool Win;//判断输赢
	int x;
	int y;
	int eatenBeanNUM;
	int counterBoom;//对炸弹的计数
	int num;
	int ghostFx;

	HBITMAP  bitmap;
	HBITMAP m_fengMian;
	list<CFruit*>m_listFruit;
	list<CBean*>m_listBean;
	list<Boom*>m_listBoom;
	list<CGhost*>m_listGhost;
	list<BigBean*>m_listBigBean;

	
	 bool bflag;
	 int m_nScore;
	 bool m_initFlag;//遍历怪物链表
	 bool canEatGhost;
	 int time;
	 int style;
	 int dieCount;
	 HANDLE m_thread;
	 HANDLE m_threadInit;
	 HANDLE m_threadDie;
	 HANDLE m_threadFruit;
	 bool   m_bFlagQuit;
	 bool   m_bFlagQuitInit;
	 bool   m_bFlagQuitDie;
	 bool   m_bFlagQuitFruit;
	 bool    soundBean;
	 bool    soundDie;
	 HANDLE  m_hSemphore;
	 HANDLE  m_hSemphoreInit;
	 HANDLE  m_hSemphoreDie;
	  HANDLE  m_hSemphoreFruit;
	 long maxSemNum;
	 bool initSnd;
	 //AI*aStar;
public:
	CPacManApp (void);
	~CPacManApp (void);
	virtual void OnCreateGame() ;
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimerID);
	virtual void OnKeyDown(WPARAM nKey);
	virtual void OnLButtonDown(POINT point);
public :
	//fruit:
	void CreateFruit(HINSTANCE hinstance);
	void creatOrange();
    void creatCherry();
	void creatCake();
	void creatBerry();
	void eatFruit();

	void showFruit();
	//beans:
	void AllBeanShow(CBackArray &arr);//显示all beans 
	void createBean(CBackArray &arr);
	void  eatBean();
	//bigbean:
	void createBigBean();
	void createBean1();
	void createBean2();
	void createBean3();
	void createBean4();
	void eatBigBean();
	void showBigBean();
	//pacman:
	void changPacManId();
	bool isDying();
	void changPacShow();
	void changDieGhostId();
	void meetGhost();
	void isBeanNull();
	
    // ghost:
	void changGhostId();
	void GhostShow(HDC hdc);


	void createGhost();
	void createRedGhost();
	void createYellowGhost();
	void createGreenGhost();
	void createPinkGhost();
	 
	void OperGhostMove();
	void GhostMove();


	void searchRed();
	void searchYellow();
	void searchGreen();
	void searchPink();
	void comeHome();//让幽灵们回家


    void levelChoose();
	//boom
	void creatBoom();
	void deleteBoom();
	void allBoomShow(HDC hdc);

	void loadfengMian();
	void fengMianShow(HDC hdc);
	void GamePicture();
	void ShowPacmanScore(HDC hdc);

	void jishu();
	void changstyle();

	void increaseTime();
	void bfs(CBackArray &arr,int x,int y,int lastx,int lasty);
	void initGameSnd();

	static unsigned _stdcall ThreadProc( void * lpvoid );//一定要是静态的啊！//bigBean
	static unsigned _stdcall ThreadProcInit( void * lpvoid );//fruit
	static unsigned _stdcall ThreadProcDie( void * lpvoid );
	static unsigned _stdcall ThreadProcFruit( void * lpvoid );
	void destroyThread();
	void killTimerAll();
	void startTimer();
};


