#pragma once

#include "Manager/SceneManager/SceneManager.h"
#include "Player/Player.h"

#define BUTTON_WIDTH	200
#define BUTTON_HEIGHT	150

const static std::wstring NOTICE = L"Press Q to quit.";

class OnGameSceneManager : public SceneManager
{
private:
	std::wstring msg;

	int alpha;
	int bgSpeed;
	int bgOffsetX;
	int bgOffsetY;

	void SetBackBuffer();
public:
	OnGameSceneManager(MainGame* _mg);
	~OnGameSceneManager();

	void Init(MainGame* _mg);
	void Update(HWND _hWnd);
	void LateUpdate();
	void Release();
	void Render(HDC _hdc);
};