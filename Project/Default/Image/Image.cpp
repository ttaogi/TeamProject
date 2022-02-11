#include "Stdafx/stdafx.h"

#include <string>

#include "Image.h"

// library for alpha blend.
#pragma comment (lib, "msimg32.lib")

Image::Image()
	: imageInfo(NULL), fileName(NULL), isTrans(FALSE),
	transColor(RGB(0, 0, 0)), blendImage(NULL)
{ }

Image::~Image() { Release(); }

HRESULT Image::Init(int _width, int _height)
{
	if (imageInfo != NULL) Release();

	HDC hdc = GetDC(HANDLE_WINDOW);

	imageInfo = new IMAGE_INFO();
	imageInfo->loadType = IMAGE_LOAD_KIND::LOAD_EMPTY;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = _width;
	imageInfo->height = _height;

	fileName = NULL;
	isTrans = FALSE;
	transColor = RGB(0, 0, 0);

	if (imageInfo->hBit == NULL)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

HRESULT Image::Init(const DWORD _resID, int _width, int _height,
	bool _isTrans, COLORREF _transColor)
{
	if (imageInfo != NULL) Release();

	HDC hdc = GetDC(HANDLE_WINDOW);

	imageInfo = new IMAGE_INFO();
	imageInfo->loadType = IMAGE_LOAD_KIND::LOAD_RESOURCE;
	imageInfo->resID = _resID;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBit = (HBITMAP)LoadBitmap(HANDLE_INSTANCE, MAKEINTRESOURCE(imageInfo->resID));
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = _width;
	imageInfo->height = _height;

	fileName = NULL;
	isTrans = _isTrans;
	transColor = _transColor;

	if (imageInfo->hBit == 0)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

HRESULT Image::Init(const wchar_t* _fileName, int _width, int _height,
	bool _isTrans, COLORREF _transColor)
{
	if (imageInfo != NULL) Release();

	HDC hdc = GetDC(HANDLE_WINDOW);

	imageInfo = new IMAGE_INFO();
	imageInfo->loadType = IMAGE_LOAD_KIND::LOAD_FILE;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);

	imageInfo->hBit = (HBITMAP)LoadImage(HANDLE_INSTANCE, _fileName, IMAGE_BITMAP,
		_width, _height, LR_LOADFROMFILE);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = _width;
	imageInfo->height = _height;

	fileName = new wchar_t[wcslen(_fileName) + 1];
	wcscpy_s(fileName, wcslen(_fileName) + 1, _fileName);

	isTrans = _isTrans;
	transColor = _transColor;

	if (imageInfo->hBit == 0)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

HRESULT Image::Init(const wchar_t* _fileName, float _x, float _y,
	int _width, int _height, BOOL _isTrans, COLORREF _transColor)
{
	if (imageInfo != NULL) this->Release();

	HDC hdc = GetDC(HANDLE_WINDOW);

	imageInfo = new IMAGE_INFO();
	imageInfo->loadType = IMAGE_LOAD_KIND::LOAD_FILE;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);

	imageInfo->hBit = (HBITMAP)LoadImage(HANDLE_INSTANCE, _fileName, IMAGE_BITMAP,
		_width, _height, LR_LOADFROMFILE);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->x = (int)_x;
	imageInfo->y = (int)_y;
	imageInfo->width = _width;
	imageInfo->height = _height;

	fileName = new wchar_t[wcslen(_fileName) + 1];
	wcscpy_s(fileName, wcslen(_fileName) + 1, _fileName);

	isTrans = _isTrans;
	transColor = _transColor;

	if (imageInfo->hBit == 0)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

// frame.
HRESULT Image::Init(const wchar_t* _fileName, int _width, int _height,
	int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
	bool _isTrans, COLORREF _transColor)
{
	if (imageInfo != NULL) this->Release();

	HDC hdc = GetDC(HANDLE_WINDOW);

	imageInfo = new IMAGE_INFO();
	imageInfo->loadType = IMAGE_LOAD_KIND::LOAD_FILE;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);

	imageInfo->hBit = (HBITMAP)LoadImage(HANDLE_INSTANCE, _fileName, IMAGE_BITMAP,
		_width, _height, LR_LOADFROMFILE);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->width = _width;
	imageInfo->height = _height;

	imageInfo->maxFrameX = _maxFrameX;
	imageInfo->maxFrameY = _maxFrameY;
	imageInfo->maxFrameIdx = _maxFrameIdx;
	imageInfo->frameWidth = _width / _maxFrameX;
	imageInfo->frameHeight = _height / _maxFrameY;

	fileName = new wchar_t[wcslen(_fileName) + 1];
	wcscpy_s(fileName, wcslen(_fileName) + 1, _fileName);

	isTrans = _isTrans;
	transColor = _transColor;

	if (imageInfo->hBit == 0)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

HRESULT Image::Init(const wchar_t* _fileName, float _x, float _y,
	int _width, int _height, int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
	bool _isTrans, COLORREF _transColor)
{
	if (imageInfo != NULL) Release();

	HDC hdc = GetDC(HANDLE_WINDOW);

	imageInfo = new IMAGE_INFO();
	imageInfo->loadType = IMAGE_LOAD_KIND::LOAD_FILE;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);

	imageInfo->hBit = (HBITMAP)LoadImage(HANDLE_INSTANCE, _fileName, IMAGE_BITMAP,
		_width, _height, LR_LOADFROMFILE);
	imageInfo->hOBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBit);
	imageInfo->x = (int)_x;
	imageInfo->y = (int)_y;
	imageInfo->width = _width;
	imageInfo->height = _height;
	imageInfo->currentFrameX = 0;
	imageInfo->currentFrameY = 0;
	imageInfo->maxFrameX = _maxFrameX;
	imageInfo->maxFrameY = _maxFrameY;
	imageInfo->maxFrameIdx = _maxFrameIdx;
	imageInfo->frameWidth = _width / _maxFrameX;
	imageInfo->frameHeight = _height / _maxFrameY;

	fileName = new wchar_t[wcslen(_fileName) + 1];
	wcscpy_s(fileName, wcslen(_fileName) + 1, _fileName);

	isTrans = _isTrans;
	transColor = _transColor;

	if (imageInfo->hBit == 0)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

HRESULT Image::InitForAlphaBlend()
{
	if (imageInfo == NULL) return E_FAIL;

	HDC hdc = GetDC(HANDLE_WINDOW);

	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.BlendOp = AC_SRC_OVER;

	blendImage = new IMAGE_INFO();
	blendImage->loadType = IMAGE_LOAD_KIND::LOAD_FILE;
	blendImage->resID = 0;
	blendImage->hMemDC = CreateCompatibleDC(hdc);

	blendImage->hBit = CreateCompatibleBitmap(hdc, imageInfo->width, imageInfo->height);
	blendImage->hOBit = (HBITMAP)SelectObject(blendImage->hMemDC, blendImage->hBit);
	blendImage->width = WINSIZE_X;
	blendImage->height = WINSIZE_Y;

	if (blendImage->hBit == 0)
	{ // fail to get resource.
		Release();
		ReleaseDC(HANDLE_WINDOW, hdc);
		return E_FAIL;
	}

	ReleaseDC(HANDLE_WINDOW, hdc);

	return S_OK;
}

void Image::SetTransColor(bool _isTrans, COLORREF _transColor)
{
	isTrans = _isTrans;
	transColor = _transColor;
}

void Image::Release()
{
	if (imageInfo != NULL)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOBit);
		DeleteObject(imageInfo->hBit);
		DeleteDC(imageInfo->hMemDC);

		SAFE_DELETE(imageInfo);
		SAFE_DELETE_ARRAY(fileName);
	}
	if (blendImage != NULL)
	{
		SelectObject(blendImage->hMemDC, blendImage->hOBit);
		DeleteObject(blendImage->hBit);
		DeleteDC(blendImage->hMemDC);

		SAFE_DELETE(blendImage);
	}
}

