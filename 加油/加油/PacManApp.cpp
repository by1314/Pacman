#include "PacManApp.h"

IMPLEMENT(CPacManApp)

CPacManApp::CPacManApp(void)
{
	 hdc=NULL;
	 tempdc=NULL;
	 bitmap=NULL;
	 x=0;
	 y=0;
	
	 bflag=0;
	 m_nScore=0;
	 time=0;
	 m_pbigBean=new BigBean;
	 m_pbean=new CBean;
	 m_pboom=new Boom;
	
	 counterBoom=3;
	 eatenBeanNUM=0;
	 beanNum=167;

	 changefengMain=false;
	 m_initFlag=false;
	 canEatGhost=false;//�Ƿ����С�ƶ�
	
	 style=0;
	 dieCount=0;

	 m_thread=NULL;
	 m_bFlagQuit = true; 
	 m_bFlagQuitInit=true;
	 m_bFlagQuitDie=true;
	 m_bFlagQuitFruit=true;

	 soundBean=false;
	 soundDie=false;
	 m_hSemphore=NULL;
	 m_hSemphoreInit=NULL;
	 m_hSemphoreDie=NULL;
	 m_hSemphoreFruit=NULL;
	 maxSemNum=168;
	 initSnd=false;
}
CPacManApp::~CPacManApp(void)
{
	 DeleteObject(bitmap);
	 bitmap=NULL;
	 DeleteDC(tempdc);
	 ReleaseDC(m_hMainWnd, hdc);
	 //ɾ��������
	 list <CBean*>::iterator ite=m_listBean.begin();
	while(ite!=m_listBean.end())
	{
		delete (*ite);//��ֻɾ������
		(*ite)=NULL;
		ite++;
	}
	 list <Boom*>::iterator ite1=m_listBoom.begin();
	while(ite1!=m_listBoom.end())
	{
		delete (*ite1);
		(*ite1)=NULL;
		ite1++;
	}
}

void CPacManApp::OnCreateGame()
{
	 loadfengMian();
	 hdc=::GetDC(m_hMainWnd);
	 tempdc=CreateCompatibleDC(hdc);//����һ��������ͼƬ���������
	 bitmap=CreateCompatibleBitmap(hdc,630,720);//���Ի���ɫ��
	 SelectObject(tempdc,bitmap);

	this->CreateFruit(m_hIns);
	
	m_map.BackInit(m_hIns);
	m_player.PacManInit(m_hIns);
	
    this ->creatBoom();
	this->createBean(m_map.m_backArray);
	this->createGhost();

	this->createBigBean();
	
	m_thread=(HANDLE)_beginthreadex(0,0,&ThreadProc,this,0,0);
	m_threadInit=(HANDLE)_beginthreadex(0,0,&ThreadProcInit,this,0,0);
	m_threadDie=(HANDLE)_beginthreadex(0,0,&ThreadProcDie,this,0,0);
	m_threadFruit=(HANDLE)_beginthreadex(0,0,&ThreadProcFruit,this,0,0);


	m_hSemphore=CreateSemaphore(NULL,0,maxSemNum,NULL);
	m_hSemphoreInit=CreateSemaphore(NULL,0,maxSemNum,NULL);
	m_hSemphoreDie=CreateSemaphore(NULL,0,maxSemNum,NULL);
	m_hSemphoreFruit=CreateSemaphore(NULL,0,maxSemNum,NULL);
}

void CPacManApp::OnGameRun(WPARAM nTimerID)
{
	if(nTimerID==PACMAN_MOVE_ID)
	{
	    m_player.Move(m_map.m_backArray);
	    m_player.PacManMove(m_map.m_backArray);     
	
		this->eatBean();
		this->eatBigBean();
		this->eatFruit();
		this->isBeanNull();
		
	}
	if(nTimerID==PACMAN_CHANG_ID)
	{
		this->changPacManId();
	}
	if(nTimerID==GHOST_MOVE_ID)
	{
		this->GhostMove();
	}
	if(nTimerID==JISHU)
	{
	   increaseTime();
	}
	if(nTimerID==PACMAN_DIE)
	{
		this->isDying();
	}
	  this->OnGameDraw();
}
void CPacManApp::OnGameDraw()
{
	 this->fengMianShow(tempdc);
	 if(changefengMain==true)
	 {
		DeleteObject(m_fengMian);
	    m_fengMian=NULL;
	    m_map.BackShow(tempdc); 
		this->ShowPacmanScore(tempdc);
		this->allBoomShow(tempdc);
	    this->GhostShow(tempdc);
		
		m_player.PacManShow(tempdc);
        AllBeanShow(m_map.m_backArray);//���ж�����ʾ
		this->showBigBean();
		this->showFruit();
	 }
	 //------------------------------------
	    BitBlt(hdc,0,0,630,720,tempdc,0,0,SRCCOPY);
 }
