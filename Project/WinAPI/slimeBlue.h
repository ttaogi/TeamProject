#pragma once
#include "Enemy.h"

class SlimeBlue : public Enemy
{
private:
	RECT _Hp_rc;

	Image* _FullHp;
	Image* _EmptyHp;

	float turnCount;
	bool posCheck;
	int count;
	int index;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);
	void move(void);

	SlimeBlue() { }
	virtual ~SlimeBlue() { }
};

