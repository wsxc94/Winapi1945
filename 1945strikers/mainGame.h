#pragma once
//#include "gameNode.h"
#include "player.h"
#include "enemy.h"

class mainGame : public gameNode
{
private:
	int _loopX, _loopY;	//루프시길 속도
	player* _player;	//플레이어 클래스
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
	//이곳에 함수 선언

	mainGame() {}
	~mainGame() {}
};