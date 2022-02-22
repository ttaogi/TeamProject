#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	
	//����� �ʱ�ȭ
	//this->setBackBuffer();

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//������ ����
		setlocale(LC_ALL, "Korean");

		//Ÿ�̸� �ʱ�ȭ
		SetTimer(_hWnd, 1, 10, NULL);

		//Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();

		//������� �ʱ�ȭ
		RND->init();

		//�̹����Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();
		//ReleaseDC(_hWnd, _hdc);

		//�ӽ� ����
		TEMPSOUNDMANAGER->init();

		//Ÿ�ӸŴ��� �ʱ�ȭ
		TIMEMANAGER->init();

		//�ؽ�Ʈ�����͸Ŵ��� �ʱ�ȭ
		TEXTDATAMANAGER->init();

		//���Ŵ��� �ʱ�ȭ
		SCENEMANAGER->init();

	}
	return S_OK;
}


void GameNode::release()
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);

		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();

		//������� �̱��� ����
		RND->releaseSingleton();

		//�̹����Ŵ��� ����, �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		
		//��Ʈ�Ŵ��� �̱��� ����
		FONTMANAGER->releaseSingleton();

		//��������Ŵ��� �̱��� ����
		TEMPSOUNDMANAGER->releaseSingleton();

		//Ÿ�ӸŴ��� ����, �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//�ؽ�Ʈ ������ �Ŵ��� ����, �̱��� ����
		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		//�� �Ŵ��� ����, �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		
		//����� �̹��� ����
		//SAFE_DELETE(_backBuffer);
	}
	//DC ����
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
