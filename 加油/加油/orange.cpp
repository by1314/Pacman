#include "orange.h"
orange::orange(void)
{
}
orange::~orange(void)
{
}
void orange::FruitShow(HDC hdc)
{
	HDC tempdc=CreateCompatibleDC(hdc);
	SelectObject(tempdc,m_wfruit);
	BitBlt(hdc,x,y,30,30,tempdc,30,0,SRCAND);
	SelectObject(tempdc,m_bfruit);
	BitBlt(hdc,x,y,30,30,tempdc,30,0,SRCPAINT);
	DeleteDC(tempdc);
}
void orange::FruitInit(HINSTANCE hiatance)
{

}