void Image::Render(HDC _hdc)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			_hdc, 0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor);
	}
	else
	{
		BitBlt(
			_hdc, 0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void Image::Render(HDC _hdc, int _destX, int _destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			_hdc, _destX, _destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor);
	}
	else
	{
		BitBlt(
			_hdc, _destX, _destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void Image::Render(HDC _hdc, int _destX, int _destY, int _destWidth, int _destHeight)
{
	GdiTransparentBlt(
		_hdc, _destX, _destY,
		_destWidth,
		_destHeight,
		imageInfo->hMemDC,
		0, 0,
		imageInfo->width,
		imageInfo->height,
		RGB(0, 0, 0));
}

void Image::Render(HDC _hdc, int _destX, int _destY,
	int _srcX, int _srcY, int _srcWidth, int _srcHeight)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			_hdc, _destX, _destY,
			_srcWidth,
			_srcHeight,
			imageInfo->hMemDC,
			_srcX, _srcY,
			_srcWidth,
			_srcHeight,
			transColor);
	}
	else
	{
		BitBlt(
			_hdc, _destX, _destY,
			_srcWidth,
			_srcHeight,
			imageInfo->hMemDC,
			_srcX, _srcY,
			SRCCOPY);
	}
}

void Image::AlphaRender(HDC _hdc, BYTE _alpha)
{
	// check that it`s the first call.
	if (!blendImage) InitForAlphaBlend();

	blendFunc.SourceConstantAlpha = _alpha;

	if (isTrans)
	{
		BitBlt(
			blendImage->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			_hdc,
			0, 0,
			SRCCOPY);
		GdiTransparentBlt(
			blendImage->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor);
		AlphaBlend(
			_hdc,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendImage->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(
			_hdc,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC _hdc, int _destX, int _destY, BYTE _alpha)
{
	// check that it`s the first call.
	if (!blendImage) InitForAlphaBlend();

	blendFunc.SourceConstantAlpha = _alpha;

	if (isTrans)
	{
		BitBlt(
			blendImage->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			_hdc,
			_destX, _destY,
			SRCCOPY);
		GdiTransparentBlt(
			blendImage->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor);
		AlphaBlend(
			_hdc,
			_destX, _destY,
			imageInfo->width,
			imageInfo->height,
			blendImage->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(
			_hdc,
			_destX, _destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC _hdc, int _destX, int _destY,
	int _srcX, int _srcY, int _srcWidth, int _srcHeight, BYTE _alpha)
{
	// check that it`s the first call.
	if (!blendImage) InitForAlphaBlend();

	blendFunc.SourceConstantAlpha = _alpha;

	if (isTrans)
	{
		BitBlt(
			blendImage->hMemDC,
			_destX, _destY,
			_srcWidth,
			_srcHeight,
			_hdc,
			_destX, _destY,
			SRCCOPY);
		GdiTransparentBlt(
			blendImage->hMemDC,
			_destX, _destY,
			_srcWidth,
			_srcHeight,
			imageInfo->hMemDC,
			_srcX, _srcY,
			_srcWidth,
			_srcHeight,
			transColor);
		AlphaBlend(
			_hdc,
			_destX, _destY,
			_srcWidth,
			_srcHeight,
			blendImage->hMemDC,
			_destX, _destY,
			_srcWidth,
			_srcHeight,
			blendFunc);
	}
	else
	{
		BitBlt(
			_hdc, _destX, _destY,
			_srcWidth,
			_srcHeight,
			imageInfo->hMemDC,
			_srcX, _srcY,
			SRCCOPY);
	}
}

void Image::FrameRender(HDC _hdc, int _destX, int _destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			_hdc, _destX, _destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			_hdc, _destX, _destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::FrameRender(HDC _hdc, int _destX, int _destY, int _currentFrameX, int _currentFrameY)
{
	imageInfo->currentFrameX = (_currentFrameX < imageInfo->maxFrameX)
		? (_currentFrameX) : imageInfo->maxFrameX - 1;
	imageInfo->currentFrameY = (_currentFrameY < imageInfo->maxFrameY)
		? (_currentFrameY) : imageInfo->maxFrameY - 1;

	if (isTrans)
	{
		GdiTransparentBlt(
			_hdc, _destX, _destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			_hdc, _destX, _destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->currentFrameX * imageInfo->frameWidth,
			imageInfo->currentFrameY * imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::LoopRender(HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY)
{
	// - offset value, revise.
	if (_offsetX < 0) _offsetX = imageInfo->width + (_offsetX % imageInfo->width);
	if (_offsetY < 0) _offsetY = imageInfo->height + (_offsetY % imageInfo->height);

	RECT rcSrc;
	int srcWidth;
	int srcHeight;

	RECT rcDest;

	int drawAreaX = _drawArea->left;
	int drawAreaY = _drawArea->top;
	int drawAreaW = _drawArea->right - _drawArea->left;
	int drawAreaH = _drawArea->bottom - _drawArea->top;

	for (int y = 0; y < drawAreaH; y += srcHeight)
	{
		rcSrc.top = (y + _offsetY) % imageInfo->height;
		rcSrc.bottom = imageInfo->height;
		srcHeight = rcSrc.bottom - rcSrc.top;

		if (y + srcHeight > drawAreaH)
		{
			rcSrc.bottom -= (y + srcHeight) - drawAreaH;
			srcHeight = rcSrc.bottom - rcSrc.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + srcHeight;

		for (int x = 0; x < drawAreaW; x += srcWidth)
		{
			rcSrc.left = (x + _offsetX) % imageInfo->width;
			rcSrc.right = imageInfo->width;
			srcWidth = rcSrc.right - rcSrc.left;

			if (x + srcWidth > drawAreaW)
			{
				rcSrc.right -= (x + srcWidth) - drawAreaW;
				srcWidth = rcSrc.right - rcSrc.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + srcWidth;

			Render(_hdc, rcDest.left, rcDest.top,
				rcSrc.left, rcSrc.top, srcWidth, srcHeight);
		}
	}
}

void Image::LoopAlphaRender(HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY, BYTE _alpha)
{
	// - offset value, revise.
	if (_offsetX < 0) _offsetX = imageInfo->width + (_offsetX % imageInfo->width);
	if (_offsetY < 0) _offsetY = imageInfo->height + (_offsetY % imageInfo->height);

	RECT rcSrc;
	int srcWidth;
	int srcHeight;

	RECT rcDest;

	int drawAreaX = _drawArea->left;
	int drawAreaY = _drawArea->top;
	int drawAreaW = _drawArea->right - _drawArea->left;
	int drawAreaH = _drawArea->bottom - _drawArea->top;

	for (int y = 0; y < drawAreaH; y += srcHeight)
	{
		rcSrc.top = (y + _offsetY) % imageInfo->height;
		rcSrc.bottom = imageInfo->height;
		srcHeight = rcSrc.bottom - rcSrc.top;

		if (y + srcHeight > drawAreaH)
		{
			rcSrc.bottom -= (y + srcHeight) - drawAreaH;
			srcHeight = rcSrc.bottom - rcSrc.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + srcHeight;

		for (int x = 0; x < drawAreaW; x += srcWidth)
		{
			rcSrc.left = (x + _offsetX) % imageInfo->width;
			rcSrc.right = imageInfo->width;
			srcWidth = rcSrc.right - rcSrc.left;

			if (x + srcWidth > drawAreaW)
			{
				rcSrc.right -= (x + srcWidth) - drawAreaW;
				srcWidth = rcSrc.right - rcSrc.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + srcWidth;

			AlphaRender(_hdc, rcDest.left, rcDest.top,
				rcSrc.left, rcSrc.top, srcWidth, srcHeight, _alpha);
		}
	}
}
