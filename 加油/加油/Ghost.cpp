#include "Ghost.h"
#include"PacManApp.h"
CGhost::CGhost(void)
{
	 GhostMoveId=3;
	 changShow=false;

	 int s[4][2]={0,1, 0,-1,1,0, -1,0};
	 vis[24][21]=0;
	 for(int i=0;i<4;i++)
	 {
		 for(int j=0;j<2;j++)
		 {
			 c[i][j]=s[i][j];
		 }
	 }
	
	int aa[24][21]={0};
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<21;j++)
		{
			a[i][j]=aa[i][j];
			vis[i][j]=aa[i][j];
		}
	}
	Point anstemp[45]={0};
	Point pretemp[24][21]={0};
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<21;j++)
		{
			pre[i][j]=pretemp[i][j];
		}
	}
}
CGhost::CGhost(CPacManApp*pApp)
{
	m_pacHwnd=pApp;

	GhostMoveId=3;
	changShow=false;

	 int s[4][2]={0,1, 0,-1,1,0, -1,0};
	 vis[24][21]=0;
	 for(int i=0;i<4;i++)
	 {
		 for(int j=0;j<2;j++)
		 {
			 c[i][j]=s[i][j];
		 }
	 }
	
	int aa[24][21]={0};
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<21;j++)
		{
			a[i][j]=aa[i][j];
			vis[i][j]=aa[i][j];
		}
	}
	Point anstemp[45]={0};
	Point pretemp[24][21]={0};
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<21;j++)
		{
			pre[i][j]=pretemp[i][j];
		}
	}
}
CGhost::~CGhost(void)
{
	DeleteObject(m_ghost);
	m_ghost=NULL;
	DeleteObject(m_Wghost);
	m_Wghost=NULL;
	DeleteObject(m_ghost1);
	m_ghost1=NULL;
	DeleteObject(m_Wghost1);
	m_Wghost1=NULL;
}
void CGhost::GhostInit(HINSTANCE hiatance)
{
	m_ghost=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_GHOST));
	m_Wghost=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_W_GHOST));
	m_ghost1=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_GHOST2));
	m_Wghost1=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_WGHOST1));
}
void CGhost::GhostMove(int x,int y )
{
	this->x=y*30;//¶ÔÓ¦
	this->y=x*30;
}

bool CGhost::meetPacMan(CPacMan *p_pacman)
{
	if(p_pacman->x==this->x&&p_pacman->y==this->y)
	{
		return true;
	}
	return false;
}