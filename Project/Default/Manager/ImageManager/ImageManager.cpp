#include "Stdafx/stdafx.h"

#include "ImageManager.h"

HRESULT ImageManager::init() { return S_OK; }

void ImageManager::Release() { DeleteAll(); }

Image * ImageManager::AddImage(std::wstring _strKey, int _width, int _height) {
	Image* img = FindImage(_strKey);

	if (img) return img;

	img = new Image();
	if (FAILED(img->Init(_width, _height))) {
		SAFE_DELETE(img);
		return NULL;
	}

	mImageList.insert(pair<wstring, Image*>(_strKey, img));

	return img;
}

Image * ImageManager::AddImage(
	wstring _strKey, const wchar_t* _fileName,
	int _width, int _height,
	bool _isTrans, COLORREF _transColor
) {
	Image* img = FindImage(_strKey);

	if (img) return img;

	img = new Image();
	if (FAILED(
		img->Init(_fileName, _width, _height, _isTrans, _transColor)
	)) {
		SAFE_DELETE(img);
		return NULL;
	}

	mImageList.insert(pair<wstring, Image*>(_strKey, img));

	return nullptr;
}

Image * ImageManager::AddImage(
	wstring _strKey, const wchar_t* _fileName,
	float _x, float _y, int _width, int _height,
	bool _isTrans, COLORREF _transColor
) {
	Image* img = FindImage(_strKey);

	if (img) return img;

	img = new Image();
	if (FAILED(
		img->Init(_fileName, _x, _y, _width, _height, _isTrans, _transColor)
	)) {
		SAFE_DELETE(img);
		return NULL;
	}

	mImageList.insert(pair<wstring, Image*>(_strKey, img));

	return nullptr;
}

Image * ImageManager::AddFrameImage(
	wstring _strKey, const wchar_t* _fileName,
	int _width, int _height, int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
	bool _isTrans, COLORREF _transColor
) {
	Image* img = FindImage(_strKey);

	if (img) return img;

	img = new Image();
	if (FAILED(
		img->Init(_fileName, _width, _height, _maxFrameX, _maxFrameY, _maxFrameIdx, _isTrans, _transColor)
	)) {
		SAFE_DELETE(img);
		return NULL;
	}

	mImageList.insert(pair<wstring, Image*>(_strKey, img));

	return nullptr;
}

Image * ImageManager::AddFrameImage(
	wstring _strKey, const wchar_t* _fileName,
	float _x, float _y, int _width, int _height,
	int _maxFrameX, int _maxFrameY, int _maxFrameIdx,
	bool _isTrans, COLORREF _transColor
) {
	Image* img = FindImage(_strKey);

	if (img) return img;

	img = new Image();
	if (FAILED(
		img->Init(_fileName, _x, _y, _width, _height, _maxFrameX, _maxFrameY, _maxFrameIdx, _isTrans, _transColor)
	)) {
		SAFE_DELETE(img);
		return NULL;
	}

	mImageList.insert(pair<wstring, Image*>(_strKey, img));

	return nullptr;
}

Image * ImageManager::FindImage(std::wstring _strKey) {
	if (mImageList.find(_strKey) == mImageList.end())
		return NULL;
	else
		return mImageList.find(_strKey)->second;
}

bool ImageManager::DeleteImage(std::wstring _strKey) {
	auto key = mImageList.find(_strKey);

	if (key != mImageList.end()) {
		key->second->Release();
		SAFE_DELETE(key->second);
		mImageList.erase(key);
		return true;
	}

	return false;
}

bool ImageManager::DeleteAll() {
	MapImageIter iter = mImageList.begin();

	for (; iter != mImageList.end();) {
		if (iter->second) {
			iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = mImageList.erase(iter);
		}
		else {
			++iter;
		}
	}

	mImageList.clear();

	return true;
}

void ImageManager::Render(wstring _strKey, HDC _hdc) {
	Image* img = FindImage(_strKey);
	if (img) img->Render(_hdc);
}

void ImageManager::Render(wstring _strKey, HDC _hdc, int _destX, int _destY) {
	Image* img = FindImage(_strKey);
	if (img) img->Render(_hdc, _destX, _destY);
}

void ImageManager::Render(wstring _strKey, HDC _hdc, int _destX, int _destY, int _srcX, int _srcY, int _srcWidth, int _srcHeight) {
	Image* img = FindImage(_strKey);
	if (img) img->Render(_hdc, _destX, _destY, _srcX, _srcY, _srcWidth, _srcHeight);
}

void ImageManager::AlphaRender(wstring _strKey, HDC _hdc, BYTE _alpha) {
	Image* img = FindImage(_strKey);
	if (img) img->AlphaRender(_hdc, _alpha);
}

void ImageManager::AlphaRender(wstring _strKey, HDC _hdc, int _destX, int _destY, BYTE _alpha) {
	Image* img = FindImage(_strKey);
	if (img) img->AlphaRender(_hdc, _destX, _destY, _alpha);

}

void ImageManager::AlphaRender(wstring _strKey, HDC _hdc, int _destX, int _destY, int _srcX, int _srcY, int _srcWidth, int _srcHeight, BYTE _alpha) {
	Image* img = FindImage(_strKey);
	if (img) img->AlphaRender(_hdc, _destX, _destY, _srcX, _srcY, _srcWidth, _srcHeight, _alpha);
}

void ImageManager::FrameRender(wstring _strKey, HDC _hdc, int _destX, int _destY) {
	Image* img = FindImage(_strKey);
	if (img) img->FrameRender(_hdc, _destX, _destY);
}

void ImageManager::FrameRender(wstring _strKey, HDC _hdc, int _destX, int _destY, int _currentFrameX, int _currentFrameY) {
	Image* img = FindImage(_strKey);
	if (img) img->FrameRender(_hdc, _destX, _destY, _currentFrameX, _currentFrameY);
}

void ImageManager::LoopRender(std::wstring _strKey, HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY) {
	Image* img = FindImage(_strKey);
	if (img) img->LoopRender(_hdc, _drawArea, _offsetX, _offsetY);
}

void ImageManager::LoopAlphaRender(std::wstring _strKey, HDC _hdc, const LPRECT _drawArea, int _offsetX, int _offsetY, BYTE _alpha) {
	Image* img = FindImage(_strKey);
	if (img) img->LoopAlphaRender(_hdc, _drawArea, _offsetX, _offsetY, _alpha);
}
