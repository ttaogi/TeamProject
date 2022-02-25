#pragma once

#include "Scene.h"

class StartScene : public Scene
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