#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
private:
	float turnCount;
	bool posCheck;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);
	void move(void);

	Skeleton() { }
	virtual ~Skeleton() { }
};

