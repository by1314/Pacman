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
	CBean *bb[50];//�ۺϹ�ϵ
		//findfriend
		//˽�г�Աͨ���ӿڻ�ȡ
		//m_

	int  x;
	int y;
public :
	void BackInit(HINSTANCE hinstance);
	void BackShow(HDC hdc);
	void BackArr(CBackArray &array);
};

