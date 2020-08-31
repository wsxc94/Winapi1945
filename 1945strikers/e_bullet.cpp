#include "stdafx.h"
#include "e_bullet.h"

HRESULT e_bullet::init()
{
	IMAGEMANAGER->addImage("ÀûÃÑ¾Ë", "image/enemyBullet.bmp", 12, 10, true, RGB(255, 0, 255));
    rectView = false;
	//ZeroMemory(&bul, 0, sizeof(tagBullet));
	for (int i = 0; i < MAXBULLET; i++)
	{
		tagBullet bul;
		ZeroMemory(&bul, sizeof(tagBullet));
		bul.img = IMAGEMANAGER->findImage("ÀûÃÑ¾Ë");
		bul.speed = 6.0f;
		bul.isFire = false;

		_vBullet.push_back(bul);
	}
	return S_OK;
}

void e_bullet::release()
{
}

void e_bullet::update()
{
	bulletMove();
	bulletOut();
	/*if (INPUT->GetKeyDown(VK_F1))
	{
		if (rectView)
		{
			rectView = false;
		}
		else {
			rectView = true;
		}
	}*/
}

void e_bullet::render()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;
		_vBullet[i].img->render(getMemDC(), _vBullet[i]._rc.left, _vBullet[i]._rc.top);
		if (rectView)
		{
			Rectangle(getMemDC(), _vBullet[i]._rc);
		}
	}
}

void e_bullet::fire(float p_x, float p_y)
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (_vBullet[i].isFire) continue;
		_vBullet[i]._rc = RectMakeCenter(p_x+5, p_y + 50, 15, 10);
		_vBullet[i].isFire = true;
		break;
	}
}



void e_bullet::bulletMove()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;
		int rand = RANDOM->range(-5, 5);
		_vBullet[i]._rc.left += rand /2;
		_vBullet[i]._rc.right += rand /2;
		_vBullet[i]._rc.top += _vBullet[i].speed;
		_vBullet[i]._rc.bottom += _vBullet[i].speed;
	}
}

void e_bullet::anim()
{
}

void e_bullet::bulletOut()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;

		RECT tmp;
		if (_vBullet[i]._rc.bottom > WINSIZEY)
		{
			_vBullet[i].isFire = false;
		}
	}
}
