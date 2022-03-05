#include "Stdafx.h"
#include "Enemy.h"

void Enemy::move(POINT _pos) {
	pos = _pos;
	POINT pixelPos = GridPointToPixelPointCenter(pos);
	_rc = RectMakeCenter(pixelPos.x, pixelPos.y,
		_rc.right - _rc.left, _rc.bottom - _rc.top);
}
