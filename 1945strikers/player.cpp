#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	//rectView = false;
	isDie = false;
	IMAGEMANAGER->addFrameImage("player", "image/playerMove.bmp", 434, 80, 7, 1);
	IMAGEMANAGER->addFrameImage("death", "image/deathExplosions.bmp", 800, 94, 12, 1);
	IMAGEMANAGER->addImage("gameOver", "image/gameOver.bmp", 558, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackScrren", "image/blackScrren.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("life", "image/life.bmp", 30, 41, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bomb", "image/playerBombCount.bmp", 30, 41, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ultimate", "image/arcade4180135.bmp", 7800, 258, 44, 1);

	_move = IMAGEMANAGER->findImage("player");
	_death = IMAGEMANAGER->findImage("death");
	_gameover = IMAGEMANAGER->findImage("gameOver");
	_blackScrren = IMAGEMANAGER->findImage("blackScrren");
	_life = IMAGEMANAGER->findImage("life");
	_bomb = IMAGEMANAGER->findImage("bomb");
	_ultimate = IMAGEMANAGER->findImage("ultimate");

	deathCnt = 0;
	response = true;
	responseMove = true;
	gameOver = false;
	p_count = 3;
	p_speed = 5;
	alpha_check = true;
	_move->setX(WINSIZEX / 2);
	_move->setY(WINSIZEY + 50);
	bulletLevel = 1;
	boomCnt = 3;
	damage = bulletLevel;
	itemcheck = make_pair(false, NONE);
	delayTime = false;
	dealTime = false;
	rectView = false;
	_count = _index = 0;
	_isLeft = false;
	
	_state = IDLE;
	time = 0;
	alpha = 255;
	cooldown = 0;
	ultidamage = 30;
	//인벤클래스 초기화
	_bullet = new bullet;
	_bullet->init(bulletLevel);
	
	_enemy = new enemy;
	_enemy->init();

	_boss = new boss;
	_boss->init();

	_phoenix = new Phoenix;
	_phoenix->init();

	ROCKETMANAGER->init(bulletLevel);
	ROCKETMANAGER->getBossPos(_boss->getbossRC());
	ITEMMANAGER->init();
	return S_OK;
}

void player::release()
{
	//인벤클래스 해제
	_bullet->release();
	_enemy->release();
	_boss->release();

	ITEMMANAGER->release();
	ROCKETMANAGER->release();
	_phoenix->release();
	SAFE_DELETE(_bullet);
	SAFE_DELETE(_enemy);
	SAFE_DELETE(_boss);
}

void player::update()
{
	if (!gameOver)
	{
		if (response)
		{
			if (time % 10 == 0)
			{
				if (responseTime)
				{
					responseTime = false;
				}
				else {
					responseTime = true;
				}
			}
			if (_move->getY() > WINSIZEY - 200) {
				p_rc.top -= p_speed;
				p_rc.bottom -= p_speed;
				_move->setY(_move->getY() - p_speed);

				if (time % 20 == 0) {
					if (alpha_check)
					{
						alpha = 255;
						alpha_check = false;
					}
					else {
						alpha = 120;
						alpha_check = true;
					}

				}
			}
			else {
				responseMove = false;

				if (time % 150 == 0) {
					responseTime = false;
					response = false;

				}


			}
		}

		time++;

		//애니메이션
		this->animation();

		//인벤클래스 업데이트
		_bullet->update();
		_enemy->update();
		_boss->update();
		_phoenix->update();
		ROCKETMANAGER->update();
		ITEMMANAGER->update();
		if (!isDie)
		{
			playerControl();
			p_rc = RectMake(_move->getX() + 25, _move->getY() +30, 10, 30);
		}

		if (!isDie) {
			//playerControl();
			coll();
			//p_rc = RectMake(_move->getX() + 15, _move->getY() + 10, 30, 60);
		}
		//_enemy->enemyOut();
	}
	else {
		if (INPUT->GetKeyDown('r') || INPUT->GetKeyDown('R'))
		{
			gameOver = false;
			p_count = 3;
			deathCnt = 0;
		}
	}
}

