#include "Back.h"


CBack::CBack(void )
{
	m_back=0;
    x=0;
	y=0;
	//m_pbackArray=array;
}
CBack::~CBack(void)
{
	DeleteObject(m_back);
	m_back=0;
	//delete m_pbackArray;
	//m_pbackArray=0;
}
void CBack::BackInit(HINSTANCE hinstance)
{
	m_back=::LoadBitmap(hinstance,MAKEINTRESOURCE(IDB_BACK));
	m_logo=::LoadBitmap(hinstance,MAKEINTRESOURCE(IDB_LOGO));

}
void CBack::BackShow(HDC hdc)
{
	HDC tempdc=CreateCompatibleDC(hdc);
	SelectObject(tempdc,m_back);
	
	BitBlt(hdc,x,y,630,720,tempdc,0,0,SRCCOPY);
	SelectObject(tempdc,m_logo);
	BitBlt(hdc,240,0,160,55,tempdc,0,0,SRCCOPY);
	DeleteDC(tempdc);
}
void CBack::BackArr(CBackArray&array)
{
	  m_backArray=array;
}
