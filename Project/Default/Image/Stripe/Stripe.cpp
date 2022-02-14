#include "Stdafx/stdafx.h"

#include "Stripe.h"

Stripe::Stripe()
{
	frameUpdateSec = DEFAULT_FUS;
	elapsedSec = 0.0f;
	image = NULL;
}

Stripe::~Stripe() { Release(); }

HRESULT Stripe::Init(std::wstring _imageKey,
	POINT _coordinateRevision, float _frameUpdateSec)
{
	image = IMG->FindImage(_imageKey);
	if (image == NULL) return E_FAIL;

	if (_frameUpdateSec > 0) frameUpdateSec = _frameUpdateSec;
	frameIdx = 0;
	coordinateRevision = _coordinateRevision;

	return S_OK;
}

void Stripe::Release() { }

void Stripe::FrameRender(HDC _hdc, POINT _pos, bool _isPlay)
{
	LPIMAGE_INFO imageInfo = image->GetImageInfo();
	int usedIdx = 0;

	if (_isPlay)
	{
		elapsedSec += TIME->GetElapsedTime();

		while (elapsedSec >= frameUpdateSec) {
			elapsedSec -= frameUpdateSec;
			++frameIdx;
		}
	}

	if (frameIdx >= imageInfo->maxFrameIdx)
	{
		frameIdx = imageInfo->maxFrameIdx;
		usedIdx = frameIdx - 1;
	}
	else
		usedIdx = frameIdx;

	int destX = _pos.x + coordinateRevision.x;
	int destY = _pos.y + coordinateRevision.y;
	int srcX = (usedIdx % imageInfo->maxFrameX) * imageInfo->frameWidth;
	int srcY = (usedIdx / imageInfo->maxFrameX) * imageInfo->frameHeight;

	if (image->GetIsTrans() == true)
	{
		GdiTransparentBlt(
			_hdc, destX, destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			srcX,
			srcY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			image->GetTransColor());
	}
	else {
		BitBlt(
			_hdc, destX, destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			srcX,
			srcY,
			SRCCOPY);
	}
}
