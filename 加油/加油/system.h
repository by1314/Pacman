#pragma once
#include<windows.h>
#include<iostream>
#include<list>
#include<stdlib.h>
#include<queue>
#include<vector>
#include"resource.h"//ע�� �Լ�д�ı������
#include "mmsystem.h"//��������ͷ�ļ�
#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���
#define PACMAN_MOVE_ID  0
#define KEY_ID  1
#define PACMAN_CHANG_ID 2
#define GHOST_MOVE_ID   3
#define  CREATE_FRUIT     4
#define RAND_FRUIT        5
#define JISHU             6
#define PACMAN_DIE        7
#define MAXN           99999
#define KEY_STATE_DOWN    8
//�������   ������

using namespace std;
 //PlaySound(MAKEINTRESOURCE(IDR_WAVE3),GetModuleHandle(NULL), SND_RESOURCE);