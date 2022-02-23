#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	char _text[64];
	Image* background;
	Image* pressAnyKey;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StartScene() {}
	~StartScene() {}
};