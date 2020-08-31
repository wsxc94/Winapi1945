#include "stdafx.h"
#include "Phoenix.h"

HRESULT Phoenix::init()
{
	IMAGEMANAGER->addFrameImage("피닉스", "image/ulti2.bmp", 1380, 245, 8, 1);
	img = IMAGEMANAGER->findImage("피닉스");

	speed = 7.0f;
	isFire = false;
	_count = 0;
	_index = 0;


	return S_OK;
}

void Phoenix::release()
{

}

void Phoenix::update()
{
	bulletMove();
	bulletOut();
	anim();
}

void Phoenix::render()
{
	if (isFire)
	{
		img->frameRender(getMemDC(), _x - img->getFrameWidth()/2 + 30, _y- img->getFrameHeight() / 2 + 30);
		//Rectangle(getMemDC(), _rc);
	}
}

void Phoenix::fire(float x, float y)
{
	_count = 0;
	_index = 0;
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x + 30, _y + 30, img->getFrameWidth(), img->getFrameHeight());
	isFire = true;
}

void Phoenix::bulletMove()
{
	_y -= speed;
	_rc = RectMakeCenter(_x+ 30, _y+ 30, img->getFrameWidth(), img->getFrameHeight());
}

void Phoenix::anim()
{
	if (isFire)
	{
		_count++;
		img->setFrameY(0);
		if (_count % 5 == 0)
		{
			if (_index < 8)
			{
				_index++;

			}
			img->setFrameX(_index);
		}
	}
}

void Phoenix::bulletOut()
{
	if (_y < 0) isFire = false;

}
