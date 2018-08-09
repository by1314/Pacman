#pragma once
#include "fruit.h"
class berry :
	public CFruit
{
public:
	berry(void);
	~berry(void);
public :
	void FruitShow(HDC hdc);
	void FruitInit(HINSTANCE hiatance);
};

