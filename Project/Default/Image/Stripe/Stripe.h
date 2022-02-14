#pragma once

#include "Image/Image.h"

#define DEFAULT_FUS		16.6f

class Stripe
{
private:
	float frameUpdateSec;
	float elapsedSec;
	int frameIdx;
	Image* image;
	POINT coordinateRevision;
public:
	Stripe();
	~Stripe();

	HRESULT Init(std::wstring _imageKey,
		POINT _coordinateRevision, float _frameUpdateSec = DEFAULT_FUS);

	void Reset() { frameIdx = 0; }

	void Release();

	void FrameRender(HDC _hdc, POINT _pos, bool _isPlay);

	bool IsEnd() const { return (frameIdx == image->GetImageInfo()->maxFrameIdx); }
};
