#include "cherry.h"

//Î÷¹Ï
cherry::cherry(void)
{

}
cherry::~cherry(void)
{
}
void cherry::FruitInit(HINSTANCE hiatance)
{

}
void cherry::FruitShow(HDC hdc)
{
	HDC tempdc=CreateCompatibleDC(hdc);
	SelectObject(tempdc,m_wfruit);
	BitBlt(hdc,x,y,30,30,tempdc,120,0,SRCAND);
	SelectObject(tempdc,m_bfruit);
	BitBlt(hdc,x,y,30,30,tempdc,120,0,SRCPAINT);
	DeleteDC(tempdc);
}