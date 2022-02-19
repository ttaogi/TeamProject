#pragma once

#include <vector>
#include <windef.h>

#include "Utility/Enums.h"

class GameObject;
class Image;
class MainGame;

class Scene
{
protected:
	Image* backgroundImage;
	std::vector<GameObject*> gameObjects;
public:
	Scene() { }
	~Scene() { }

	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};