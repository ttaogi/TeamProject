#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	bool quit;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}

	void quitGame();
};

