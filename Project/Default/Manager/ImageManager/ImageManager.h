#pragma once

#include <map>
#include <string>
#include <Windows.h>

#include "DesignPattern/SingletonBase/SingletonBase.h"
#include "Image/Image.h"

typedef std::map<std::wstring, Image*> MapImageList;
typedef std::map<std::wstring, Image*>::iterator MapImageIter;

class ImageManager : public SingletonBase<ImageManager> {
private:
	MapImageList mImageList;
public:
	HRESULT init();
	void Release();

	Image* AddImage(std::wstring _strKey, int _width, int _height);
	Image* AddImage(
		std::wstring _strKey, const wchar_t* _fileName,
		int _width, int _height,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0)
	);
	Image* AddImage(
		std::wstring _strKey, const wchar_t* _fileName,
		float _x, float _y, int _width, int _height,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0)
	);
	Image* AddFrameImage(
		std::wstring _strKey, const wchar_t* _fileName,
		int _width, int _height, int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0)
	);
	Image* AddFrameImage(
		std::wstring _strKey, const wchar_t* _fileName,
		float _x, float _y, int _width, int _height,
		int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
		bool _isTrans = FALSE, COLORREF _transColor = RGB(0, 0, 0)
	);

	Image* FindImage(std::wstring _strKey);
	bool DeleteImage(std::wstring _strKey);
	bool DeleteAll();

	void Render(std::wstring _strKey, HDC _hdc);
	void Render(std::wstring _strKey, HDC _hdc, int _destX, int _destY);
	void Render(std::wstring _strKey, HDC _hdc, int _destX, int _destY, int _srcX, int _srcY, int _srcWidth, int _srcHeight);

	void AlphaRender(std::wstring _strKey, HDC _hdc, BYTE _alpha);
	void AlphaRender(std::wstring _strKey, HDC _hdc, int _destX, int _destY, BYTE _alpha);
	void AlphaRender(std::wstring _strKey, HDC _hdc, int _destX, int _destY, int _srcX, int _srcY, int _srcWidth, int _srcHeight, BYTE _alpha);

	void FrameRender(std::wstring _strKey, HDC _hdc, int _destX, int _destY);
	void FrameRender(std::wstring _strKey, HDC _hdc, int _destX, int _destY, int _currentFrameX, int _currentFrameY);

	void LoopRender(std::wstring _strKey, HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY);
	void LoopAlphaRender(std::wstring _strKey, HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY, BYTE _alpha);
};