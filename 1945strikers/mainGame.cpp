#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//이곳에서 초기화를 한다
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("백그라운드", "image/backGround.bmp", 600, 4288);
	IMAGEMANAGER->addImage("메인화면", "image/inGameStart.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("스타트버튼", "image/inGameStartButton.bmp", 305, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로딩", "image/loading.bmp", 3000, 800, 5, 1);

	_main = IMAGEMANAGER->findImage("메인화면");
	_startButton = IMAGEMANAGER->findImage("스타트버튼");
	_loading = IMAGEMANAGER->findImage("로딩");

	_count = 0;
	_index = 0;
	//루프용 변수 초기화
	_loopX = _loopY = 0;
	time = 0;
	_gameStart = false;
	_load = false;
	//플레이어 클래스 초기화
	_player = new player;
	_player->init();

	/*_enemy = new enemy;
	_enemy->init();*/

	_loadLoop = false;
	alpha = 0;
	timecheck = false;

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다

	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);
	/*_enemy->release();
	SAFE_DELETE(_enemy);*/
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	//충돌처리
	time++;
	if (INPUT->GetKeyDown('1')) {
		_gameStart = true;
		_load = true;
		time = 0;
	}
	if (!_gameStart) {
		//time = 0;
		if (time % 60 == 0)
		{
			if (!timecheck) {
				alpha = 255;
				timecheck = true;
			}
			else {
				alpha = 0;
				timecheck = false;
			}
			
		}
		
	}
	else {
		if (_load) {
			loadAnim();
		}
		else {
			_loopY--;
			//플레이어 클래스 업데이트
			_player->update();
			//_enemy->update();

		}
	}
	
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것은 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다
	
	//백그라운드 렌더
	//IMAGEMANAGER->render("백그라운드", getMemDC());

	//백그라운드 루프렌더
	if (_gameStart && !_load) {
		RECT rc = RectMake(0, 0, WINSIZEX, 4288);
		IMAGEMANAGER->loopRender("백그라운드", getMemDC(), &rc, _loopX, _loopY);
		//플레이어 렌더
		_player->render();
		//_enemy->render();
	}
	if (!_gameStart && !_load) { 
		_main->render(getMemDC(), 0, 0);
		//_startButton->render(getMemDC(), WINSIZEX / 2 - 150, WINSIZEY - 200);
		_startButton->alphaRender(getMemDC(), WINSIZEX / 2 - 150, WINSIZEY - 200, alpha);
	}
	if (_load)
	{
		_loading->frameRender(getMemDC(), 0, 0);
	}
	
//=============================================================
	//백버퍼의 내용을 화면DC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}

void mainGame::loadAnim()
{
	_count++;
	_loading->setFrameY(0);
	if (!_loadLoop)
	{
		if (_count % 20 == 0)
		{
			if (_index < 4)
			{
				_index++;
			}	
			_loading->setFrameX(_index);
			if (_index == 4)
			{
				_loadLoop = true;
			}
		}
	}
	else {
		if (time % 30 == 0)
		{
			if (timecheck)
			{
				_index = 4;
				timecheck = false;
			}
			else {
				_index = 3;
				timecheck = true;
			}
		}
		_loading->setFrameX(_index);
		if (time % 300 == 0) _load = false;

	}
}

