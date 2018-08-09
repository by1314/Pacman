#include "berry.h"


berry::berry(void)
{

}


berry::~berry(void)
{
}
void berry::FruitInit(HINSTANCE hiatance)
{

}
void berry::FruitShow(HDC hdc)
{
	HDC tempdc=CreateCompatibleDC(hdc);
	SelectObject(tempdc,m_wfruit);
	BitBlt(hdc,x,y,30,30,tempdc,60,0,SRCAND);
	SelectObject(tempdc,m_bfruit);
	BitBlt(hdc,x,y,30,30,tempdc,60,0,SRCPAINT);
	DeleteDC(tempdc);
}
