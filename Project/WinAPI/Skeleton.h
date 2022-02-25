#pragma once
#include "Enemy.h"
#include "Animator.h"

class Skeleton : public Enemy
{
private:
	float turnCount;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	void move(void);

	Skeleton() { }
	~Skeleton() { }
};

