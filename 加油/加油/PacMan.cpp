#include "PacMan.h"
#include"PacManApp.h"//不允许使用不完整的类型是英文没有头文件
CPacMan::CPacMan(void)
{
	m_pacMan=0;
	m_wpacMan=0;
	pacMoveId=3;
	m_blood=3;
	x=330;
	y=390;
	dx=0;
	dy=0;
	bflag=false;
	iseat=false;//没有被吃
	changShow=false;
	isDied=false;
}
CPacMan::CPacMan(CPacManApp *pCPacManApp)
{
	m_CPacManApp=pCPacManApp;
	m_pacMan=0;
	m_wpacMan=0;
	pacMoveId=3;
	m_blood=3;
	x=330;
	y=390;
	dx=0;
	dy=0;
	bflag=false;
	iseat=false;
	changShow=false;
	isDied=false;
}
CPacMan::~CPacMan(void)
{
	DeleteObject(m_pacMan);
	DeleteObject(m_wpacMan);
	m_wpacMan=0;
	m_pacMan=0;
}
void CPacMan::PacManInit(HINSTANCE histance)
{
	m_pacMan=::LoadBitmap(histance,MAKEINTRESOURCE(IDB_PACMAN));
	m_wpacMan=::LoadBitmap(histance,MAKEINTRESOURCE(IDB_Wpacman));
	m_pacMan1=::LoadBitmap(histance,MAKEINTRESOURCE(IDB_GHOST2));
	m_wpacMan1=::LoadBitmap(histance,MAKEINTRESOURCE(IDB_WGHOST1));
	m_diePacman=::LoadBitmap(histance,MAKEINTRESOURCE(IDB_DIE_PACMAN));
}
void  CPacMan::Move(CBackArray&sz)
{
	switch(g_fx)//dx和arr对应
	{
	case 0:
		dx=-1;
		dy=0;
		break;
	case 1:
		dx=1;
		dy=0;
		break;
	case 2:
		dx=0;
		dy=-1;
		break;
	case 3:
		dx=0;
		dy=1;//temp--
		break;
	}
	int tempj=(this->x/30)+dy;//注意！数组的x,y和位图的x,y相反
	int tempi=(this->y/30)+dx;	
	if(sz.arr[ tempi][tempj]==1||sz.arr[ tempi][tempj]==4||sz.arr[ tempi][tempj]==2||sz.arr[ tempi][tempj]==5||sz.arr[ tempi][tempj]==9)
	{
	    bflag= true;//是否可以通过
	}
	else 
	{
		bflag= false ;
	}
}
void CPacMan::PacManMove(CBackArray&sz)
{       
	if(bflag)
	{
		switch(g_fx)
		{
		case 0:
			if(y>0)
			{
				y-=30;
			}
			break;
		case 1:
			if(y<690)
			{
				y+=30;
			}
			break;
		case 2:
			if(x>0&&x!=0)
			{
				x-=30;
			}
			else if(x==0)
			{
				x=570;
			}
			break;
		case 3:
			if(x<600)
			{
				x+=30;
			}
			break;
			
		}
	}
	else
	{
		return ;
	}
}
bool CPacMan::isDying()
{
	return false;
}
void CPacMan::DecBlood()///wei  生命为0 时要在外部控制游戏结束
{
	if(isDying())
	{
		m_blood--;
	}
}
void CPacMan::PacManShow(HDC hdc)
{
	if(changShow==false)
	{
	 HDC tempdc=CreateCompatibleDC(hdc);
	 switch(g_fx)
	 {
	 case 0://up
		SelectObject(tempdc,m_wpacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,90,SRCAND);
		SelectObject(tempdc,m_pacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,90,SRCPAINT);
		break;
	 case 1://down
		SelectObject(tempdc,m_wpacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,30,SRCAND);
		SelectObject(tempdc,m_pacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,30,SRCPAINT);
		break;
	 case 2://left
		SelectObject(tempdc,m_wpacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,60,SRCAND);
		SelectObject(tempdc,m_pacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,60,SRCPAINT);
		break;
	 case 3://right
		SelectObject(tempdc,m_wpacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,0,SRCAND);
		SelectObject(tempdc,m_pacMan);
		BitBlt(hdc,x,y,30,30,tempdc,(4-pacMoveId)*30,0,SRCPAINT);
		break;
	 default:
		SelectObject(tempdc,m_wpacMan);
		BitBlt(hdc,x,y,30,30,tempdc,0,0,SRCAND);
		SelectObject(tempdc,m_pacMan);
		BitBlt(hdc,x,y,30,30,tempdc,0,0,SRCPAINT);
		break;
	   }DeleteDC(tempdc);
	}
	if(changShow==true)
	{
		HDC tempdc=CreateCompatibleDC(hdc);
		SelectObject(tempdc,m_wpacMan1);
		BitBlt(hdc,x,y,30,30,tempdc,270,0,SRCAND);
		SelectObject(tempdc,m_pacMan1);
		BitBlt(hdc,x,y,30,30,tempdc,270,0,SRCPAINT);
		DeleteDC(tempdc);
	}
}
void  CPacMan::PacManShowDying(HDC hdc)
{
	if(isDied==true)
	{

	}
	//置回false且不可以移动
}
bool  CPacMan::eatBean(CBean *bean)
{
	if((bean->x==this->x)&&(bean->y==this->y))
	{
		return true;
	}
	return false;
}
bool CPacMan::eatBigBean(BigBean *bigBean)
{
	if((bigBean->x==this->x)&&(bigBean->y==this->y))
	{
		return true;
	}
	return false;
}
bool CPacMan::eatFruit(CFruit *fruit)
{
	if((fruit->x==this->x)&&(fruit->y==this->y))
	{
		//fruit->eatflag=true;//吃到了水果
		return true;
	}
	return false;
}
