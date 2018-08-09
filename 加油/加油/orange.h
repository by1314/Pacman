#pragma once
#include "fruit.h"
class orange :
	public CFruit
{
public:
	orange(void);
	~orange(void);
	void FruitShow(HDC hdc );
	void FruitInit(HINSTANCE hiatance);
};

