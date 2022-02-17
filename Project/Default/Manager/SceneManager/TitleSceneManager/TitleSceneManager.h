#pragma once

#include "Manager/SceneManager/SceneManager.h"

class TitleSceneManager : public SceneManager {
private:
public:
	TitleSceneManager();
	~TitleSceneManager() {}

	void Init();
	void Release();
	void Update();
	void Render();
};