#include "Bean.h"
#include"BackArray.h"
CBean::CBean(void)
{
	m_bean=0;
	m_wbean=0;
	x=0;
	y=0;
}
CBean::~CBean(void)
{
	DeleteObject(m_bean);
	m_bean=NULL;
	DeleteObject(m_wbean);
	m_wbean=NULL;
}
void CBean::BeanInit(HINSTANCE hiatance,CBackArray &arr)
{
	m_bean=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_BEAN));
	m_wbean=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_W_BEAN));
	for(int i=0;i<24;i++)
	{
		int flag;
		for(int j=0;j<21;j++)
		{
			flag = 0;
			if(arr.arr[i][j]==1)
			{
				flag =1;
				this->x=j*30;
				this->y=i*30;																					
				arr.arr[i][j]=2;
			}
			if (flag == 1) break;
		}
		if (flag == 1) break;
	}
}
void CBean::BeanShow(HDC hdc)
{
		    HDC tempdc=CreateCompatibleDC(hdc);
			SelectObject(tempdc,m_wbean);
			BitBlt(hdc,x,y,30,30,tempdc,0,0,SRCAND);
			SelectObject(tempdc,m_bean);
			BitBlt(hdc,x,y,30,30,tempdc,0,0,SRCPAINT);
			DeleteDC(tempdc);
}
