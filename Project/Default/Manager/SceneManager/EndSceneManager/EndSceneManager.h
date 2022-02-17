#pragma once

#include "Manager/SceneManager/SceneManager.h"

class EndSceneManager : public SceneManager
{
private:
public:
	EndSceneManager();
	~EndSceneManager();

	void Init();
	void Update();
	void Release();
	void Render();
};