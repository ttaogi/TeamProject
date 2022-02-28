#pragma once
#include "Enemy.h"

class Necrodancer : public Enemy
{
private:
	float turnCount;
	bool posCheck;

	bool rightIdleTF;
	bool leftIdleTF;

	bool rightUpJump;
	bool rightDownJump;
	bool leftUpJump;
	bool leftDownJump;
	bool explosion;

	bool countTF;
	bool countTF2;

	int rightCount;
	int leftCount;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);
	void move(void);

	Necrodancer() { }
	~Necrodancer() { }
};

