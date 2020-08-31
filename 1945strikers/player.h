#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "boss.h"
#include "Phoenix.h"

//ĳ���� ���� (�ִϸ��̼� ����)
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
	image* _move;		//�޸��� �������̹��� 10*2
	image* _death;
	image* _gameover;
	image* _blackScrren;
	image* _life;
	image* _bomb;
	image* _ultimate;

	int _count;			//������ ���� ī��Ʈ(�ӵ�����)
	int _index;			//������ �̹��� �ε���
	bool _isLeft;		//�����̳�?
	bool isDie;
	bool response;
	bool alpha_check;
	bool rectView;
	bool responseMove;
	bool responseTime;
	bool gameOver;
	int alpha;
	STATE _state;		//ĳ���� ����
	//bullet* _bullet;		//�κ�Ŭ���� ����
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
	//ĳ���� �ִϸ��̼�
	void animation();
	void coll();

	player() {}
	~player() {}
};

