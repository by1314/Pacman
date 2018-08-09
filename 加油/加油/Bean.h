#pragma once
#include"BackArray.h"
#include"system.h"
class CBean
{
public :
	HBITMAP m_bean;
	HBITMAP m_wbean;
	int x;
	int y;
public:
	CBean(void);
	~CBean(void);
	void BeanInit(HINSTANCE hiatance,CBackArray &arr);
	bool eatBean(CBean *bean);
    void BeanShow(HDC hdc);
};

