#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	IMAGEMANAGER->addImage("利厚青扁", "image/enemy.bmp", 104, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("利秋扁", "image/enemy1.bmp", 50, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("利气惯", "image/enemyExplosion.bmp", 350, 44, 8, 1);
	time = 0;
	responCnt = 0; // enemy1
	responCheck = false; // enemy1
	rectView = false;
	string a1[2] = { "利厚青扁", "利秋扁" };

	for (int i = 0; i < MAXENEMY; i++)
	{
		int rand = 0;
		if (i % 2 == 0)
			rand = 1;
		
		tagEnemy _enemy1;

		ZeroMemory(&_enemy1, sizeof(tagEnemy));
		
		if (rand == 0)
		{
			_enemy1.width = 104;
			_enemy1.height = 68;
		}
		else {
			_enemy1.width = 50;
			_enemy1.height = 70;
		}
		_enemy1.isActive = false;
		_enemy1._img = IMAGEMANAGER->findImage(a1[rand]);
		_enemy1._explosion = IMAGEMANAGER->findImage("利气惯");
		_enemy1.speed = 2.0f;
		_enemy1.isDie = false;
		_enemy1.e_count = 0;
		_enemy1.e_index = 0;
		_enemy1.e_move = RANDOM->range(0,1);
		v_enemy.emplace_back(_enemy1);
	}
	enemy_bullet = new e_bullet;
	enemy_bullet->init();

	return S_OK;
}

void enemy::release()
{
	enemy_bullet->release();
	SAFE_DELETE(enemy_bullet);
}

void enemy::update()
{
	time++;

	ROCKETMANAGER->bulletMove(v_enemy);

	if (time % 200 == 0)
	{
		create();
	}
	if (time % 500 == 0)
	{
		enemy1create();
	}
	enemyMove();
	enemy_bullet->update();
	enemyFire();
	enemyOut();
	animation();
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

void enemy::render()
{

	for (int i = 0; i < MAXENEMY; i++)
	{

		if (!v_enemy[i].isActive) continue;

		v_enemy[i]._img->render(getMemDC(), v_enemy[i]._rc.left, v_enemy[i]._rc.top);
		
		enemy_bullet->render();


		if (rectView)
		{
			Rectangle(getMemDC(), v_enemy[i]._rc);
		}
	}
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!v_enemy[i].isDie) continue;
		
		if(v_enemy[i].width == 104)
			v_enemy[i]._explosion->frameRender(getMemDC(), v_enemy[i]._rc.left + 30, v_enemy[i]._rc.top+20);
		else
		 v_enemy[i]._explosion->frameRender(getMemDC(), v_enemy[i]._rc.left, v_enemy[i]._rc.top);
		
	}
}

void enemy::animation()
{

	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!v_enemy[i].isDie) continue;
		
		v_enemy[i].e_count++;
			v_enemy[i]._explosion->setFrameY(0);
			if (v_enemy[i].e_count % 10 == 0)
			{

				if (v_enemy[i].e_index < 8)
				{
					v_enemy[i].e_index++;
				}
				else {
					v_enemy[i].isDie = false;
					v_enemy[i].e_count = 0;
					v_enemy[i].e_index = 0;


				}
				v_enemy[i]._explosion->setFrameX(v_enemy[i].e_index);
			}
		
	}
	
}

void enemy::create()
{

	for (int i = 0; i < MAXENEMY; i++)
	{
		if (v_enemy[i].isActive || i % 2 == 0) continue;

		v_enemy[i].isActive = true;
		v_enemy[i]._rc = RectMakeCenter(RANDOM->range(0,WINSIZEX - 50),RANDOM->range(-200,-10),v_enemy[i].width, v_enemy[i].height-20);
		break;
	}
}

void enemy::enemy1create()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
	
			if (v_enemy[i].isActive || i % 2 != 0) continue;

			v_enemy[i].isActive = true;

			if (responCheck)
			{
				v_enemy[i]._rc = RectMakeCenter(-50 * responCnt, -50 * responCnt, v_enemy[i].width, v_enemy[i].height - 20);
				responCnt++;
			}
			else {
				v_enemy[i]._rc = RectMakeCenter(WINSIZEX - 50 * responCnt, -50 * responCnt, v_enemy[i].width, v_enemy[i].height - 20);
				responCnt++;
			}


			if (responCnt > 4) {
				responCnt = 0;
				if (responCheck)
				{
					responCheck = false;
				}
				else {
					responCheck = true;
				}
				
				break;
			}
		
	}
}

void enemy::enemyOut()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!v_enemy[i].isActive) continue;
		RECT tmp;

		if (v_enemy[i]._rc.bottom > WINSIZEY )
		{
			v_enemy[i].isActive = false;

		}
	}

}

void enemy::enemyMove()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!v_enemy[i].isActive) continue;
		
		//ROCKETMANAGER->bulletMove(v_enemy[0]._rc.left, v_enemy[0]._rc.top);
		
		if (v_enemy[i].width == 104) {
			v_enemy[i]._rc.top += v_enemy[i].speed;
			v_enemy[i]._rc.bottom += v_enemy[i].speed;
		}
		else {
			v_enemy[i]._rc.top += v_enemy[i].speed;
			v_enemy[i]._rc.bottom += v_enemy[i].speed;

			if (v_enemy[i]._rc.left <= 0) {
				v_enemy[i].e_move = true;
			}
			else if(v_enemy[i]._rc.right > WINSIZEX-20){
				v_enemy[i].e_move = false;
				
			}
			if (v_enemy[i].e_move) {
				v_enemy[i]._rc.left += v_enemy[i].speed/2;
				v_enemy[i]._rc.right += v_enemy[i].speed/2;
			}
			else {
				v_enemy[i]._rc.left -= v_enemy[i].speed/2;
				v_enemy[i]._rc.right -= v_enemy[i].speed/2;
			}

		}
		
	}
	/*for (int i = 0; i < MAXENEMY; i++)
	{
		if (v_enemy[i].isActive)
		{
			ROCKETMANAGER->bulletMove(v_enemy[i]._rc.left, v_enemy[i]._rc.top);
			break;
		}
		else
		{
			ROCKETMANAGER->bulletMove(-999, -999);
		}
		
	}*/
}

void enemy::enemyFire()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!v_enemy[i].isActive) continue;

		if (time % 120 == 0) {
			enemy_bullet->fire(v_enemy[i]._rc.left + ((v_enemy[i].width /2) - 5), v_enemy[i]._rc.top);
		}
	}
}
