#pragma once
#include "GameNode.h"

class Animator;

class Player : public GameNode
{
private:
	int hp;
	float initTime;
	float turnCount;
	DIRECTION command;
	RECT rc;
	Animator* headAnimator;
	Animator* bodyAnimator;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void Move(POINT _pos);

	Player() { }
	~Player() { }
};