void player::render()
{

	_enemy->render();
	_boss->render();
	_phoenix->render();

	//캐릭터 출력
	if (isDie) {
		_death->frameRender(getMemDC(), _move->getX(), _move->getY());
	}
	/*else if (response)
	{
		_move->alphaframeRender(getMemDC(), _move->getX(), _move->getY(), alpha);
	}*/
	else {
		if (!responseTime)
		{
			if(_state == MOVE || _state == IDLE)
			_move->frameRender(getMemDC(), _move->getX(), _move->getY());

			if (_state == ULTIMATE && delayTime)
			{
				_ultimate->frameRender(getMemDC(), _move->getX() - _ultimate->getFrameWidth() / 2 + 30, _move->getY() - _ultimate->getFrameHeight() / 2);
			}

		}
		
	}
	
	
	if (rectView)
	{
		Rectangle(getMemDC(), p_rc);
	}

	_bullet->render();
	
	ROCKETMANAGER->render(getMemDC());
	//ROCKET->render(getMemDC());
	ITEMMANAGER->render(getMemDC());

	for (int i = 0; i < p_count; i++)
	{
		_life->render(getMemDC(), 30  * (i), 40);
		
	}
	for (int i = 0; i < boomCnt; i++)
	{
		_bomb->render(getMemDC(), 30 * i, WINSIZEY - 50);
	}
	if (gameOver)
	{
		_blackScrren->alphaRender(getMemDC(), 0, 0, 100);
		_gameover->render(getMemDC(), 20, WINSIZEY / 2);
	}
}

void player::playerControl()
{
	cooldown++;
		if (INPUT->GetKey(VK_LEFT))
		{
			if (_state != ULTIMATE) {
				_isLeft = true;
				_state = MOVE;
				_index = 2;
			}
			//이미지 좌표 움직이기
			if (_move->getX() > 0) {
				
				_move->setX(_move->getX() - p_speed);
			}
			
			
		}
		if (INPUT->GetKeyUp(VK_LEFT))
		{
			if (_state != ULTIMATE)
			_state = IDLE;

		}
		if (INPUT->GetKeyUp(VK_RIGHT))
		{
			if (_state != ULTIMATE)
			_state = IDLE;
		}
		if (INPUT->GetKey(VK_RIGHT))
		{
			if (_state != ULTIMATE) {
				_isLeft = false;
				_state = MOVE;
				_index = 4;
			}
			//이미지 좌표 움직이기
			if (_move->getX() < WINSIZEX - 30) {
				
				_move->setX(_move->getX() + p_speed);
			}
			
		}
		if (INPUT->GetKeyDown(VK_F1))
		{
			if (rectView)
			{
				rectView = false;
			}
			else {
				rectView = true;
			}
		}
	
		if (!responseMove)
		{
			if (INPUT->GetKey(VK_UP))
			{
				if (_move->getY() > 0) {

					_move->setY(_move->getY() - p_speed);
				}

			}
			if (INPUT->GetKey(VK_DOWN))
			{
				if (_move->getY() < WINSIZEY - 70) {

					_move->setY(_move->getY() + p_speed);
				}

			}
			
		}
		if ((INPUT->GetKey('a') || INPUT->GetKey('A')) && !delayTime) {

			if (time % 8 == 0)
				_bullet->fire(_move->getX(), _move->getY());
			if (time % 20 == 0)
				ROCKETMANAGER->fire(_move->getX(), _move->getY() , 3.141592f/2);

		}
		if (INPUT->GetKeyDown('s') || INPUT->GetKeyDown('S') && cooldown > 20)
		{
			if (!delayTime && boomCnt > 0)
			{
				_count = 0;
				_index = 0;
				_phoenix->fire(_move->getX(), _move->getY());
				delayTime = true;
				_state = ULTIMATE;
				boomCnt--;
			}
			
		}
	

	

	
}
void player::animation()
{
	switch (_state)
	{
	case IDLE:
		_move->setFrameX(3);
		break;
	
	case MOVE:
		//왼쪽프레임 일때 인덱스 변경하기
		if (_isLeft)
		{
			_count++;
			_move->setFrameY(0);
			if (_count % 10 == 0)
			{
				
				if (_index > 0)
				{
					_index--;
				}
				_move->setFrameX(_index);
			}

		}
		else//오른쪽프레임
		{
			_count++;
			_move->setFrameY(0);
			if (_count % 10 == 0)
			{
				
				if (_index < 6)
				{
					_index++;
				}
				_move->setFrameX(_index);
			}
		}

		break;
	case DIE:
		_count++;
		_death->setFrameY(0);
		if (_count % 5 == 0)
		{

			if (_index < 11)
			{
				_index++;
			}
			else {
				if (p_count == 0)
				{
					
					if (deathCnt == 0) {
						ITEMMANAGER->active(p_rc.left, p_rc.top, RANDOM->range(DEGREE(1), DEGREE(360)), LEVLEUPITEM);
						ITEMMANAGER->active(p_rc.left, p_rc.top, RANDOM->range(DEGREE(1), DEGREE(360)), LEVLEUPITEM);
						ITEMMANAGER->active(p_rc.left, p_rc.top, RANDOM->range(DEGREE(1), DEGREE(360)), LEVLEUPITEM);
						ITEMMANAGER->active(p_rc.left, p_rc.top, RANDOM->range(DEGREE(1), DEGREE(360)), ULTIMATEITEM);
					}
					deathCnt++;
					if (deathCnt % 15 == 0) {

						gameOver = true;
						isDie = false;
						_state = IDLE;
						response = true;
						responseMove = false;
						_move->setX(WINSIZEX / 2);
						_move->setY(WINSIZEY + 50);
					}
					
				}
				else {

					isDie = false;
					_state = IDLE;
					response = true;
					responseMove = false;
					_move->setX(WINSIZEX / 2);
					_move->setY(WINSIZEY + 50);

				}
				
			}
			_death->setFrameX(_index);
		}
	case ULTIMATE:
		_count++;
		_ultimate->setFrameY(0);
		if (_count % 3 == 0)
		{
			if (_index < 47)
			{
				_index++;
			}
			else {
				
				delayTime = false;
				_state = IDLE;
				cooldown = 0;

				
			}
			_ultimate->setFrameX(_index);
		}
		//break;
	}

}

