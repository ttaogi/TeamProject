#pragma once

#include "Object.h"

//Enemy (�θ� Ŭ����): �� Ŭ������ ������� ����, �Ϲ� ���͵��� ����ٰ� ������ ������ ������ �����Ҷ� �����ϰ� ����°� ����
class Enemy : public Object
{
protected:
	int hp;
	RECT _rc;
public:
	virtual HRESULT init(Scene* scenePtr, POINT position) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	virtual bool interact(Player* player) = 0;

	void move(POINT _pos);

	RECT getRect(void) { return _rc; }

	Enemy(void) { }
	~Enemy(void) { }
};

