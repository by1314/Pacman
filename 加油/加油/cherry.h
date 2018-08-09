#pragma once
#include "fruit.h"
class cherry :
	public CFruit
{
public:
	cherry(void);
	~cherry(void);
	
	void FruitShow(HDC hdc);
	void FruitInit(HINSTANCE hiatance);
};

