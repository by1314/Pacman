#include "cake.h"


cake::cake(void)
{
}


cake::~cake(void)
{
}
void cake::FruitInit(HINSTANCE hiatance)
{

}
void cake::FruitShow(HDC hdc)
{
	HDC tempdc=CreateCompatibleDC(hdc);
	SelectObject(tempdc,m_wfruit);
	BitBlt(hdc,x,y,30,30,tempdc,270,0,SRCAND);
	SelectObject(tempdc,m_bfruit);
	BitBlt(hdc,x,y,30,30,tempdc,270,0,SRCPAINT);
	DeleteDC(tempdc);
}

