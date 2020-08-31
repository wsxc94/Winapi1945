#pragma once
#include "singletonBase.h"

class enemyManager : public singletonBase <enemyManager>
{
private:
	//boss _boss;
public:

	HRESULT init();
	void release();
	enemyManager() {}
	~enemyManager() {}

};