void player::coll()
{
	
	RECT tmp;
	if (BOSSBULLETMANAGER->collision(_phoenix->getPhoenixRect()));
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_enemy->enemy_bullet->_vBullet[i].isFire) continue;
		if (IntersectRect(&tmp, &_phoenix->getPhoenixRect(), &_enemy->enemy_bullet->_vBullet[i]._rc)) {
			_enemy->enemy_bullet->_vBullet[i].isFire = false;
		}
	}

	if (!response && !delayTime)
	{
		
		if (BOSSBULLETMANAGER->collision(p_rc)) {
			_state = DIE;
			isDie = true;
			_index = 0;
			p_count--;
			bulletLevel = 1;
			_bullet = new bullet;
			_bullet->init(bulletLevel);
			ROCKETMANAGER->release();
			ROCKETMANAGER->init(bulletLevel);
			delayTime = false;
			boomCnt = 3;
			damage = 1;
			
			return;
		}

		for (int i = 0; i < MAXBULLET; i++)
		{
			if (!_enemy->enemy_bullet->_vBullet[i].isFire) continue;
			if (IntersectRect(&tmp, &p_rc, &_enemy->enemy_bullet->_vBullet[i]._rc)) {
				_state = DIE;
				isDie = true;
				_index = 0;
				p_count--;
				bulletLevel = 1;
				_bullet = new bullet;
				_bullet->init(bulletLevel);
				ROCKETMANAGER->release();
				ROCKETMANAGER->init(bulletLevel);
				_enemy->enemy_bullet->_vBullet[i].isFire = false;
				boomCnt = 3;
				damage = 1;
				break;
			}
		}
		for (int j = 0; j < MAXENEMY; j++)
		{
			if (!_enemy->v_enemy[j].isActive) continue;
			if (IntersectRect(&tmp, &p_rc, &_enemy->v_enemy[j]._rc)) {
				_state = DIE;
				isDie = true;
				_index = 0;
				p_count--;
				bulletLevel = 1;
				_bullet = new bullet;
				_bullet->init(bulletLevel);
				ROCKETMANAGER->release();
				ROCKETMANAGER->init(bulletLevel);
				delayTime = false;
				boomCnt = 3;
				damage = 1;
				break;

			}

		}
	}
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_bullet->_vBullet[i].isFire) continue;
		for (int j = 0; j < MAXENEMY; j++)
		{
			if (!_enemy->v_enemy[j].isActive) continue;
			
			if (IntersectRect(&tmp, &_bullet->_vBullet[i]._rc, &_enemy->v_enemy[j]._rc)) {
				int rnd = RANDOM->range(0,10);
				if(rnd == 1)
				ITEMMANAGER->active(_enemy->v_enemy[j]._rc.left, _enemy->v_enemy[j]._rc.top , RANDOM->range(DEGREE(1), DEGREE(360)) ,LEVLEUPITEM);
				if (rnd == 2)
				ITEMMANAGER->active(_enemy->v_enemy[j]._rc.left, _enemy->v_enemy[j]._rc.top , RANDOM->range(DEGREE(1), DEGREE(360)) ,ULTIMATEITEM);
				_bullet->_vBullet[i].isFire = false;
				_enemy->v_enemy[j].isDie = true;
				_enemy->v_enemy[j].isActive = false;
				

			}

		}
	}

	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_bullet->_vBullet[i].isFire) continue;
		if (_boss->bossColl(_bullet->_vBullet[i]._rc , damage))
		{
			_bullet->_vBullet[i].isFire = false;
		}
	}
	
	if (!dealTime)
	{
	if (_boss->bossColl(_phoenix->getPhoenixRect(), ultidamage)) {
		//printf("보스필살기맞음 데미지 : %d\n", ultidamage);
		dealTime = true;
	}
	}
	else {
	if (time % 100 == 0) dealTime = false;

	}


	itemcheck = ITEMMANAGER->collision(p_rc);
	if (itemcheck.first && itemcheck.second == LEVLEUPITEM)
	{
		// 레벨업
		
		if (bulletLevel < 3) {
			bulletLevel++;
			damage++;
			//cout << "불렛레벨 : " << bulletLevel << '\n';
			//printf("불렛레벨 : %d\n", bulletLevel);
			_bullet = new bullet;
			_bullet->init(bulletLevel);
			ROCKETMANAGER->release();
			ROCKETMANAGER->init(bulletLevel);
			
		}
	

		itemcheck = make_pair(false, NONE);
	}
	if (itemcheck.first && itemcheck.second == ULTIMATEITEM) {
		//폭탄 +1
		//cout << "폭탄 + 1" << endl;
		//printf("폭탄 + 1\n");
		if(boomCnt < 5)
		boomCnt++;
		itemcheck = make_pair(false, NONE);
	}

	for (int i = 0; i < _enemy->v_enemy.size(); i++)
	{
		RECT tmp;
		if (!_enemy->v_enemy[i].isActive) continue;
		if (ROCKETMANAGER->coll(_enemy->v_enemy[i]._rc) || IntersectRect(&tmp , &_phoenix->getPhoenixRect() , &_enemy->v_enemy[i]._rc))
		{
			int rnd = RANDOM->range(0, 10);
			if (rnd == 1)
				ITEMMANAGER->active(_enemy->v_enemy[i]._rc.left, _enemy->v_enemy[i]._rc.top, RANDOM->range(DEGREE(1), DEGREE(360)), LEVLEUPITEM);
			if (rnd == 2)
				ITEMMANAGER->active(_enemy->v_enemy[i]._rc.left, _enemy->v_enemy[i]._rc.top, RANDOM->range(DEGREE(1), DEGREE(360)), ULTIMATEITEM);
			_enemy->v_enemy[i].isDie = true;
			_enemy->v_enemy[i].isActive = false;
		}
	}
}


