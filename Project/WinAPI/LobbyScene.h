#pragma once

#include "Scene.h"

class Object;
class Player;
class Slime;

class LobbyScene : public Scene
{
private:
	Slime* slime;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	LobbyScene() {}
	~LobbyScene() {}
};