#pragma once
#include "singletonBase.h"
#include "image.h"

enum ITEMKIND{
	NONE,
	LEVLEUPITEM,
	ULTIMATEITEM
};
struct tagItem
{
	image* img;
	int _count;
	int _index;
	float x;
	float y;
	float angle;
	RECT rc;
	bool isActive;
	int width;
	int height;
	float speed;
	int time;

};

class itemManager : public singletonBase<itemManager>
{
private:
	enum{MAXITEM = 10};
	vector<tagItem> v_levelItem;
	vector<tagItem> v_ultiItem;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void itemMove();
	void anim();
	void active(float x, float y, float angle , ITEMKIND kind);
	pair<bool, ITEMKIND> collision(RECT p_rc);
	void itemOut();

	itemManager() {}
	~itemManager() {}
};

