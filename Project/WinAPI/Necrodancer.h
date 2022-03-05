#pragma once
#include "Enemy.h"

class Necrodancer : public Enemy
{
private:
	RECT _Hp_rc;

	Image* _FullHp;
	Image* _EmptyHp;

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

	int count;


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

