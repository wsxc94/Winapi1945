#pragma once
//#include "gameNode.h"
#include "player.h"
#include "enemy.h"

class mainGame : public gameNode
{
private:
	int _loopX, _loopY;	//�����ñ� �ӵ�
	player* _player;	//�÷��̾� Ŭ����
	enemy* _enemy;

	image* _main;
	image* _startButton;
	image* _loading;
	int time;
	bool _gameStart;
	bool _load;
	bool _loadLoop;
	int alpha;
	bool timecheck;
	int _count;
	int _index;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void loadAnim();
	//�̰��� �Լ� ����

	mainGame() {}
	~mainGame() {}
};