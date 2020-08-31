#pragma once
#include "bullet.h"
#define PI 3.141592f
class e_bullet : public bullet
{
private:
	//tagBullet bul;
	bool rectView;
	vector<tagBullet>::iterator _viBullet;
public:
	vector<tagBullet> e_vBullet;
	int bulletcount;
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float p_x, float p_y);
	virtual void bulletMove();
	void anim();
	virtual void bulletOut();
	e_bullet() {}
	virtual ~e_bullet() {}
};

