#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init(int level)
{
	IMAGEMANAGER->addFrameImage("·¹º§1ÃÑ¾Ë", "image/playerAttack.bmp", 200, 85, 4, 1);
	IMAGEMANAGER->addFrameImage("·¹º§2ÃÑ¾Ë", "image/playerAttack2.bmp", 250, 104, 4, 1);
	IMAGEMANAGER->addFrameImage("·¹º§3ÃÑ¾Ë", "image/playerAttack3.bmp", 300, 128, 4, 1);

	currentLevel = level;
	rectView = false;
	//ZeroMemory(&bul, 0, sizeof(tagBullet));
	switch (currentLevel)
	{
	case 1:
		for (int i = 0; i < MAXBULLET; i++)
		{
			tagBullet bul;
			ZeroMemory(&bul, sizeof(tagBullet));
			bul.img = IMAGEMANAGER->findImage("·¹º§1ÃÑ¾Ë");
			bul.speed = 7.0f;
			bul.isFire = false;

			_vBullet.push_back(bul);
		}

		break;
	case 2:
		for (int i = 0; i < MAXBULLET; i++)
		{
			tagBullet bul;
			ZeroMemory(&bul, sizeof(tagBullet));
			bul.img = IMAGEMANAGER->findImage("·¹º§2ÃÑ¾Ë");
			bul.speed = 8.0f;
			bul.isFire = false;

			_vBullet.push_back(bul);
		}
		break;
	case 3:
		for (int i = 0; i < MAXBULLET; i++)
		{
			tagBullet bul;
			ZeroMemory(&bul, sizeof(tagBullet));
			bul.img = IMAGEMANAGER->findImage("·¹º§3ÃÑ¾Ë");
			bul.speed = 9.0f;
			bul.isFire = false;

			_vBullet.push_back(bul);
		}
		break;

	default:
		break;
	}
	
	b_count = b_index = 0;
	return S_OK;
}

void bullet::release()
{	
}

void bullet::update()
{
	bulletMove();
	//bulletOut();
	anim();
	bulletOut();
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
}

void bullet::render()
{

	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;
		if(currentLevel == 1)
		_vBullet[i].img->frameRender(getMemDC(), _vBullet[i]._rc.left - 12, _vBullet[i]._rc.top);
		else if(currentLevel == 2)
		_vBullet[i].img->frameRender(getMemDC(), _vBullet[i]._rc.left - 9, _vBullet[i]._rc.top);
		else
		_vBullet[i].img->frameRender(getMemDC(), _vBullet[i]._rc.left, _vBullet[i]._rc.top);
		if (rectView)
		{
			Rectangle(getMemDC(), _vBullet[i]._rc);
		}
	}
	

}

void bullet::fire(float p_x , float p_y)
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (_vBullet[i].isFire) continue;
		if (currentLevel == 1)
		{
			_vBullet[i]._rc = RectMakeCenter(p_x + 30, p_y - 30, _vBullet[i].img->getFrameWidth()/2, _vBullet[i].img->getFrameHeight() / 2);
		}
		else if(currentLevel == 2){
			_vBullet[i]._rc = RectMakeCenter(p_x + 30, p_y - 30, _vBullet[i].img->getFrameWidth() -15, _vBullet[i].img->getFrameHeight() / 2);
		}
		else {
			_vBullet[i]._rc = RectMakeCenter(p_x + 30, p_y - 30, _vBullet[i].img->getFrameWidth(), _vBullet[i].img->getFrameHeight() / 2);
		}
		
		_vBullet[i].isFire = true;
		break;
	}
}

void bullet::bulletMove()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;
		_vBullet[i]._rc.top -= _vBullet[i].speed;
		_vBullet[i]._rc.bottom -= _vBullet[i].speed;
	}
}

void bullet::anim()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;

		b_count++;
		_vBullet[i].img->setFrameY(0);
		if (b_count % 5 == 0)
		{

			if (b_index < 3)
			{
				b_index++;
			}
			_vBullet[i].img->setFrameX(b_index);
		}
	}
	
}

void bullet::bulletOut()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!_vBullet[i].isFire) continue;

		if (_vBullet[i]._rc.top < 0)
		{
			_vBullet[i].isFire = false;
		}
	}

}
