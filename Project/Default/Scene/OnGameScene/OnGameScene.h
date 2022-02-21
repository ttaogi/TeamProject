#pragma once

#include "Scene/Scene.h"

const static std::wstring NOTICE = L"Press Q to quit.";

class OnGameScene : public Scene
{
private:
	std::wstring msg;
	MapInfo* mapInfo;

	int alpha;
	int bgSpeed;
	int bgOffsetX;
	int bgOffsetY;
public:
	OnGameScene();
	~OnGameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};