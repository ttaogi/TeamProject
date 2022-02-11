#pragma once

#include "../Image.h"

class Stripe {
private:
	Image* image;
	int frameIdx;
	POINT coordinateRevision;
public:
	Stripe();
	~Stripe();

	HRESULT Init(std::wstring _imageKey, POINT _coordinateRevision);

	void Reset() { frameIdx = 0; }

	void Release();

	void FrameRender(HDC _hdc, POINT _pos);

	bool IsEnd() const { return (frameIdx == image->GetImageInfo()->maxFrameIdx); }
};
