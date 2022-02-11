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
	Image* backBuffer;
	MainGame* mg;
	std::vector<GameObject*> gameObjects;

	virtual void SetBackBuffer() = 0;
public:
	SceneManager(SCENE_TYPE _scnType, MainGame* _mg)
	{
		scnType = _scnType;
		mg = _mg;
		backBuffer = NULL;
	}
	~SceneManager() {}

	virtual void Init(MainGame* _mg) = 0;
	virtual void Update(HWND _hWnd) = 0;
	virtual void LateUpdate() = 0;
	virtual void Release() = 0;
	virtual void Render(HDC _hdc) = 0;

	virtual SCENE_TYPE GetSceneType() { return scnType; }

	Image* GetBackBuffer() { return backBuffer; }
};