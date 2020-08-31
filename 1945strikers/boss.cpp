#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	IMAGEMANAGER->addFrameImage("보스", "image/boss1.bmp", 2000, 263, 5, 1);
	IMAGEMANAGER->addFrameImage("보스사망", "image/bossExplosions.bmp", 4000, 200, 20, 1);

	_boss._explosion= IMAGEMANAGER->findImage("보스사망");
	_boss._img = IMAGEMANAGER->findImage("보스");
	_boss.isDie = false;
	_boss.e_count = 0;
	_boss.e_index = 0;
	_boss.isActive = false;
	_boss.speed = 1.5f;
	_boss.hp = 500;
	_boss.angle = 270;
	_boss.angle2 = 270;
	_boss.x = WINSIZEX / 2;
	_boss.y = -100;
	_boss.width = _boss._img->getFrameWidth();
	_boss.height = _boss._img->getFrameHeight();
	_boss._index = 0;
	_boss._count = 0;
	_boss.time = 0;
	_boss.b_dir = false;
	respone = true;

	selectPattern = 0;
	BOSSBULLETMANAGER->init();
	return S_OK;
}

void boss::release()
{
	BOSSBULLETMANAGER->release();
}

void boss::update()
{
	_boss.time++;
	_boss._rc = RectMake(_boss.x - _boss._img->getFrameWidth()/2, _boss.y - _boss._img->getFrameHeight(), _boss._img->getFrameWidth(), _boss._img->getFrameHeight() - 100);

	if (_boss.time % 300 == 0)
	{
		create();
	}

	if (ROCKETMANAGER->coll(_boss._rc)) {
		_boss.hp--;
	}

	if (_boss.isActive)
	{
	bossMove();
	bossFire();
	}

	if (_boss.hp <= 0)
	{
		_boss.isActive = false;
		_boss.isDie = true;

	}

	if (_boss.isDie)
	{
		anim();
	}
	animation();

	BOSSBULLETMANAGER->update();
	//BOSSBULLETMANAGER->fire(1,2,3,PATTRN1);
}

void boss::render()
{
	if (_boss.isActive)
	{
		if (_boss.hp > 400)
		{
		_boss._img->frameRender(getMemDC(), _boss.x - _boss.width/2, _boss.y - _boss.height, 4, 0);
		}
		
		else if (_boss.hp > 200)
		{
			_boss._img->frameRender(getMemDC(), _boss.x - _boss.width / 2, _boss.y - _boss.height, 1, 0);
		}
		else if (_boss.hp > 0)
		{
			_boss._img->frameRender(getMemDC(), _boss.x - _boss.width / 2, _boss.y - _boss.height, 0, 0);
		}
		//IMAGEMANAGER->findImage("보스")->render(getMemDC(), _boss.x, _boss.y);
		//Rectangle(getMemDC(), _boss._rc);
	}
	if (_boss.isDie){
		_boss._explosion->frameRender(getMemDC(), _boss.x - 100, _boss.y - 200);
	}
	
	BOSSBULLETMANAGER->render(getMemDC());
}

void boss::animation()
{
	BOSSBULLETMANAGER->anim();
}

void boss::create()
{
	
	if (respone)
	{
		if (_boss.time % 180 == 0)
		{
			if (!_boss.isActive)
			{
				_boss.isActive = true;
				respone = false;
			}

		}
		
	}
	
}

void boss::bossMove()
{
	if (_boss.y < 200)
	{
		_boss.y += 2;
	}
	else {
		_boss.x += _boss.speed;

		if (_boss.x < 0 && _boss.b_dir) {
			_boss.b_dir = false;
		}
		if (_boss.x > WINSIZEX - 100 && !_boss.b_dir) {
			_boss.b_dir = true;
		}

		if (_boss.b_dir)
		{
			_boss.speed = -3.0f;
		}
		else {
			_boss.speed = 3.0f;
		}
	}
	
}

void boss::bossFire()
{


	if (_boss.time > 200 && _boss.time < 900)
	{
		if (_boss.time % 20 == 0)
		{
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle), PATTRN1);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle - 45), PATTRN1);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle + 45), PATTRN1);
		}
	}
	else if (_boss.time > 1000 && _boss.time < 2000)
	{

		if (_boss.time % 15 == 0)
		{
			//BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle- 225), PATTRN2);
			//BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle -315), PATTRN2);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle + 120), PATTRN2);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle + 240), PATTRN2);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle), PATTRN2);
			_boss.angle -= 3;
		}
	}
	else if (_boss.time > 2100 && _boss.time < 3300)
	{
		if (_boss.time % 10 == 0)
		{
			_boss.angle += 5;
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle), PATTRN3);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle - 90), PATTRN3);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle - 180), PATTRN3);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle - 270), PATTRN3);

			_boss.angle2 -= 5;
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle2 - 45), PATTRN3);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle2 - 135), PATTRN3);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle2 - 225), PATTRN3);
			BOSSBULLETMANAGER->fire(_boss.x, _boss.y, DEGREE((int)_boss.angle2 - 315), PATTRN3);
		}
	}
	else if (_boss.time > 3400)
	{
		_boss.time = 0;
		_boss.angle = 270;
		//_boss.angle2 = 270;
	}
	
}

bool boss::bossColl(RECT rc , int _damage)
{
	RECT tmp;
	if (IntersectRect(&tmp , &rc , &_boss._rc))
	{
		_boss.hp -= _damage;
		//printf("보스 hp : %d\n", _boss.hp);

		return true;
	}
	return false;

	
}

void boss::anim()
{
	_boss._count++;
	_boss._explosion->setFrameY(0);
	if (_boss._count % 10 == 0)
	{

		if (_boss._index < 20)
		{
			_boss._index++;
		}
		else {
			_boss.isDie = false;
			
			_boss.x = WINSIZEX / 2;
			_boss.y = -100;
			init();
		}
		_boss._explosion->setFrameX(_boss._index);
	}
}
