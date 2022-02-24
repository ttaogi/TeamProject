#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE	_hInstance;
HWND		_hWnd;
POINT		_ptMouse = { 0, 0 };
LPTSTR		_lpszClass = TEXT("WindowsAPI");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

//! 윈도우 메인함수
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	_mg = new MainGame();
	_hInstance = hInstance;

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

	//게임 프로그래밍
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

	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	_mg->release();
	UnregisterClass(WINNAME, hInstance);


	return (int)message.wParam;
	*/
	_mg->release();

	return (int)message.wParam;
}
       
//! 윈도우 프로시저 
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