void CPacManApp::OnKeyDown(WPARAM nKey)
{
	if(nKey==VK_UP)
	{
		m_player.g_fx=0;
	}
	if(nKey==VK_DOWN)
	{
		m_player.g_fx=1;
	}
	if(nKey==VK_LEFT)
	{
		m_player.g_fx=2;
	}
	if(nKey==VK_RIGHT)
	{
		m_player.g_fx=3;	
	}
	if(nKey==13)
	{
	    this->deleteBoom();
		//this->changPacShow();
		//m_initFlag=true;
	}
	if(nKey=VK_SPACE&&dieCount<=2)
	{
		this->startTimer();
	}
}
unsigned _stdcall CPacManApp::ThreadProcInit( void * lpvoid )
{
	
	CPacManApp*pthis=(CPacManApp*)lpvoid;
	while(pthis->m_bFlagQuitInit)
	{
		if(WaitForSingleObject(pthis->m_hSemphoreInit,INFINITE)!= WAIT_OBJECT_0)
		{ //û�ȵ��ͼ�����
			continue;
		}
		PlaySound(MAKEINTRESOURCE(IDR_WAVE5),GetModuleHandle(NULL), SND_RESOURCE);
	}
	return 0;
}
unsigned _stdcall CPacManApp::ThreadProc( void * lpvoid )//bigBean
{
	CPacManApp*pthis=(CPacManApp*)lpvoid;
	while(pthis->m_bFlagQuit)
	{
		if(WaitForSingleObject(pthis->m_hSemphore,INFINITE)!= WAIT_OBJECT_0)
		{ //û�ȵ��ͼ�����
			continue;
		}
		//�ȵ�����������
		PlaySound(MAKEINTRESOURCE(IDR_WAVE10),GetModuleHandle(NULL), SND_RESOURCE);
		Sleep(1);
	}
	return 0;

	
}
unsigned _stdcall CPacManApp::ThreadProcFruit( void * lpvoid )
{
	CPacManApp*pthis=(CPacManApp*)lpvoid;
	while(pthis->m_bFlagQuitFruit)
	{
		if(WaitForSingleObject(pthis->m_hSemphoreFruit,INFINITE)!= WAIT_OBJECT_0)
		{ //û�ȵ��ͼ�����
			continue;
		}
		//�ȵ�����������
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3),GetModuleHandle(NULL), SND_RESOURCE);
		Sleep(1);
	}
	return 0;
}
unsigned _stdcall CPacManApp::ThreadProcDie( void * lpvoid )
{
	CPacManApp*pthis=(CPacManApp*)lpvoid;
	while(pthis->m_bFlagQuitDie)
	{
		if(WaitForSingleObject(pthis->m_hSemphoreDie,INFINITE)!= WAIT_OBJECT_0)
		{ //û�ȵ��ͼ�����
			continue;
		}
		//�ȵ�����������
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2),GetModuleHandle(NULL), SND_RESOURCE);
		Sleep(1);
	}
	return 0;
}
void CPacManApp::startTimer()
{
    SetTimer(m_hMainWnd,PACMAN_MOVE_ID,170,NULL);
    SetTimer(m_hMainWnd,PACMAN_CHANG_ID,80,NULL);//���ƳԶ�������
	SetTimer(m_hMainWnd,GHOST_MOVE_ID,190,NULL);
	SetTimer(m_hMainWnd,PACMAN_DIE,200,NULL);
	SetTimer(m_hMainWnd,KEY_STATE_DOWN,1,NULL);//�����̰���״̬
}
void  CPacManApp::OnLButtonDown(POINT point)
{
	this->startTimer();
	changefengMain=true;
	if(m_hSemphoreInit)//��֤�����������������ʾ
	{
		CloseHandle(m_hSemphoreInit);
		m_hSemphoreInit = NULL;
	}
	//ReleaseSemaphore(m_hSemphoreInit,1,NULL);//�ڷ�����ʾ��ʱ���ͷ��ź���
	
}
void CPacManApp::killTimerAll()
{
	KillTimer(m_hMainWnd,PACMAN_MOVE_ID);
	KillTimer(m_hMainWnd,GHOST_MOVE_ID);
}
void CPacManApp::changPacShow()
{
	//m_player.changShow=true;	
}
void CPacManApp::initGameSnd()
{
		PlaySound(MAKEINTRESOURCE(IDR_WAVE5),GetModuleHandle(NULL), SND_RESOURCE);
}
bool CPacManApp::isDying()
{   //�ڶ�ʱ�����ж��������
	list<CGhost*>::iterator ite=m_listGhost.begin();
	while(ite!=m_listGhost.end())
	{
		if((*ite)->meetPacMan(&m_player)==true)//ȡ��ַ
		{ 
			ReleaseSemaphore(m_hSemphoreDie,1,NULL);
            dieCount++;
			(*ite)->comeHome();
			if(dieCount==1)
			{

			this->killTimerAll();
			MessageBox(NULL,"С�����������ˣ�����ո������","��һ����",MB_OK);
			  break;
			}
			if(dieCount==2)
			{
			 
			 this->killTimerAll();
			  MessageBox(NULL,"С�������������ˣ�����ո������","�ڶ���",MB_OK);
			  break;
			}
			if(dieCount==3)
			{
			  this->killTimerAll();
			  MessageBox(NULL,"С������˫�����ˣ�û��������","������",MB_OK);
			  MessageBox(NULL,"��Ϸ�������Ҳ�������һ�Σ�","�����ټ�",MB_OK);
			  break;
			}
		}
		ite++;
	}
	return true;
}
void CPacManApp::changDieGhostId()
{
	 if(m_player.pacMoveId!=0)
	{
		m_player.pacMoveId-- ;
	}
	 else 
	 {
		 m_player.pacMoveId=3;
	 }
	 this->OnGameDraw();
}
void CPacManApp::changPacManId()
{
     if(m_player.pacMoveId!=0)
	{
		m_player.pacMoveId-- ;
	}
	 else 
	 {
		 m_player.pacMoveId=3;
	 }
	 this->OnGameDraw();
}
void CPacManApp::AllBeanShow(CBackArray &arr)
{
	list<CBean*>::iterator ite=m_listBean.begin();
	while(ite!=m_listBean.end())
	{
		(*ite)->BeanShow(tempdc);
		++ite;
	}
}
void CPacManApp::allBoomShow(HDC hdc)
{
	list<Boom*>::iterator  ite=m_listBoom.begin();
	while(ite!=m_listBoom.end())
	{
		(*ite)->BoomShow(hdc);
		/*if(ite==m_listBoom.end())
		{
			return ;
		}*/
		ite++;
	}
}
void CPacManApp::increaseTime()
{
	time=time+1;
}
void CPacManApp::changGhostId()//ÿ5�����һ��  //����
{
	 if(m_player.pacMoveId!=0)
	{
		m_player.pacMoveId-- ;
	}
	 else 
	 {
		 m_player.pacMoveId=3;
	 }
	 this->OnGameDraw();
}
void CPacManApp::createBean(CBackArray &arr)
{
	int nnm=0;
		while(nnm!=167)
		{
	          	   CBean *newBean=new CBean;
				   newBean->BeanInit(m_hIns,arr);
				   m_listBean.push_back(newBean);
				   nnm++;
		}
}
void CPacManApp::creatOrange()
{
	CFruit *fruit=new orange;
	m_listFruit.push_back(fruit);
	fruit->FruitInit(m_hIns,150,120);
}
void CPacManApp::creatCherry()
{
	CFruit *fruit=new cherry;
	m_listFruit.push_back(fruit);
	fruit->FruitInit(m_hIns,450,120);
}
void CPacManApp::creatCake()
{
	CFruit *fruit=new cake;
	m_listFruit.push_back(fruit);
	fruit->FruitInit(m_hIns,150,570);
}
void CPacManApp::creatBerry()
{
	CFruit *fruit=new berry;
	m_listFruit.push_back(fruit);
	fruit->FruitInit(m_hIns,450,570);
}
void CPacManApp::CreateFruit(HINSTANCE hinstance)//create showì��
{
	this->creatCake();
	this->creatOrange();
	this->creatCherry();
	this->creatBerry();
}
void CPacManApp::showFruit()
{
	if(m_listFruit.size()>0)//������ж�ȫ���������������Ԫ�ؾͻ��
	{
	list<CFruit*>::iterator ite=m_listFruit.begin();
	if(*ite!=NULL)
	{
		   (*ite)->FruitShow(tempdc);
	}
	else
		return ;
	}
}
void CPacManApp::isBeanNull()
{
	if(beanNum==0)
	{
		dieCount=4;
		this->killTimerAll();
		MessageBox(NULL,"��Ϸ����! ��Ӯ����","���Ӷ�û����",MB_OK);
		
	}	
}
void CPacManApp::eatBean()
{
	bool flag=false;
	list <CBean*>::iterator ite=m_listBean.begin();//��
	while(ite!=m_listBean.end())
	{
		if(m_player.eatBean(*ite))//����Ե���
		{
			soundBean=true;
			m_nScore+=5;
			beanNum-=1;
		    flag=true;
			delete (*ite);
			(*ite)=NULL;
			ite=m_listBean.erase(ite);//Ҫ��סһ��

			/*if(ite==m_listBean.end())
			{
				break;
			}*/
		}
		if(!flag)//ɾ��Ҫ�����Ƶ�
		{
		   ite++;
		}
		else
		{
			flag=false;//�û�false
		}
	}
}
void CPacManApp::destroyThread()//�����߳��Լ��ź���
{
	m_bFlagQuit=false;
	if(WAIT_TIMEOUT == WaitForSingleObject(m_thread,100))
	{
		TerminateThread(m_thread,-1);
	}
	CloseHandle(m_thread);
	m_thread = NULL;
	CloseHandle(m_threadInit);
	m_threadInit = NULL;
	CloseHandle(m_threadFruit);
	m_threadFruit = NULL;
	if(m_hSemphore)
	{
		CloseHandle(m_hSemphore);
		m_hSemphore = NULL;
	}
	if(m_hSemphoreInit)
	{
		CloseHandle(m_hSemphoreInit);
		m_hSemphoreInit = NULL;
	}
	if(m_hSemphoreDie)
	{
		CloseHandle(m_hSemphoreDie);
		m_hSemphoreDie = NULL;
	}
	if(m_hSemphoreFruit)
	{
		CloseHandle(m_hSemphoreFruit);
		m_hSemphoreFruit = NULL;
	}
}
void CPacManApp::eatFruit()
{
	bool flag=false;
	list <CFruit*>::iterator ite=m_listFruit.begin();//��
	while(ite!=m_listFruit.end())
	{
		if(m_player.eatFruit(*ite))//����Ե���
		{
			ReleaseSemaphore(m_hSemphoreFruit,1,NULL);
			(*ite)->eatflag=true;
			
			m_nScore+=30;
			
		    flag=true;
			delete (*ite);
			(*ite)=NULL;
			ite=m_listFruit.erase(ite);//Ҫ��סһ��
			if(ite==m_listFruit.end())
			{
				break;
			}
		}
		if(!flag)//ɾ��Ҫ�����Ƶ�
		{
		   ite++;
		}
		else
		{
			flag=false;//�û�false
		}
	}
}
void CPacManApp::creatBoom()
{
	int num=0;
	while(num!=3)
	{
		Boom *boom=new Boom;
		m_listBoom.push_back(boom);
		boom->BoomInit(m_hIns,458+num*43);
		num++;
	}
}
void CPacManApp:: deleteBoom()
{
	m_initFlag=true;
	if(m_listBoom.size()>0)//��֤������û��Ԫ���Ժ󲻻��
	{
	   list<Boom*>::iterator ite=m_listBoom.begin();
	    m_listBoom.erase(ite);
	}
}
void CPacManApp::ShowPacmanScore(HDC hdc)
{
	RECT rect1;
	RECT rect2;
	COLORREF m_BackcrColor; 
	m_BackcrColor = RGB(0,0,0);
	COLORREF m_TextcrColor; 
	m_TextcrColor = RGB(13,255,13);
	rect1.left = 10;
	rect1.top = 10;
	rect1.right = 200;
	rect1.bottom = 50;

	rect2.left = 10;
	rect2.top = 40;
	rect2.right = 200;
	rect2.bottom = 70;
	char buf1[255] = {0};
	char buf2[255] = {"����"};
	//������ת���ַ���
	_itoa_s(this->m_nScore,buf1,10);
	//������������
	
	//��������
	LOGFONT logfont;
	ZeroMemory(&logfont,sizeof(LOGFONT));
	logfont.lfCharSet = GB2312_CHARSET ;
	logfont.lfHeight = -25;    //��������Ĵ�С
	HFONT hfont = CreateFontIndirect(&logfont);
	//����������ɫ
	SetTextColor(hdc,m_TextcrColor);
	//���ñ�����ɫ
	SetBkColor (hdc, m_BackcrColor) ;
	SelectObject (hdc, hfont) ;
	
	//��ʾ����
	DrawText(hdc,buf2,-1,&rect1,0);
	DrawText(hdc,buf1,-1,&rect2,0);
	DeleteObject (hfont);
}
void CPacManApp::createBean1()
{
	BigBean *pbean=new BigBean;
	m_listBigBean.push_back(pbean);
	pbean->bigBeanInit(m_hIns,30,150);
}
void CPacManApp::createBean2()
{
	BigBean *pbean=new BigBean;
	m_listBigBean.push_back(pbean);
	pbean->bigBeanInit(m_hIns,570,150);
}
void CPacManApp::createBean3()
{
	BigBean *pbean=new BigBean;
	m_listBigBean.push_back(pbean);
	pbean->bigBeanInit(m_hIns,30,510);
}
void CPacManApp::createBean4()
{
	BigBean *pbean=new BigBean;
	m_listBigBean.push_back(pbean);
	pbean->bigBeanInit(m_hIns,570,510);
}
void CPacManApp::jishu()//δ
{
		RECT rect1;
	RECT rect2;
	COLORREF m_BackcrColor; 
	m_BackcrColor = RGB(0,0,0);
	COLORREF m_TextcrColor; 
	m_TextcrColor = RGB(13,255,13);
	rect1.left = 10;
	rect1.top = 10;
	rect1.right = 200;
	rect1.bottom = 50;

	rect2.left = 10;
	rect2.top = 40;
	rect2.right = 200;
	rect2.bottom = 70;
	char buf1[255] = {0};
	char buf2[255] = {"ʱ��"};
	//������ת���ַ���
	_itoa_s(this->m_nScore,buf1,10);
	//������������
	
	//��������
	LOGFONT logfont;
	ZeroMemory(&logfont,sizeof(LOGFONT));
	logfont.lfCharSet = GB2312_CHARSET ;
	logfont.lfHeight = -25;    //��������Ĵ�С
	HFONT hfont = CreateFontIndirect(&logfont);
	//����������ɫ
	SetTextColor(hdc,m_TextcrColor);
	//���ñ�����ɫ
	SetBkColor (hdc, m_BackcrColor) ;
	SelectObject (hdc, hfont) ;
	
	//��ʾ����
	DrawText(hdc,buf2,-1,&rect1,0);
	DrawText(hdc,buf1,-1,&rect2,0);
}
void CPacManApp::fengMianShow(HDC hdc)
{
	ReleaseSemaphore(m_hSemphoreInit,1,NULL);
	HDC tempdc=CreateCompatibleDC(hdc);
	SelectObject(tempdc,m_fengMian);
	BitBlt(hdc,x,y,630,720,tempdc,4,0,SRCCOPY);
	DeleteDC(tempdc);
}
void CPacManApp::createGhost()
{
	this->createRedGhost();
	this->createYellowGhost();
	this->createGreenGhost();
	this->createPinkGhost();
}
void CPacManApp::createRedGhost()
{
	    CGhost *ghost=NULL;
		ghost=new RedGhost;
		ghost->GhostInit(m_hIns);
		m_listGhost.push_back(ghost);

}
void CPacManApp::createYellowGhost()
{
	    CGhost *ghost=NULL;
        ghost=new YellowGhost;
		ghost->GhostInit(m_hIns);
		m_listGhost.push_back(ghost);
}
void CPacManApp::createGreenGhost()
{
	    CGhost *ghost=NULL;
        ghost=new GreenGhost;
		ghost->GhostInit(m_hIns);
		m_listGhost.push_back(ghost);
}
void CPacManApp::createPinkGhost()
{
	    CGhost *ghost=NULL;
        ghost=new PinkGhost;
		ghost->GhostInit(m_hIns);
		m_listGhost.push_back(ghost);
}
void CPacManApp::GhostShow(HDC hdc)
{
	list<CGhost*>::iterator ite=m_listGhost.begin();
	while(ite!=m_listGhost.end())
	{
		(*ite)->GhostShow(tempdc);
		ite++;
	}
}
void CPacManApp::GhostMove()
{
	list<CGhost*>::iterator ite=m_listGhost.begin();

	while(ite!=m_listGhost.end())
	{
		if(ite==m_listGhost.end())//���β�ڵ���
		{
			return ;
		}
		if(this->m_initFlag==true)
         {
			this->comeHome();
		
			(*ite)->startMove(this);
			if((*ite)->move==true)
			{
				if((*ite)->aaaa==1)
				(*ite)->bfs(m_map.m_backArray,(*ite)->x,(*ite)->y,m_player.x,m_player.y);
				(*ite)->OperGhostMove();
			
			}
			ite++; 
			m_initFlag=false;//����false��һֱ��������ֵ
		  }
		(*ite)->startMove(this);
		if((*ite)->move==true)
		{
			if((*ite)->aaaa==1)
			(*ite)->bfs(m_map.m_backArray,(*ite)->x,(*ite)->y,m_player.x,m_player.y);
			(*ite)->OperGhostMove();
			
		}
		ite++; 
		//m_initFlag=false;
	}
	}

