#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	IMAGEMANAGER->addFrameImage("레벨업아이템", "image/attackItem.bmp", 260, 30, 6, 1);
	IMAGEMANAGER->addFrameImage("폭탄업아이템", "image/playerItemBomb.bmp", 550, 30, 11, 1);


	for (int i = 0; i < MAXITEM; i++)
	{
		tagItem _item;
		ZeroMemory(&_item, sizeof(tagItem));
		_item.img = IMAGEMANAGER->findImage("레벨업아이템");
		_item._count = 0;
		_item._index = 0;
		_item.angle = 0;
		_item.width = _item.img->getFrameWidth();
		_item.height = _item.img->getFrameHeight();
		_item.isActive = false;
		_item.speed = 2.0f;
		_item.time = 0;

		v_levelItem.emplace_back(_item);

		tagItem _item2;
		ZeroMemory(&_item2, sizeof(tagItem));
		_item2.img = IMAGEMANAGER->findImage("폭탄업아이템");
		_item2._count = 0;
		_item2._index = 0;
		_item2.angle = 0;
		_item2.width = _item2.img->getFrameWidth();
		_item2.height = _item2.img->getFrameHeight();
		_item2.isActive = false;
		_item2.speed = 2.0f;
		_item.time = 0;

		v_ultiItem.emplace_back(_item2);
	}
	
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	itemMove();
	anim();
	itemOut();
}

void itemManager::render(HDC hdc)
{

	for (int i = 0; i < v_levelItem.size(); i++)
	{
		if (!v_levelItem[i].isActive) continue;
		v_levelItem[i].img->frameRender(hdc, v_levelItem[i].x, v_levelItem[i].y);
	}

	for (int i = 0; i < v_ultiItem.size(); i++)
	{
		if (!v_ultiItem[i].isActive) continue;
		v_ultiItem[i].img->frameRender(hdc, v_ultiItem[i].x, v_ultiItem[i].y);
	}
}

void itemManager::itemMove()
{
	for (int i = 0; i < v_levelItem.size(); i++)
	{
		if (!v_levelItem[i].isActive) continue;
		v_levelItem[i].x += cosf(v_levelItem[i].angle) * v_levelItem[i].speed;
		v_levelItem[i].y += -sinf(v_levelItem[i].angle) * v_levelItem[i].speed;
		v_levelItem[i].rc = RectMakeCenter(v_levelItem[i].x + v_levelItem[i].width / 2, v_levelItem[i].y + v_levelItem[i].height / 2, v_levelItem[i].width / 2, v_levelItem[i].height / 2);
		v_levelItem[i].time++;
		if (v_levelItem[i].time % 600 == 0) v_levelItem[i].isActive = false;
	}

	for (int i = 0; i < v_ultiItem.size(); i++)
	{
		if (!v_ultiItem[i].isActive) continue;
		v_ultiItem[i].x += cosf(v_ultiItem[i].angle) * v_ultiItem[i].speed;
		v_ultiItem[i].y += -sinf(v_ultiItem[i].angle) * v_ultiItem[i].speed;
		v_ultiItem[i].rc = RectMakeCenter(v_ultiItem[i].x + v_ultiItem[i].width / 2, v_ultiItem[i].y + v_ultiItem[i].height / 2, v_ultiItem[i].width / 2, v_ultiItem[i].height / 2);
		v_ultiItem[i].time++;
		if (v_ultiItem[i].time % 600 == 0) v_ultiItem[i].isActive = false;
	}
}

void itemManager::anim()
{

	for (int i = 0; i < v_levelItem.size(); i++)
	{
		if (!v_levelItem[i].isActive) continue;
		v_levelItem[i]._count++;
		v_levelItem[i].img->setFrameY(0);
		if (v_levelItem[i]._count % 20 == 0)
		{
			v_levelItem[i]._index++;
			if (v_levelItem[i]._index > 6)
			{
				v_levelItem[i]._index = 0;
			}
			v_levelItem[i].img->setFrameX(v_levelItem[i]._index);
		}
	}
	for (int i = 0; i < v_ultiItem.size(); i++)
	{
		if (!v_ultiItem[i].isActive) continue;
		v_ultiItem[i]._count++;
		v_ultiItem[i].img->setFrameY(0);
		if (v_ultiItem[i]._count % 20 == 0)
		{
			v_ultiItem[i]._index++;
			if (v_ultiItem[i]._index > 11)
			{
				v_ultiItem[i]._index = 0;
			}
			v_ultiItem[i].img->setFrameX(v_ultiItem[i]._index);
		}
	}
	
}

