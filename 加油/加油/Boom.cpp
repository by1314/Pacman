#include "Boom.h"
Boom::Boom(void)
{
	m_bboom=0;
	m_wboom=0;
	x=458;
	y=680;
	counter=3;
}
Boom::~Boom(void)
{
	DeleteObject(m_bboom);
	DeleteObject(m_wboom);
	m_bboom=0;
	m_wboom=0;
}
void Boom::BoomInit(HINSTANCE hinstance,int x)
{
	this->x=x;
	m_wboom=::LoadBitmap(hinstance,MAKEINTRESOURCE(IDB_BOOM));
	m_bboom=::LoadBitmap(hinstance,MAKEINTRESOURCE(IDB_BBOOM));
	
}
void Boom::BoomDes()
{
	if(counter>0)
	{
	   counter--;
	}
}
void Boom::BoomShow(HDC hdc)
{
	  HDC tempdc=CreateCompatibleDC(hdc);
	  SelectObject(tempdc,m_wboom);//ÏÈ°×ºóºÚ
	  BitBlt(hdc,x,y,43,43,tempdc,0,0,SRCAND);
	  SelectObject(tempdc,m_bboom);
	  BitBlt(hdc,x,y,43,43,tempdc,0,0,SRCPAINT);

	DeleteDC(tempdc);

}