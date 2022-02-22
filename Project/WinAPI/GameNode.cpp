#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	
	//백버퍼 초기화
	//this->setBackBuffer();

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//로케일 설정
		setlocale(LC_ALL, "Korean");

		//타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);

		//키매니저 초기화
		KEYMANAGER->init();

		//랜덤펑션 초기화
		RND->init();

		//이미지매니저 초기화
		IMAGEMANAGER->init();
		//ReleaseDC(_hWnd, _hdc);

		//임시 사운드
		TEMPSOUNDMANAGER->init();

		//타임매니저 초기화
		TIMEMANAGER->init();

		//텍스트데이터매니저 초기화
		TEXTDATAMANAGER->init();

		//씬매니저 초기화
		SCENEMANAGER->init();

	}
	return S_OK;
}


void GameNode::release()
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);

		//키매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();

		//랜덤펑션 싱글톤 해제
		RND->releaseSingleton();

		//이미지매니저 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		
		//폰트매니저 싱글톤 해제
		FONTMANAGER->releaseSingleton();

		//템프사운드매니저 싱글톤 해제
		TEMPSOUNDMANAGER->releaseSingleton();

		//타임매니저 해제, 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//텍스트 데이터 매니저 해제, 싱글톤 해제
		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		//씬 매니저 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		
		//백버퍼 이미지 해제
		//SAFE_DELETE(_backBuffer);
	}
	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//InvalidateRect(_hWnd, NULL, FALSE);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (imessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:

		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		//InvalidateRect(hWnd, NULL, true);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, imessage, wParam, lParam));
	//return LRESULT();
}
