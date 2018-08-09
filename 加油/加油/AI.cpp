//#include "AI.h"
////abs fabs
//AI::AI()
//{
//	m_pstartNode=new Node;
//	m_pendNode= new Node;
//	isEndNode=NULL;//被赋值说明已经是终点
//	row=7;
//	col=9;
//}
//AI::~AI()
//{
//	delete m_pstartNode;
//	m_pstartNode=nullptr;
//	delete m_pendNode;
//	m_pendNode=nullptr;
//	delete isEndNode;
//	isEndNode=nullptr;
//}
//void AI::setStartNode(int x,int y)
//{
//	m_pstartNode->x=x;
//	m_pstartNode->y=y;	
//	m_pstartNode->parent=NULL;
//}
//void AI::setEndNode(int x,int y)
//{
//    m_pendNode->x=x;
//	m_pendNode->y=y;
//}
//void AI::InitMap(CBackArray &arr)
//{
//	for(int i=0;i<24;i++)
//	{
//		for(int j=0;j<21;j++)
//		{
//			sz[i][j]=arr.arr[i][j];//row.col
//			col=j;
//		}
//		row=i;
//	}
//}
//bool AI::isInOpen(Node*node)
//{
//	list<Node*>::iterator ite=m_openList.begin();
//	while(ite!=m_openList.end())
//	{
//		if(node->x==(*ite)->x&&node->y==(*ite)->y)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//bool AI::isBlocked(Node*node)
//{
//	for(int i=0;i<row;i++)
//	{
//		for(int j=0;j<col;j++)
//		{
//			if(sz[i][j]==1)//输出@#
//			{
//				//node->bflag=1 ;
//				return false;
//			}
//			//node->bflag=0;
//			return true;
//		}
//	}
//}
//bool AI::isInClose(Node*node)
//{
//	list<Node*>::iterator ite=m_closeList.begin();
//	while(ite!=m_closeList.end())
//	{
//		if(node->x==(*ite)->x&&node->y==(*ite)->y)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//Node*AI::getBestNode()
//{
//	Node* minNode;//new？
//	int bestF=MAXN;
//	list <Node*>::iterator bjIte;
//	list <Node*>::iterator  ite=m_openList.begin();
//	while(ite!=m_closeList.end())
//	{
//		if((*ite)->f<bestF)
//		{
//			bestF=(*ite)->f;
//			minNode=(*ite);//node里装的就是最小的f
//			bjIte=ite;
//		}
//		ite++;
//	}
//	if(minNode)
//	{
//		m_openList.erase(bjIte);
//	}
//	return minNode;//局部变量？
//}
//void  AI::calH(Node*node)
//{
//	int high=abs(node->y-m_pendNode->y);
//	int wide=abs(node->x-m_pendNode->x);
//	node->h=(high+wide)*m_cost;
//}
//void  AI::calF(Node*node)//是否有返回值
//{
//	calG(node);
//	calH(node);
//	node->f=node->g+node->h;
//}
//void AI::calG(Node*node)
//{
//	node->g=node->parent->g+m_cost;///?????????
//}
//void AI::checkNode(Node*preNode,int x,int y)
//{
//	Node*newNode=new Node;
//	newNode->parent=preNode;
//	if(isInClose(newNode)||isBlocked(newNode))
//	{
//		return ;
//	}
//	if(!isInOpen(newNode))
//	{
//		m_openList.push_front(newNode);
//		
//		    //calF(newNode);//添加后最小值的计算由getBestNode得出就可以
//	}
//		if(newNode->x == m_pendNode->x && newNode->y == m_pendNode->y)  
//		{
//			 isEndNode = newNode;
//		}
//}
//bool AI::isPath()
//{
//
//	return true;
//}
//void AI:: search()
//{
//	Node*currentNode;
//	currentNode=m_pstartNode;//x,y初始化
//
//	currentNode->g=0;                       
//	currentNode->parent=NULL;
//	calH(currentNode);
//	calF(currentNode);
//
//	
//	m_openList.push_front(m_pstartNode);
//	
//
//	do
//	{
//		currentNode=getBestNode();
//
//		checkNode(currentNode,currentNode->x,currentNode->y-1);
//		checkNode(currentNode,currentNode->x,currentNode->y+1); 
//		checkNode(currentNode,currentNode->x-1,currentNode->y);
//		checkNode(currentNode,currentNode->x+1,currentNode->y);//x,y的处理
//
//		m_closeList.push_front(currentNode);
//
//		  if(m_openList.size()<1||isEndNode)//终点
//		{
//			break;
//		}
//	}while(true);
// }
//bool AI::isendNode(Node *currentnode)
//{
//	if((m_pendNode->x=currentnode->x)&&(m_pendNode->y=currentnode->y))
//	{
//		return true;
//	}
//	return false;
//}