#pragma once
#include "gameNode.h"
#define MAXBULLET 100
struct tagBullet
{
	float x, y;
	float angle;
	float radius;
	image* img;
	RECT _rc;
	bool isFire;
	float speed;
};
class bullet : public gameNode
{
private:
	//tagBullet bul;
	
	int b_count;			//프레임 돌릴 카운트(속도조절)
	int b_index;			//프레임 이미지 인덱스
	bool rectView;
	int currentLevel;
public:
	vector<tagBullet> _vBullet;
	vector<tagBullet> _vBullet2;
	vector<tagBullet> _vBullet3;

	virtual HRESULT init(int level);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float p_x , float p_y);
	virtual void bulletMove();
	virtual void anim();
	virtual void bulletOut();
	bullet(){}
	virtual ~bullet(){}
};

