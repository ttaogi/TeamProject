#pragma once

#include "Enemy.h"


class Slime : public Enemy
{
private:
	float turnCount;
	float attackDelay;
	float atkRange;
	float fieldOfVision;
	float distanceX;
	float distanceY;

	bool posCheck;
	bool act;

	Animator* atk_animator;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	void attackTarget();
	
	Slime() {}
	virtual ~Slime() {}
};

