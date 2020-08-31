#pragma once
#include "gameNode.h"
#define PI 3.141592
#define DEGREE(p) (PI/180*(p))
struct tagBoss
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
	float x;
	float y;
	float angle;
	float angle2;
	int hp;
	int _count;
	int _index;
	int time;
	//float b_speed;
	bool b_dir;
};
class boss : public gameNode
{
private:
	tagBoss _boss;
	bool respone;
	int selectPattern;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void animation();
	void create();
	void bossMove();
	void bossFire();
	bool bossColl(RECT rc , int _damage);
	void anim();

	RECT getbossRC() { return _boss._rc; }
	boss() {}
	~boss() {}

};



