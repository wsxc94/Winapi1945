#include "stdafx.h"
#include "bossBulletManager.h"

HRESULT bossBulletManager::init()
{
	IMAGEMANAGER->addFrameImage("ÆÐÅÏ1ÃÑ¾Ë", "image/enemyBullets.bmp", 72, 20,6,1);
	IMAGEMANAGER->addFrameImage("ÆÐÅÏ2ÃÑ¾Ë", "image/enemyBullets2.bmp", 120, 20,9,1);
	IMAGEMANAGER->addImage("ÆÐÅÏ3ÃÑ¾Ë", "image/enemyJuneBossBullet.bmp", 18, 16, true, RGB(255, 0, 255));

	for (int i = 0; i < MAXBULLET_BOSS; i++)
	{
		tagBossBullet bul;
		ZeroMemory(&bul, sizeof(tagBossBullet));
		bul.img = IMAGEMANAGER->findImage("ÆÐÅÏ1ÃÑ¾Ë");
		bul.speed = 6.0f;
		bul.isFire = false;
		bul._count = 0;
		bul._index = 0;
		bul.width = bul.img->getFrameWidth();
		bul.height = bul.img->getFrameHeight();
		v_BossBullet.push_back(bul);
	}
	for (int i = 0; i < MAXBULLET_BOSS; i++)
	{
		tagBossBullet bul;
		ZeroMemory(&bul, sizeof(tagBossBullet));
		bul.img = IMAGEMANAGER->findImage("ÆÐÅÏ2ÃÑ¾Ë");
		bul.speed = 6.0f;
		bul.isFire = false;
		bul._count = 0;
		bul._index = 0;
		bul.width = bul.img->getFrameWidth();
		bul.height = bul.img->getFrameHeight();
		v_BossBullet2.push_back(bul);
	}
	for (int i = 0; i < MAXBULLET_BOSS; i++)
	{
		tagBossBullet bul;
		ZeroMemory(&bul, sizeof(tagBossBullet));
		bul.img = IMAGEMANAGER->findImage("ÆÐÅÏ3ÃÑ¾Ë");
		bul.speed = 6.0f;
		bul.isFire = false;
		bul._count = 0;
		bul._index = 0;
		bul.width = bul.img->getFrameWidth();
		bul.height = bul.img->getFrameHeight();
		v_BossBullet3.push_back(bul);
	}
	
	return S_OK;
}

void bossBulletManager::release()
{
}

void bossBulletManager::update()
{
	bulletMove();
	bulletOut();
}

void bossBulletManager::render(HDC hdc)
{
	for (int i = 0; i < v_BossBullet.size(); i++)
	{
		if (!v_BossBullet[i].isFire) continue;
		v_BossBullet[i].img->frameRender(hdc, v_BossBullet[i].x, v_BossBullet[i].y);
		//Rectangle(hdc, v_BossBullet[i]._rc);
	}

	for (int i = 0; i < v_BossBullet2.size(); i++)
	{
		if (!v_BossBullet2[i].isFire) continue;
		v_BossBullet2[i].img->frameRender(hdc, v_BossBullet2[i].x, v_BossBullet2[i].y);
		//Rectangle(hdc, v_BossBullet2[i]._rc);
	}

	for (int i = 0; i < v_BossBullet3.size(); i++)
	{
		if (!v_BossBullet3[i].isFire) continue;
		v_BossBullet3[i].img->render(hdc, v_BossBullet3[i].x, v_BossBullet3[i].y);
		//Rectangle(hdc, v_BossBullet3[i]._rc);
	}
}

void bossBulletManager::fire(float p_x, float p_y, float angle , PATTRN pt)
{
	switch (pt)
	{
	case PATTRN1:
		for (int i = 0; i < v_BossBullet.size(); i++)
		{
			if (v_BossBullet[i].isFire) continue;
			
			v_BossBullet[i].x = p_x;
			v_BossBullet[i].y = p_y;
			v_BossBullet[i].angle = angle;
			v_BossBullet[i].isFire = true;
			break;

		}
		break;
	case PATTRN2:
		for (int i = 0; i < v_BossBullet2.size(); i++)
		{
			if (v_BossBullet2[i].isFire) continue;
			v_BossBullet2[i].x = p_x;
			v_BossBullet2[i].y = p_y;
			v_BossBullet2[i].angle = angle;
			v_BossBullet2[i].isFire = true;
			break;
		}
		break;
	case PATTRN3:
		for (int i = 0; i < v_BossBullet3.size(); i++)
		{
			if (v_BossBullet3[i].isFire) continue;
			v_BossBullet3[i].x = p_x;
			v_BossBullet3[i].y = p_y;
			v_BossBullet3[i].angle = angle;
			v_BossBullet3[i].isFire = true;
			break;
		}
		break;
	default:
		break;
	}
	
}

