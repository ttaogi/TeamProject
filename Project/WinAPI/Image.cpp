#include "Stdafx.h"
#include "Image.h"
#include "Animation.h"

Image::Image() : _imageInfo(NULL) //��� �ޱ����� �ʱ�ȭ �ض�
				, _fileName(NULL)
				, _isTrans(FALSE)
				, _transColor(RGB(0, 0, 0))
				,_blendImage(RGB(0,0,0))
				,_blendFunc()
{
}

HRESULT Image::init(int width, int height)
{
	//���ʱ�ȭ ���� -> �̹��� ������ ���� ��� �ִٸ� ������ ���� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	//���� �˻� �� assert, static_assert
	/*
	���� �����ϰ� ����� ������� ���ܰ� �߰ߵǸ� ��Ÿ�� ���δ� if���� ���ϋ� ���� assert�� false�϶� ����
	assert(_imageInfo == nullptr); 

	������ ���̱� static_assert �� ������ ���߿� ��������� �״´� (����Ÿ���� ������ ���� ����϶� ����)
	static_assert
	*/
	
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	/*
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
	*/
	//�̹��� ���� ���� ������ �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->LoadType = LOAD_EMPTY;
	_imageInfo->resID = 0;

	//1 (CreateCompatibleDC) ���� ����
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);

	//2 (CreateCompatibleBitmap) ���� ����
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ������µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ���� -> �̹��� ������ ���� ��� �ִٸ� ������ ���� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	//���� �˻� �� assert, static_assert
	/*
	���� �����ϰ� ����� ������� ���ܰ� �߰ߵǸ� ��Ÿ�� ���δ� if���� ���ϋ� ���� assert�� false�϶� ����
	assert(_imageInfo == nullptr);

	������ ���̱� static_assert �� ������ ���߿� ��������� �״´� (����Ÿ���� ������ ���� ����϶� ����)
	static_assert
	*/

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	
	//�̹��� ���� ���� ������ �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->LoadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	//3.LoadBitmap ���� ����
	//4.MAKEINTRESOURCE(���ҽ��� �������µ� �ٽ����� �Լ�) ���� ����
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ���� -> �̹��� ������ ���� ��� �ִٸ� ������ ���� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ������ �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->LoadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = (int)strlen(fileName);

	_fileName = new CHAR[len + 1]; // +1 �ϴ������� white space �Ǽ� ���� �����ϱ����� �����ϰ�
	strcpy_s(_fileName, len + 1, fileName);
	
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);


	//�̹��� ���� ���� ������ �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->LoadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->x = x;
	_imageInfo->y = y;

	//���� �̸�
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);


	//�̹��� ���� ���� ������ �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->LoadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;


	//���� �̸�
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);


	//�̹��� ���� ���� ������ �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->LoadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;
	_imageInfo->x = x;
	_imageInfo->y = y;


	//���� �̸�
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	
	//�̹��� ���� ���� ������ �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->LoadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void Image::release(void) //�����Ͱ� �����ִٸ� release �� �������
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}

//���� (0, 0������ ����)
void Image::render(HDC hdc)
{
	if (_isTrans)
	{
		//GdiTransparentBlt: ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ������ �ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			0,						//����� ��ǥ ���� X
			0,						//����� ��ǥ ���� Y
			_imageInfo->width,		//����� �̹��� ���� ũ��
			_imageInfo->height,		//����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		//����� ��� �޸� DC
			0, 0,					//���� ���� ����
			_imageInfo->width,		//���� ���� ���� ũ��
			_imageInfo->height,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);
	}

	else
	{
		//BitBlt: ������ �Ȼ��ϱ� GdiTransparentBlt���� ������ ,DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt: ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ������ �ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			destX,					//����� ��ǥ ���� X
			destY,					//����� ��ǥ ���� Y
			_imageInfo->width,		//����� �̹��� ���� ũ��
			_imageInfo->height,		//����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		//����� ��� �޸� DC
			0, 0,					//���� ���� ����
			_imageInfo->width,		//���� ���� ���� ũ��
			_imageInfo->height,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);
	}

	else
	{
		//BitBlt: ������ �Ȼ��ϱ� GdiTransparentBlt���� ������ ,DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//Ŭ����
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		//GdiTransparentBlt: ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ������ �ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			destX,					//����� ��ǥ ���� X
			destY,					//����� ��ǥ ���� Y
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,					
			sourWidth,
			sourHeight,		
			_transColor				
		);
	}

	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,  _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϴ���?
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. ����ؾ� �� DC �� �׷��� �ִ� ������ ���� �̹����� �׸���.
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		//2. ���� �̹����� ����� ������ ���� �̹����� �׸���.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			0,0,					//����� ��ǥ ���� X
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,					//���� ���� ����
			_imageInfo->width,
			_imageInfo->height,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);

		//3. ���� �̹����� ȭ�鿡 �׸���.
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}

}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϴ���?
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//1. ����ؾ� �� DC �� �׷��� �ִ� ������ ���� �̹����� �׸���.
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		);

		//2. ���� �̹����� ����� ������ ���� �̹����� �׸���.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			0, 0,					//����� ��ǥ ���� X
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,					//���� ���� ����
			_imageInfo->width,
			_imageInfo->height,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);

		//3. ���� �̹����� ȭ�鿡 �׸���.
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else
	{
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (_isTrans)
	{
		//GdiTransparentBlt: ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ������ �ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			destX,					//����� ��ǥ ���� X
			destY,					//����� ��ǥ ���� Y
			_imageInfo->frameWidth,		//����� �̹��� ���� ũ��
			_imageInfo->frameHeight,		//����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		//����� ��� �޸� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ����
			_imageInfo->frameWidth,		//���� ���� ���� ũ��
			_imageInfo->frameHeight,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);
	}

	else
	{
		//BitBlt: ������ �Ȼ��ϱ� GdiTransparentBlt���� ������ ,DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	//�̹��� ����ó��

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			destX,					//����� ��ǥ ���� X
			destY,					//����� ��ǥ ���� Y
			_imageInfo->frameWidth,		//����� �̹��� ���� ũ��
			_imageInfo->frameHeight,		//����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		//����� ��� �޸� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ����
			_imageInfo->frameWidth,		//���� ���� ���� ũ��
			_imageInfo->frameHeight,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);
	}

	else
	{
		//BitBlt: ������ �Ȼ��ϱ� GdiTransparentBlt���� ������ ,DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ��DC ( ȭ�鿡 ������))
			destX,					//����� ��ǥ ���� X
			destY,					//����� ��ǥ ���� Y
			_imageInfo->frameWidth,		//����� �̹��� ���� ũ��
			_imageInfo->frameHeight,		//����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		//����� ��� �޸� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ����
			_imageInfo->frameWidth,		//���� ���� ���� ũ��
			_imageInfo->frameHeight,		//���� ���� ���� ũ��
			_transColor				//�����Ҷ� ������ ����
		);
	}

	else
	{
		//BitBlt: ������ �Ȼ��ϱ� GdiTransparentBlt���� ������ ,DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset ���� ������ ��� ������ �ϰڴ�.
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC���� (ȭ�� ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ �÷��ְٴ�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				sourWidth, sourHeight);
		}//end of second for
	}//end of for
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}

void Image::aniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}
