#pragma once
#include "ghost.h"
class GreenGhost :
	public CGhost
{
	
public:
	GreenGhost(void);
	//GreenGhost(CPacManApp*pApp);
	~GreenGhost(void);
public :
    void GhostInit(HINSTANCE hiatance);
	void GhostMove(int x,int y);
    void GhostShow(HDC hdc );
	void bfs(CBackArray &arr,int x,int y,int lastx,int lasty);
	void OperGhostMove();
	void startMove(CPacManApp *papp);
	void comeHome();
	//CPacManApp *p_green;
};

