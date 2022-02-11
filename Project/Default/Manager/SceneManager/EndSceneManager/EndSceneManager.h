#pragma once

#include "../SceneManager.h"

class EndSceneManager : public SceneManager
{
private:
	Image* bgImage;
	
	void SetBackBuffer();
public:
	EndSceneManager(MainGame* _mg);
	~EndSceneManager() {}

	void Init(MainGame* _mg);
	void Update(HWND _hWnd);
	void LateUpdate();
	void Release();
	void Render(HDC _hdc);
};