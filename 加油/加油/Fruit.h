#pragma once
#include"system.h"
class CFruit
{
public :
	HBITMAP m_bfruit;
	HBITMAP m_wfruit;
	int x;
	int y;
	bool eatflag;
public:
	CFruit(void);
	virtual~CFruit(void);
public :
	void FruitInit(HINSTANCE hiatance,int x,int y);
	virtual void FruitShow(HDC hdc)=0;
};

