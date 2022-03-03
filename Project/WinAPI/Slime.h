#pragma once

#include "Enemy.h"


class Slime : public Enemy
{
private:
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);
	
	Slime() { }
	virtual ~Slime() { release(); }
};

