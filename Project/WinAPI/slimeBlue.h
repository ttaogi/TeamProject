#pragma once
#include "Enemy.h"

class SlimeBlue : public Enemy
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
	void move(void);

	void attackTarget();

	SlimeBlue() {}
	virtual ~SlimeBlue() {}
};

