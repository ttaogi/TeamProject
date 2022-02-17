#pragma once

#include "Manager/SceneManager/SceneManager.h"

const static std::wstring NOTICE = L"Press Q to quit.";

class OnGameSceneManager : public SceneManager
{
private:
	std::wstring msg;

	int alpha;
	int bgSpeed;
	int bgOffsetX;
	int bgOffsetY;
public:
	OnGameSceneManager();
	~OnGameSceneManager();

	void Init();
	void Release();
	void Update();
	void Render();
};