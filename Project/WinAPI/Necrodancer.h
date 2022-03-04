#pragma once
#include "Enemy.h"

class Necrodancer : public Enemy
{
private:
	float turnCount;
	int globalCool;
	int summonCool;
	int freezeCool;
	int explosionCool;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	void moveRandom();
	void summon();
	void freeze();
	void explosion();

	Necrodancer() { }
	~Necrodancer() { }
};
