#pragma once

#include "Manager/SceneManager/SceneManager.h"

class TitleSceneManager : public SceneManager {
private:
	Image* bgImage;
	
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