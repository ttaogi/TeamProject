#include "Stdafx/stdafx.h"

#include "Animation.h"

HRESULT Animation::Init(
	std::wstring _ImageKey, POINT _coordinateRevision,
	CHARACTER_STATE _state, bool _autoLoop
) {
	if (
		FAILED(stripe.Init(_ImageKey, _coordinateRevision))
	) {
		return E_FAIL;
	}

	state = _state;
	autoLoop = _autoLoop;

	return S_OK;
}

void Animation::AnimationRender(HDC _hdc, POINT _pos) {
	stripe.FrameRender(_hdc, _pos);
	if (autoLoop && stripe.IsEnd()) stripe.Reset();
}

bool Animation::IsEnd() const {
	if (autoLoop) return false;
	return stripe.IsEnd();
}
