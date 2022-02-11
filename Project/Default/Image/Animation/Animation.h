#pragma once

#include "../Stripe/Stripe.h"
#include "../../Utility/Enums.h"

std::wstring StateToWString(CHARACTER_STATE _state);

class Animation {
private:
	Stripe stripe;
	CHARACTER_STATE state;
	bool autoLoop;
public:
	Animation() {}
	~Animation() { Release(); }

	HRESULT Init(
		std::wstring _ImageKey,POINT _coordinateRevision,
		CHARACTER_STATE _state, bool _autoLoop
	);

	void Reset() { stripe.Reset(); }

	void Release() { stripe.Release(); }

	void AnimationRender(HDC _hdc, POINT _pos);

	bool IsEnd() const;
};