#pragma once
#include "gameNode.h"
class Phoenix : public gameNode
{

private:
	float _x, _y;
	image* img;
	RECT _rc;
	bool isFire;
	float speed;
	int _count;
	int _index;

public:
	Phoenix() {}
	~Phoenix() {}

	HRESULT init();
	void release();
	void update();
	void render();
	void fire(float x , float y);
	void bulletMove();
	void anim();
	void bulletOut();
	RECT getPhoenixRect() { return _rc; }
};

