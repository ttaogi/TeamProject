#pragma once
#include "Enemy.h"
#include "Animator.h"

class Slime : public Enemy
{
private:
	float turnCount;
	int count;

	bool posCheck;

	Animator* slimeJumpAnimator;

	RECT rc;
public:
	HRESULT init(void);
	HRESULT Slime::init(const char * imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);
	
	Slime();
	~Slime() {};

};

