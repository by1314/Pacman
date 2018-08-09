#pragma once
#include "fruit.h"
class cake :
	public CFruit
{
public:
	cake(void);
	~cake(void);
public :
	void FruitShow(HDC hdc);
	void FruitInit(HINSTANCE hiatance);
};