void itemManager::active(float x, float y, float angle, ITEMKIND kind)
{
	switch (kind)
	{
	case LEVLEUPITEM:
		for (int i = 0; i < v_levelItem.size(); i++)
		{
			if (v_levelItem[i].isActive) continue;
			
			v_levelItem[i].x = x;
			v_levelItem[i].y = y;
			v_levelItem[i].angle = angle;
			v_levelItem[i].isActive = true;
			v_levelItem[i].time = 0;
			break;
		}
		break;
	case ULTIMATEITEM:
		for (int i = 0; i < v_ultiItem.size(); i++)
		{
			if (v_ultiItem[i].isActive) continue;

			v_ultiItem[i].x = x;
			v_ultiItem[i].y = y;
			v_ultiItem[i].angle = angle;
			v_ultiItem[i].isActive = true;
			v_ultiItem[i].time = 0;
			break;
		}
		break;
	default:
		break;
	}
}

pair<bool, ITEMKIND> itemManager::collision(RECT p_rc)
{
	RECT tmp;
	for (int i = 0; i < v_levelItem.size(); i++)
	{
		if (!v_levelItem[i].isActive) continue;
		if (IntersectRect(&tmp , &p_rc , &v_levelItem[i].rc))
		{
			v_levelItem[i].isActive = false;
			return make_pair(true, LEVLEUPITEM);
		}
	}

	for (int i = 0; i < v_ultiItem.size(); i++)
	{
		if (!v_ultiItem[i].isActive) continue;
		if (IntersectRect(&tmp, &p_rc, &v_ultiItem[i].rc))
		{
			v_ultiItem[i].isActive = false;
			return make_pair(true, ULTIMATEITEM);
		}
	}

	return make_pair(false, NONE);
}

void itemManager::itemOut()
{
	for (int i = 0; i < v_levelItem.size(); i++)
	{

		if (v_levelItem[i].x < 0) {
			v_levelItem[i].x++;
			v_levelItem[i].angle = 3.141592 - v_levelItem[i].angle;
		}
		if (v_levelItem[i].x + v_levelItem[i].width > WINSIZEX)
		{
			v_levelItem[i].x--;
			v_levelItem[i].angle = 3.141592 - v_levelItem[i].angle;
		}
		if (v_levelItem[i].y < 0)
		{
			v_levelItem[i].y++;
			v_levelItem[i].angle = 2 * 3.141592 - v_levelItem[i].angle;
		}
		if (v_levelItem[i].y + v_levelItem[i].height > WINSIZEY)
		{
			v_levelItem[i].y--;
			v_levelItem[i].angle = 2 * 3.141592 - v_levelItem[i].angle;
		}
	}
	for (int i = 0; i < v_ultiItem.size(); i++)
	{

		if (v_ultiItem[i].x < 0) {
			v_ultiItem[i].x++;
			v_ultiItem[i].angle = 3.141592 - v_ultiItem[i].angle;
		}
		if (v_ultiItem[i].x + v_ultiItem[i].width > WINSIZEX)
		{
			v_ultiItem[i].x--;
			v_ultiItem[i].angle = 3.141592 - v_ultiItem[i].angle;
		}
		if (v_ultiItem[i].y < 0)
		{
			v_ultiItem[i].y++;
			v_ultiItem[i].angle = 2 * 3.141592 - v_ultiItem[i].angle;
		}
		if (v_ultiItem[i].y + v_levelItem[i].height > WINSIZEY)
		{
			v_ultiItem[i].y--;
			v_ultiItem[i].angle = 2 * 3.141592 - v_ultiItem[i].angle;
		}
	}
}