void bossBulletManager::bulletMove()
{
	for (int i = 0; i < v_BossBullet.size(); i++)
	{
		if (!v_BossBullet[i].isFire) continue;

		v_BossBullet[i].x += cosf(v_BossBullet[i].angle)* v_BossBullet[i].speed;
		v_BossBullet[i].y += -sinf(v_BossBullet[i].angle) * v_BossBullet[i].speed;
		v_BossBullet[i]._rc = RectMakeCenter(v_BossBullet[i].x + v_BossBullet[i].width / 2, v_BossBullet[i].y + v_BossBullet[i].height / 2, v_BossBullet[i].width / 2, v_BossBullet[i].height / 2);
	}
	for (int i = 0; i < v_BossBullet2.size(); i++)
	{
		if (!v_BossBullet2[i].isFire) continue;

		v_BossBullet2[i].x += cosf(v_BossBullet2[i].angle)* v_BossBullet2[i].speed;
		v_BossBullet2[i].y += -sinf(v_BossBullet2[i].angle) * v_BossBullet2[i].speed;
		v_BossBullet2[i]._rc = RectMakeCenter(v_BossBullet2[i].x + v_BossBullet2[i].width / 2, v_BossBullet2[i].y + v_BossBullet2[i].height / 2, v_BossBullet2[i].width / 2, v_BossBullet2[i].height / 2);
	}
	for (int i = 0; i < v_BossBullet3.size(); i++)
	{
		if (!v_BossBullet3[i].isFire) continue;

		v_BossBullet3[i].x += cosf(v_BossBullet3[i].angle)* v_BossBullet3[i].speed;
		v_BossBullet3[i].y += -sinf(v_BossBullet3[i].angle) * v_BossBullet3[i].speed;
		v_BossBullet3[i]._rc = RectMakeCenter(v_BossBullet3[i].x + 8, v_BossBullet3[i].y + 8, 10, 10);
	}

}

void bossBulletManager::anim()
{
	for (int i = 0; i < v_BossBullet.size(); i++)
	{
		if (!v_BossBullet[i].isFire) continue;
		v_BossBullet[i]._count++;
		v_BossBullet[i].img->setFrameY(0);
		if (v_BossBullet[i]._count % 30 == 0)
		{
			v_BossBullet[i]._index++;
			if (v_BossBullet[i]._index > 6)
			{
				v_BossBullet[i]._index = 0;
			}
			v_BossBullet[i].img->setFrameX(v_BossBullet[i]._index);
		}
	}
	for (int i = 0; i < v_BossBullet2.size(); i++)
	{
		if (!v_BossBullet2[i].isFire) continue;
		v_BossBullet2[i]._count++;
		v_BossBullet2[i].img->setFrameY(0);
		if (v_BossBullet2[i]._count % 20 == 0)
		{
			v_BossBullet2[i]._index++;
			if (v_BossBullet2[i]._index > 9)
			{
				v_BossBullet2[i]._index = 0;
			}
			v_BossBullet2[i].img->setFrameX(v_BossBullet2[i]._index);
		}
	}

}

void bossBulletManager::bulletOut()
{
	for (int i = 0; i < v_BossBullet.size(); i++)
	{
		if (v_BossBullet[i].x > WINSIZEX || v_BossBullet[i].x < 0 ||
			v_BossBullet[i].y > WINSIZEY || v_BossBullet[i].y < 0) {
			v_BossBullet[i].isFire = false;
			v_BossBullet[i]._count = 0;
			v_BossBullet[i]._index = 0;
		}
	}
	for (int i = 0; i < v_BossBullet2.size(); i++)
	{
		if (v_BossBullet2[i].x > WINSIZEX || v_BossBullet2[i].x < 0 ||
			v_BossBullet2[i].y > WINSIZEY || v_BossBullet2[i].y < 0) {
			v_BossBullet2[i].isFire = false;
			v_BossBullet2[i]._count = 0;
			v_BossBullet2[i]._index = 0;
		}
	}
	for (int i = 0; i < v_BossBullet3.size(); i++)
	{
		if (v_BossBullet3[i].x > WINSIZEX || v_BossBullet3[i].x < 0 ||
			v_BossBullet3[i].y > WINSIZEY || v_BossBullet3[i].y < 0) {
			v_BossBullet3[i].isFire = false;
			//cout << "ÇØÁ¦" << endl;
		}
	}
	
}

bool bossBulletManager::collision(RECT p_rc)
{
	RECT tmp;
	for (int i = 0; i < v_BossBullet.size(); i++)
	{
		if (!v_BossBullet[i].isFire) continue;
		if (IntersectRect(&tmp , &v_BossBullet[i]._rc , &p_rc))
		{
			v_BossBullet[i].isFire = false;
			return true;
		}
	}
	for (int i = 0; i < v_BossBullet2.size(); i++)
	{
		if (!v_BossBullet2[i].isFire) continue;
		if (IntersectRect(&tmp, &v_BossBullet2[i]._rc, &p_rc))
		{
			v_BossBullet2[i].isFire = false;
			return true;
		}
	}
	for (int i = 0; i < v_BossBullet3.size(); i++)
	{
		if (!v_BossBullet3[i].isFire) continue;
		if (IntersectRect(&tmp, &v_BossBullet3[i]._rc, &p_rc))
		{
			v_BossBullet3[i].isFire = false;
			return true;
		}
	}

	return false;
}
