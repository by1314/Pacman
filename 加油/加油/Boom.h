#pragma once
#include"system.h"
class Boom
{
public :
	int counter;
	int x;
	int y;
	HBITMAP m_bboom;
	HBITMAP m_wboom;
public:
	Boom(void);
	~Boom(void);
public:
	void BoomInit(HINSTANCE hinstance,int x );
	void BoomDes();
	void BoomShow(HDC hdc);
};

