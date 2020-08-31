#pragma once
#include "singletonBase.h"
#include "image.h"

struct tagEnemy
{
	image* _img;
	image* _explosion;
	RECT _rc;
	float width;
	float height;
	bool isActive;
	bool isDie;
	float speed;
	int e_count;
	int e_index;
	bool e_move;

};

struct tagRocket
{
	float x, y;
	float angle;
	float radius;
	image* img;
	RECT _rc;
	bool isFire;
	float speed;
	int _count;
	int _index;
	float targetX;
	float targetY;
};

class rocketManager : public singletonBase<rocketManager>
{
private:
	int currentLevel;
	vector<tagRocket> v_bullet;
	//vector<tagRocket>::iterator iter;
	int targetX;
	int targetY;
	int distance;
	RECT _bossRC;

public:
	rocketManager() {}
	~rocketManager() {}

	HRESULT init(int level);
	void release();
	void update();
	void render(HDC hdc);

	void fire(float p_x, float p_y , float p_angle);
	//void bulletMove(float x , float y);
	void bulletMove(vector<tagEnemy>& v);
	void anim();
	void bulletOut();
	bool coll(RECT _rc);
	void getBossPos(RECT _rc);
};

