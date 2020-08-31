#include "stdafx.h"
#include "rocketManager.h"

HRESULT rocketManager::init(int level)
{
	IMAGEMANAGER->addFrameImage("rocket", "image/rocket.bmp", 120, 41, 4, 1);
	//IMAGEMANAGER->addImage("rocket", "playerBombCount.bmp", 30, 41);

	currentLevel = level;
	cout << currentLevel; 
	for (int i = 0; i < currentLevel; i++)
	{
		tagRocket bul;
		ZeroMemory(&bul, sizeof(tagRocket));
		//bul.angle = 0;
		bul.img = IMAGEMANAGER->findImage("rocket");
		bul.isFire = false;
		bul.speed = 10.0f;
		bul.x = WINSIZEX / 2;
		bul.y = WINSIZEY;
		bul._count = 0;
		bul._index = 0;
		bul.targetX = 0;
		bul.targetY = 0;
		bul.angle = 0;
		v_bullet.push_back(bul);
	}
	targetX = 0;
	targetY = 0;
	distance = 65535;
	
	_bossRC.left = WINSIZEX/2;
	_bossRC.top = 100;
	return S_OK;
}

void rocketManager::release()
{
	v_bullet.clear();
}

void rocketManager::update()
{
	anim();
	bulletOut();
}

void rocketManager::render(HDC hdc)
{
	for (int i = 0; i < v_bullet.size(); i++)
	{
		if (!v_bullet[i].isFire) continue;
		v_bullet[i].img->frameRender(hdc, v_bullet[i].x, v_bullet[i].y);
		//Rectangle(hdc, v_bullet[i]._rc);
	}
}

void rocketManager::fire(float p_x, float p_y , float p_angle)
{
	for (int i = 0; i < v_bullet.size(); i++)
	{
		if (v_bullet[i].isFire) continue;

		v_bullet[i].x = p_x;
		v_bullet[i].y = p_y;
		v_bullet[i].angle = p_angle;
		v_bullet[i]._rc = RectMakeCenter(v_bullet[i].x, v_bullet[i].y, v_bullet[i].img->getFrameWidth(), v_bullet[i].img->getFrameHeight());

		v_bullet[i].isFire = true;

		break;

	}
}

void rocketManager::bulletMove(vector<tagEnemy>& v)
{
	for (int i = 0 ; i < v_bullet.size();i++)
	{
		if (!v_bullet[i].isFire) continue;
			float tmpDis, enemyCenterX = 0, enemyCenterY = 0;
			float dis = GetDistance(v_bullet[i].x, v_bullet[i].y, _bossRC.left, _bossRC.top);
			enemyCenterX = _bossRC.left;
			enemyCenterY = _bossRC.top;
			tmpDis = 5000;
			
			
			for (int j = 0; j < v.size(); j++)
			{
				if (!v[j].isActive) continue; 
					dis = GetDistance(v_bullet[i].x, v_bullet[i].y, v[j]._rc.left, v[j]._rc.top);
					if (tmpDis > dis) {
						tmpDis = dis;
						enemyCenterX = v[j]._rc.left;
						enemyCenterY = v[j]._rc.top;
						
					}
					
				if (v_bullet[i].angle < -atan2f(enemyCenterY - v_bullet[i].y, enemyCenterX - v_bullet[i].x)) {
					v_bullet[i].angle += 0.08f;
					
					
				}
				else if (v_bullet[i].angle > -atan2f(enemyCenterY - v_bullet[i].y, enemyCenterX - v_bullet[i].x))
				{
					v_bullet[i].angle -= 0.08f;
					
				}
				
			}
			v_bullet[i].x += cosf(v_bullet[i].angle) * v_bullet[i].speed;
			v_bullet[i].y += -sinf(v_bullet[i].angle) * v_bullet[i].speed;

			v_bullet[i]._rc = RectMakeCenter(v_bullet[i].x + v_bullet[i].img->getFrameWidth() / 2,
				v_bullet[i].y + v_bullet[i].img->getFrameHeight() / 2, v_bullet[i].img->getFrameWidth(),
				v_bullet[i].img->getFrameHeight());
	}
	

}

void rocketManager::anim()
{
	for (int i = 0; i < v_bullet.size(); i++)
	{
		if (!v_bullet[i].isFire) continue;

		v_bullet[i]._count++;
		v_bullet[i].img->setFrameY(0);
		if (v_bullet[i]._count % 10 == 0)
		{
			if (v_bullet[i]._index < 4)
			{
				v_bullet[i]._index++;
			}
			v_bullet[i].img->setFrameX(v_bullet[i]._index);
		}
	}
}

void rocketManager::bulletOut()
{
	for (int i = 0; i < v_bullet.size(); i++)
	{
		if (!v_bullet[i].isFire) continue;
		if (v_bullet[i].y < 0) v_bullet[i].isFire = false;
	}
}

bool rocketManager::coll(RECT _rc)
{
	RECT tmp;
	for (int i = 0; i < v_bullet.size(); i++)
	{
		if (!v_bullet[i].isFire) continue;

		if (IntersectRect(&tmp , &_rc , &v_bullet[i]._rc))
		{
		    v_bullet[i].isFire = false;

		return true;
		}
	}

	return false;
}

void rocketManager::getBossPos(RECT _rc)
{
	_bossRC = _rc;
}
