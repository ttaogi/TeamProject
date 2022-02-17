#pragma once

#include "GameNode/GameNode.h"
#include "Utility/Enums.h"

class SceneManager;

class MainGame : public GameNode
{
private:
	bool quit;
	SceneManager* scnMgr;
	SCENE_TYPE nextScnType;
public:
	MainGame();
	~MainGame();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	void SetNextScene_ONGAME();
	void SetNextScene_END();

	void QuitGame();
};