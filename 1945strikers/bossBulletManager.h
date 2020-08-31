#pragma once
#include "singletonBase.h"
#include "image.h"
#define MAXBULLET_BOSS 300

enum PATTRN
{
	PATTRN1,
	PATTRN2,
	PATTRN3
};

struct tagBossBullet
{
	float x, y;
	float angle;
	float radius;
	image* img;
	RECT _rc;
	bool isFire;
	float speed;
	PATTRN pt;
	int _count;
	int _index;
	int width;
	int height;
};

class bossBulletManager : public singletonBase<bossBulletManager>
{
public:
	bossBulletManager() {}
	~bossBulletManager() {}

	HRESULT init();

	void release();
	void update();
	void render(HDC hdc);

	void fire(float p_x, float p_y , float angle, PATTRN pt);
	void bulletMove();
	void anim();
	void bulletOut();
	bool collision(RECT p_rc);

protected:
	PATTERN _pt;
	vector<tagBossBullet> v_BossBullet;
	vector<tagBossBullet> v_BossBullet2;
	vector<tagBossBullet> v_BossBullet3;
};
