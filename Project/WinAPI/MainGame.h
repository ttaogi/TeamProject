#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	std::string nextSceneKey;
	bool quit;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void quitGame();
	void setNextScene(std::string _nextSceneKey);

	MainGame() {}
	~MainGame() {}
};

