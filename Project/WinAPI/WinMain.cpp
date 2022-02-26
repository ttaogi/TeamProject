﻿#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE	_hInstance;
HWND		_hWnd;
POINT		_ptMouse = { 0, 0 };
LPTSTR		_lpszClass = TEXT("WindowsAPI");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
void loadResources();
void releaseResources();

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	_mg = new MainGame();
	_hInstance = hInstance;

	loadResources();

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wndClass);

	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init()))
	{
		return 0;
	}

	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	_mg->release();

	releaseResources();

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, imessage, wParam, lParam);
}
         
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

void loadResources()
{
	setlocale(LC_ALL, "Korean");

	RND->init();
	// FONTMANAGER has no init.
	IMAGEMANAGER->init();
	KEYMANAGER->init();
	SCENEMANAGER->init();
	SOUNDMANAGER->init();
	TEXTDATAMANAGER->init();
	TIMEMANAGER->init();
	XMLMANAGER->init();

	ITEMINFOMANAGER->init();
	MAPINFOMANAGER->init();
	PLAYERINFOMANAGER->init();

	SOUNDMANAGER->addSound(KEY_BGM_INTRO, DIR_BGM_INTRO, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_LOBBY, DIR_BGM_LOBBY, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_MAIN_MENU, DIR_BGM_MAIN_MENU, true, true);
}

void releaseResources()
{
	PLAYERINFOMANAGER->release();
	PLAYERINFOMANAGER->releaseSingleton();
	MAPINFOMANAGER->release();
	MAPINFOMANAGER->releaseSingleton();
	ITEMINFOMANAGER->release();
	ITEMINFOMANAGER->releaseSingleton();

	XMLMANAGER->release();
	XMLMANAGER->releaseSingleton();
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	TEXTDATAMANAGER->release();
	TEXTDATAMANAGER->releaseSingleton();
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	MAPINFOMANAGER->release();
	MAPINFOMANAGER->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();
	FONTMANAGER->releaseSingleton();
	RND->releaseSingleton();
}
