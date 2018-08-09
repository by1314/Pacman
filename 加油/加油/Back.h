#pragma once
#include"system.h"
#include"BackArray.h"
#include"Bean.h"
//630+16   720+38
//
class CBack
{
public:
	CBack(void);
	~CBack(void);
public :
	HBITMAP m_back;
	HBITMAP m_logo;
	CBackArray m_backArray;
	CBean *bb[50];//聚合关系
		//findfriend
		//私有成员通过接口获取
		//m_

	int  x;
	int y;
public :
	void BackInit(HINSTANCE hinstance);
	void BackShow(HDC hdc);
	void BackArr(CBackArray &array);
};

