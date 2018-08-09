#include "Fruit.h"


CFruit::CFruit(void)
{
	x=0;
	y=0;
	eatflag=false;
}
CFruit::~CFruit(void)
{
	DeleteObject(m_bfruit);
	m_bfruit=NULL;
	DeleteObject(m_wfruit);
	m_wfruit=NULL;
}
void CFruit::FruitInit(HINSTANCE hiatance,int x,int y)
{
	this->x=x;
	this->y=y;
	m_wfruit=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_W_FRUIT));
	m_bfruit=::LoadBitmap(hiatance,MAKEINTRESOURCE(IDB_FRUIT));
}
void CFruit::FruitShow(HDC hdc)
{

}