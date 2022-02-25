#pragma once

#include "Enemy.h"

class SlimeBlue : public Enemy
{
private:
	float turnCount;
	int count;
	bool posCheck;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	SlimeBlue() { }
	~SlimeBlue() { }

};

