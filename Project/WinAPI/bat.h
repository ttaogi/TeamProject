#pragma once
#include "Enemy.h"

class Bat : public Enemy
{
private:
	float turnCount;
	bool posCheck;
	
	int rightCount;
	int leftCount;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);
	void move(void);

	Bat() { }
	~Bat() { }
};

