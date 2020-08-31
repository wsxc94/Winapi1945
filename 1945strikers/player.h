#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "boss.h"
#include "Phoenix.h"

//캐릭터 상태 (애니메이션 포함)
#define MAXBULLET 30

enum STATE
{
	IDLE,
	LEFT,
	RIGHT,
	MOVE,
	DIE,
	ULTIMATE
};

class player : public gameNode
{
private:
	image* _move;		//달리는 프레임이미지 10*2
	image* _death;
	image* _gameover;
	image* _blackScrren;
	image* _life;
	image* _bomb;
	image* _ultimate;

	int _count;			//프레임 돌릴 카운트(속도조절)
	int _index;			//프레임 이미지 인덱스
	bool _isLeft;		//왼쪽이냐?
	bool isDie;
	bool response;
	bool alpha_check;
	bool rectView;
	bool responseMove;
	bool responseTime;
	bool gameOver;
	int alpha;
	STATE _state;		//캐릭터 상태
	//bullet* _bullet;		//인벤클래스 선언
	int time;
	int p_count;
	bullet* _bullet;
	enemy* _enemy;
	boss* _boss;
	Phoenix* _phoenix;
	RECT p_rc;
	int p_speed;
	int bulletLevel;
	int boomCnt;
	int deathCnt;
	int damage;
	int cooldown;
	int ultidamage;
	bool dealTime;
	bool delayTime;
	pair<bool, ITEMKIND> itemcheck;
public:
	
	HRESULT init();
	void release();
	void update();
	void render();
	void playerControl();
	//캐릭터 애니메이션
	void animation();
	void coll();

	player() {}
	~player() {}
};

