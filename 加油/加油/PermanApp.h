#pragma once
#include "cgamectrl.h"
#include"Back.h"
#include"PacMan.h"
#include"Boom.h"
#include"BackArray.h"
class CPermanApp :
	public CGameCtrl
{
public :
	CBack m_map;
	CPacMan m_player;
	Boom m_boom;
	CBackArray m_array;
public :
	DECLARE()
public:
	CPermanApp(void);
	~CPermanApp(void);
	virtual void OnCreateGame() ;
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimerID);
	virtual void OnKeyDown(WPARAM nKey);
};

