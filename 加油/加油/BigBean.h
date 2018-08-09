#pragma once
#include"system.h"
class BigBean
{
public :
	HBITMAP  m_bigBean;
	HBITMAP m_w_bigBean;
	int x;
	int y;
public:
	BigBean(void);
	~BigBean(void);
	void bigBeanInit(HINSTANCE hinstance,int x,int y);
	void bigBeanShow(HDC hdc);
};

