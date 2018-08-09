#include "BigBean.h"


BigBean::BigBean(void)
{
	m_bigBean=NULL;
	m_w_bigBean=NULL;
	x=0;
	y=0;
}


BigBean::~BigBean(void)
{
	DeleteObject(m_bigBean);
	m_bigBean=NULL;
	DeleteObject(m_w_bigBean);
	m_w_bigBean=NULL;
}
void BigBean::bigBeanInit(HINSTANCE hinstance,int x,int y)
{
	this->x=x;
	this->y=y;
	m_bigBean=::LoadBitmap(hinstance,MAKEINTRESOURCE(IDB_BIGBEAN));
	m_w_bigBean=::LoadBitmap(hinstance,MAKEINTRESOURCE(IDB_WBIGBEAN));
}
void BigBean::bigBeanShow(HDC hdc)
{
		    HDC tempdc=CreateCompatibleDC(hdc);
			SelectObject(tempdc,m_w_bigBean);
			BitBlt(hdc,x,y,30,30,tempdc,0,0,SRCAND);
			SelectObject(tempdc,m_bigBean);
			BitBlt(hdc,x,y,30,30,tempdc,0,0,SRCPAINT);
			DeleteDC(tempdc);
}
