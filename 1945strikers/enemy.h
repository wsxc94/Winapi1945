#pragma once
#include "gameNode.h"
#include "e_bullet.h"
#define MAXENEMY 30
enum E_STATE
{
	Die
};
class enemy : public gameNode
{
private:
	E_STATE e_state;
	int time;
	bool rectView;
	int responCnt;
	bool responCheck;
public:
	e_bullet* enemy_bullet;
	vector<tagEnemy> v_enemy;
	HRESULT init();
	void release();
	void update();
	void render();
	void animation();
	void create();
	void enemy1create();

	void enemyOut();
	void enemyMove();
	void enemyFire();
	enemy() {}
	~enemy() {}
};

