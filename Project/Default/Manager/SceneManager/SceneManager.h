#pragma once

#include <functional>
#include <vector>
#include <windef.h>

#include "Utility/Enums.h"

class GameObject;
class Image;
class MainGame;

class SceneManager
{
protected:
	SCENE_TYPE scnType;
	Image* backgroundImage;
	std::vector<GameObject*> gameObjects;
public:
	SceneManager(SCENE_TYPE _scnType)
	{
		scnType = _scnType;
		backgroundImage = NULL;
	}
	~SceneManager() {}

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual SCENE_TYPE GetSceneType() { return scnType; }
};