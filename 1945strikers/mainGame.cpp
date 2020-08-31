#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//�̰����� �ʱ�ȭ�� �Ѵ�
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "image/backGround.bmp", 600, 4288);
	IMAGEMANAGER->addImage("����ȭ��", "image/inGameStart.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("��ŸƮ��ư", "image/inGameStartButton.bmp", 305, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ε�", "image/loading.bmp", 3000, 800, 5, 1);

	_main = IMAGEMANAGER->findImage("����ȭ��");
	_startButton = IMAGEMANAGER->findImage("��ŸƮ��ư");
	_loading = IMAGEMANAGER->findImage("�ε�");

	_count = 0;
	_index = 0;
	//������ ���� �ʱ�ȭ
	_loopX = _loopY = 0;
	time = 0;
	_gameStart = false;
	_load = false;
	//�÷��̾� Ŭ���� �ʱ�ȭ
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
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�

	//�÷��̾� Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);
	/*_enemy->release();
	SAFE_DELETE(_enemy);*/
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�
	//�浹ó��
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
			//�÷��̾� Ŭ���� ������Ʈ
			_player->update();
			//_enemy->update();

		}
	}
	
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰��� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//�̰����� WM_PAINT���� �ߴ����� ó���ϸ� �ȴ�
	
	//��׶��� ����
	//IMAGEMANAGER->render("��׶���", getMemDC());

	//��׶��� ��������
	if (_gameStart && !_load) {
		RECT rc = RectMake(0, 0, WINSIZEX, 4288);
		IMAGEMANAGER->loopRender("��׶���", getMemDC(), &rc, _loopX, _loopY);
		//�÷��̾� ����
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
	//������� ������ ȭ��DC�� �׸��� (�̰͵� ������ �׳� �α�)
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