void CPacManApp::meetGhost()
{

}
void CPacManApp::comeHome()
{
	list<CGhost*>::iterator ite2=m_listGhost.begin();
	while(ite2!=m_listGhost.end())
	{
		if(ite2==m_listGhost.end())
		{
			return ;
		}
		(*ite2)->comeHome();
		ite2++;
	}
}
void CPacManApp::createBigBean()
{
	this->createBean1();
	this->createBean2();
	this->createBean3();
	this->createBean4();
}
void CPacManApp::showBigBean()
{
	list<BigBean *>::iterator ite=m_listBigBean.begin();
	while(ite!=m_listBigBean.end())
	{
		(*ite)->bigBeanShow(tempdc);
		ite++;
	}
}
void CPacManApp:: eatBigBean()
{
	bool flag=false;
	
	list <BigBean*>::iterator ite=m_listBigBean.begin();//��
	while(ite!=m_listBigBean.end())
	{
		if(m_player.eatBigBean(*ite))//����Ե���
		{
			ReleaseSemaphore(m_hSemphore,1,NULL);
			m_nScore+=20;
			
		    flag=true;
			delete (*ite);
			(*ite)=NULL;
			ite=m_listBigBean.erase(ite);//Ҫ��סһ��
			if(ite==m_listBigBean.end())
			{
				break;
			}
		}
		if(!flag)//ɾ��Ҫ�����Ƶ�
		{
		   ite++;
		}
		else
		{
			flag=false;//�û�false
		}
	}
}

void CPacManApp::loadfengMian()
{
	
	m_fengMian=LoadBitmap(m_hIns,MAKEINTRESOURCE(IDB_FENGMIAN));
}

void CPacManApp::changstyle()
{
	//�ı�Ŀ���
	//��������false���
}
