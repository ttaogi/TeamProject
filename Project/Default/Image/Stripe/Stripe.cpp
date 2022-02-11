#include "Stdafx/stdafx.h"

#include "Stripe.h"

Stripe::Stripe() {
	image = NULL;
}

Stripe::~Stripe() {
	Release();
}

HRESULT Stripe::Init(std::wstring _imageKey, POINT _coordinateRevision) {
	image = IMG->FindImage(_imageKey);
	if (image == NULL) return E_FAIL;

	frameIdx = 0;
	coordinateRevision = _coordinateRevision;

	return S_OK;
}

void Stripe::Release() { }

void Stripe::FrameRender(HDC _hdc, POINT _pos) {
	LPIMAGE_INFO imageInfo = image->GetImageInfo();

	if (frameIdx >= imageInfo->maxFrameIdx) frameIdx = imageInfo->maxFrameIdx - 1;
	int destX = _pos.x + coordinateRevision.x;
	int destY = _pos.y + coordinateRevision.y;
	int srcX = (frameIdx % imageInfo->maxFrameX) * imageInfo->frameWidth;
	int srcY = (frameIdx / imageInfo->maxFrameX) * imageInfo->frameHeight;

	if (image->GetIsTrans() == true) {
		GdiTransparentBlt(
			_hdc, destX, destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			srcX,
			srcY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			image->GetTransColor()
		);
	}
	else {
		BitBlt(
			_hdc, destX, destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			srcX,
			srcY,
			SRCCOPY
		);
	}

	++frameIdx;
}
