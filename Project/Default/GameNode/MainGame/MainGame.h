#pragma once

#include "GameNode/GameNode.h"
#include "Manager/SceneManager/EndSceneManager/EndSceneManager.h"
#include "Manager/SceneManager/OnGameSceneManager/OnGameSceneManager.h"
#include "Manager/SceneManager/TitleSceneManager/TitleSceneManager.h"

class MainGame : public GameNode
{
	SceneManager* scnMgr;
	SCENE_TYPE nextScnType;
	bool quit;
public:
	MainGame();
	~MainGame();

	HRESULT Init();
	HRESULT Init(bool _managerInit);
	void Release();

	void Update(HWND _hWnd);
	void Render(HDC _hdc);

	LRESULT MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	void SetNextScene_ONGAME();
	void SetNextScene_END();

	void QuitGame();
};