#pragma once

#include "Scene.h"

class Object;
class Player;
class Slime;
class SlimeBlue;

class LobbyScene : public Scene
{
private:
	Slime* slime;
	SlimeBlue* slimeBlue;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	~LobbyScene() {}
};