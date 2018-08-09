#pragma once
#include<windows.h>
#include<iostream>
#include<list>
#include<stdlib.h>
#include<queue>
#include<vector>
#include"resource.h"//注意 自己写的别加这里
#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库
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
//幽灵出现   响声音

using namespace std;
 //PlaySound(MAKEINTRESOURCE(IDR_WAVE3),GetModuleHandle(NULL), SND_RESOURCE);