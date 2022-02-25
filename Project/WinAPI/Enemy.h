#pragma once

#include "Object.h"

//Enemy (부모 클래스): 이 클래스를 기반으로 보스, 일반 몬스터등을 만든다고 했을때 문제가 없는지 설계할때 생각하고 만드는게 좋다
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

