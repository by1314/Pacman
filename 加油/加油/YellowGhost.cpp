#include "YellowGhost.h"
#include"PacManApp.h"
YellowGhost::YellowGhost(void)
{
	x=330;
	y=330;
	move=false;
	aaaa=1;
	initX=330;
	initY=330;
}
YellowGhost::~YellowGhost(void)
{

}

void YellowGhost::GhostInit(HINSTANCE hiatance)
{

}
void YellowGhost::GhostMove(int x,int y)
{
	this->x=y*30;//对应
	this->y=x*30;
}
void YellowGhost::GhostShow(HDC hdc )
{

	if(changShow==true)
	{
		HDC tempdc=CreateCompatibleDC(hdc);
		SelectObject(tempdc,m_Wghost1);
		BitBlt(hdc,x,y,30,30,tempdc,270,0,SRCAND);
		SelectObject(tempdc,m_ghost1);
		BitBlt(hdc,x,y,30,30,tempdc,270,0,SRCPAINT);
		DeleteDC(tempdc);
	}
	if(changShow==false)
	{
		HDC tempdc=CreateCompatibleDC(hdc);
		SelectObject(tempdc,m_Wghost);
		BitBlt(hdc,x,y,30,30,tempdc,240,0,SRCAND);
		SelectObject(tempdc,m_ghost);
		BitBlt(hdc,x,y,30,30,tempdc,240,0,SRCPAINT);
		DeleteDC(tempdc);
		}
}
void  YellowGhost::bfs(CBackArray &arr,int x,int y,int lastx,int lasty)
{
	memset(ans,0,45*8);
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<21;j++)
		{
			a[i][j]=arr.arr[i][j];
		}
	}
	while(!que.empty())
	{
		que.pop();
	}
        tmp.x=y/30;
        tmp.y=x/30;//一定是30 的倍数
	   //目标要与前进方向有关
		int tempLastx;
		int tempLasty;

		if((lasty+180<720)&&(lastx+180<630)&&(m_Back.arr[(lasty+180)/30][(lastx+180)/30]==1||m_Back.arr[(lasty+180)/30][(lastx+180)/30]==5
			||m_Back.arr[(lasty+180)/30][(lastx+180)/30]==2||m_Back.arr[(lasty+180)/30][(lastx+180)/30]==4||m_Back.arr[(lasty+180)/30][(lastx+180)/30]==3))
		{//+60是因为一定大于
          tempLastx=lastx+180;
		  tempLasty=lasty+180;
		}
		else
		{
			tempLastx=lastx;
		    tempLasty=lasty;
		}
		 
		int lastxx;
			lastxx=(tempLasty/30);
		int lastyy;
			lastyy=(tempLastx/30);

        que.push(tmp);

		::memset(vis,0,24*21*4);
		::memset(pre,0,24*21*8);
        vis[tmp.x][tmp.y]=1;//走过的就标记为不可以走
        while(!que.empty())
	   {
            tmp=que.front();
            que.pop();   
            for(int i=0;i<4;i++)
			{       
                tmp2.x=tmp.x+c[i][0];
                tmp2.y=tmp.y+c[i][1];
                if(tmp2.x>=0 && tmp2.x<= 23&& tmp2.y>=0 && tmp2.y<=21 && !vis[tmp2.x][tmp2.y] &&( (a[tmp2.x][tmp2.y]==1)||a[tmp2.x][tmp2.y]==4||a[tmp2.x][tmp2.y]==2||a[tmp2.x][tmp2.y]==5||a[tmp2.x][tmp2.y]==3))
				{
                    vis[tmp2.x][tmp2.y]=vis[tmp.x][tmp.y]+1;
                    que.push(tmp2);// 入
                    pre[tmp2.x][tmp2.y].x=tmp.x;//tmp2的上一个节点是tmp
                    pre[tmp2.x][tmp2.y].y=tmp.y;
                }
            }
            if(!vis[lastxx][lastyy])//找到终点返回
			{
                //break;
				//bfs(m_map.m_backArray,tmp2.y*30,tmp2.x*30,m_player.x,m_player.y);
				//ghostFx=5;//pacman is eaten        
            }   
        }
		 int ghostNum=0;
		  int tempx,tempy;
          while(lastxx||lastyy)
		{ 
            ans[ghostNum].x=lastxx;
			ans[ghostNum++].y=lastyy;
            tempx=lastxx;
            tempy=lastyy;
            lastxx=pre[tempx][tempy].x;
            lastyy=pre[tempx][tempy].y;
        }
		  GhostMoveNum=ghostNum;
}
void YellowGhost::OperGhostMove()
{
	   this->GhostMove(ans[GhostMoveNum-1-aaaa].x,ans[GhostMoveNum-1-aaaa].y);
		
        if((GhostMoveNum-1-aaaa) == 0)//如果走到
		{	
		  aaaa = 1;
		}
		else
			aaaa++;	
}
void YellowGhost::startMove(CPacManApp *papp)
{
	if(papp->m_nScore>=150)
	{
		move=true;
	}
}
void YellowGhost::comeHome()
{
	this->x=initX;
	this->y=initY;
}