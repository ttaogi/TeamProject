#include "Stdafx.h"
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
	CAMERAMANAGER->init();
	// FONTMANAGER has no init.
	IMAGEMANAGER->init();
	KEYMANAGER->init();
	SCENEMANAGER->init();
	SOUNDMANAGER->init();
	TEXTDATAMANAGER->init();
	TIMEMANAGER->init();
	XMLMANAGER->init();

	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_LEFT, DIR_STEPPING_STONE_LEFT, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_TOP, DIR_STEPPING_STONE_TOP, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_RIGHT, DIR_STEPPING_STONE_RIGHT, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STEPPING_STONE_BOTTOM, DIR_STEPPING_STONE_BOTTOM, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_STAIR, DIR_STAIR, 48, 48, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_ITEM_GOLD, DIR_ITEM_GOLD, 480, 96, 10, 2, 20, true, MAGENTA);

	IMAGEMANAGER->addImage(KEY_ITEM_SHOVEL, DIR_ITEM_SHOVEL, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_DAGGER, DIR_ITEM_DAGGER, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_BROADSWORD, DIR_ITEM_BROADSWORD, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_BODY, DIR_ITEM_BODY, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_HEAD, DIR_ITEM_HEAD, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_TORCH, DIR_ITEM_TORCH, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_APPLE, DIR_ITEM_APPLE, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_BOMB, DIR_ITEM_BOMB, 48, 48, true, MAGENTA);
	IMAGEMANAGER->addImage(KEY_ITEM_GOLDENLUTE, DIR_ITEM_GOLDENLUTE, 60, 50, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_ITEM_BOMBDROP, DIR_ITEM_BOMBDROP, 240, 48, 5, 1, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SFX_EXPLOSION, DIR_SFX_EXPLOSION, 1184, 148, 8, 1, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_NPC_SHOPKEEPER, DIR_NPC_SHOPKEEPER, 752, 152, 8, 2, 8, true, MAGENTA);

	SOUNDMANAGER->addSound(KEY_BGM_INTRO, DIR_BGM_INTRO, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_LOBBY, DIR_BGM_LOBBY, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_MAIN_MENU, DIR_BGM_MAIN_MENU, true, true);
	SOUNDMANAGER->addSound(KEY_BGM_ZONE_1_1, DIR_BGM_ZONE_1_1, true, true);
	
	ITEMINFOMANAGER->init();
	MAPINFOMANAGER->init();
	PLAYERINFOMANAGER->init();
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
	CAMERAMANAGER->release();
	CAMERAMANAGER->releaseSingleton();
	RND->releaseSingleton();
}
