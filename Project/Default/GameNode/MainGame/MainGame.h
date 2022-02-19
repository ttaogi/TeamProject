#pragma once

#include "GameNode/GameNode.h"

class SceneManager;

class MainGame : public GameNode
{
private:
	bool quit;
public:
	MainGame();
	~MainGame();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	void QuitGame();
};