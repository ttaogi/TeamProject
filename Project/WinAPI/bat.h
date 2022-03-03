#pragma once
#include "Enemy.h"

class Bat : public Enemy
{
private:
	RECT _Hp_rc;

	Image* _FullHp;
	Image* _EmptyHp;

	float turnCount;
	bool posCheck;
	
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

	Bat() { }
	virtual ~Bat() { }
};

