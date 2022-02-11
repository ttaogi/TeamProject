#pragma once

#include "../Utility/Enums.h"

typedef struct tagImage {
	DWORD	resID;
	HDC		hMemDC;
	HBITMAP	hBit;
	HBITMAP	hOBit;
	int		width;
	int		height;
	IMAGE_LOAD_KIND	loadType;

	int x, y;
	int currentFrameX, currentFrameY;
	int maxFrameX, maxFrameY, maxFrameIdx;
	int frameWidth, frameHeight;

	tagImage() {
		resID = 0;
		hMemDC = NULL;
		hBit = NULL;
		hOBit = NULL;
		width = 0;
		height = 0;
		loadType = IMAGE_LOAD_KIND::LOAD_RESOURCE;
		x = y = 0;
		currentFrameX = currentFrameY = 0;
		maxFrameX = maxFrameY = maxFrameIdx = 0;
		frameWidth = frameHeight = 0;
	}
} IMAGE_INFO, * LPIMAGE_INFO;

class Image {
protected:
	LPIMAGE_INFO	imageInfo;
	wchar_t*		fileName;
	bool			isTrans;
	COLORREF		transColor;

	BLENDFUNCTION	blendFunc;
	LPIMAGE_INFO	blendImage;
public:
	Image();
	~Image();

	HRESULT Init(int _width, int _height);
	HRESULT Init(const DWORD _resID, int _width, int _height,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0));
	HRESULT Init(const wchar_t* _fileName, int _width, int _height,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0));
	HRESULT Init(const wchar_t* _fileName, float _x, float _y,
		int _width, int _height, BOOL _isTrans, COLORREF _transColor);
	// frame.
	HRESULT Init(const wchar_t* _fileName, int _width, int _height,
		int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0));
	HRESULT Init(const wchar_t* _fileName,
		float _x, float _y, int _width, int _height,
		int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0));
	HRESULT InitForAlphaBlend();

	LPIMAGE_INFO GetImageInfo() { return imageInfo; }
	bool GetIsTrans() const { return isTrans; }
	COLORREF GetTransColor() const { return transColor; }
	void SetTransColor(bool _isTrans, COLORREF _transColor);
	LPIMAGE_INFO GetBlendImageInfo() { return blendImage; }

	void Release();

	void Render(HDC _hdc);
	void Render(HDC _hdc, int _destX, int _destY);
	void Render(HDC _hdc, int _destX, int _destY, int _destWidth, int _destHeight);
	void Render(HDC _hdc, int _destX, int _destY,
		int _srcX, int _srcY, int _srcWidth, int _srcHeight);
	void AlphaRender(HDC _hdc, BYTE _alpha);
	void AlphaRender(HDC _hdc, int _destX, int _destY, BYTE _alpha);
	void AlphaRender(HDC _hdc, int _destX, int _destY,
		int _srcX, int _srcY, int _srcWidth, int _srcHeight, BYTE _alpha);

	void FrameRender(HDC _hdc, int _destX, int _destY);
	void FrameRender(HDC _hdc, int _destX, int _destY, int _currentFrameX, int _currentFrameY);

	void LoopRender(HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY);
	void LoopAlphaRender(HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY, BYTE _alpha);

	inline HDC GetMemDC() { return imageInfo->hMemDC; }
};