#pragma once

#include "Manager/SceneManager/SceneManager.h"

#define BUTTON_WIDTH	200
#define BUTTON_HEIGHT	150

class TitleSceneManager : public SceneManager {
private:
	void SetBackBuffer();
public:
	TitleSceneManager(MainGame* _mg);
	~TitleSceneManager() {}

	void Init(MainGame* _mg);
	void Update(HWND _hWnd);
	void LateUpdate();
	void Release();
	void Render(HDC _hdc);
};