#pragma once
#include"system.h"
#include"BackArray.h"
#include"Bean.h"
#include"BigBean.h"
#include"Fruit.h"
class CPacManApp;
class CPacMan
{
public :
	HBITMAP m_pacMan;
	HBITMAP m_wpacMan;
	HBITMAP  m_pacMan1;
	HBITMAP   m_wpacMan1;
	HBITMAP m_diePacman;
	int g_fx;
	int m_blood;
	int m_speed;
	int dx;
	int dy;
	//CBackArray m_array;����ô��Σ��¶�������µ���
	int pacMoveId;
	bool bflag;//�Ƿ����谭��
	int x;
	int y;
	bool iseat;
	bool changShow;
	bool isDied;//�Ƿ�����
	CPacManApp *m_CPacManApp;
public:
	CPacMan(void);
	CPacMan(CPacManApp *pCPacManApp);
	~CPacMan(void);
public:
	void PacManInit(HINSTANCE histance);
	void PacManMove(CBackArray&sz);
    bool eatBean(CBean *bean);
	bool eatBigBean(BigBean *bigBean);
	bool eatFruit(CFruit *fruit);
	void Move(CBackArray&sz);
	void PacManShow(HDC hdc);
	void DecBlood();
	bool isDying();
	void PacManShowDying(HDC hdc);
	//new �����delete����
};

