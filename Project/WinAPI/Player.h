#pragma once
#include "GameNode.h"

class Player : public GameNode
{
private:
	int hp;
	float initTime;
	float turnCount;
	DIRECTION command;
	RECT rc;
	Image* head;
	Image* body;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void Move(POINT _pos);

	Player() { }
	~Player() { }
};