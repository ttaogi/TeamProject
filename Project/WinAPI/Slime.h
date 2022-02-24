#pragma once
#include "Enemy.h"

class Slime : public Enemy
{
private:
	Image* slime;
	RECT rc;

	int count;
	int slimeIndex;

public:
	HRESULT init(void);
	HRESULT Slime::init(const char * imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);
	
	Slime();
	~Slime() {};

};

