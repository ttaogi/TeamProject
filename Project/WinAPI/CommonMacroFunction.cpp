#include "Stdafx.h"

#include "CommonMacroFunction.h"

POINT GridPointToPixelPointCenter(POINT pos)
{
	return POINT{pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2};
}

POINT GridPointToPixelPointLeftTop(POINT pos)
{
	return POINT{ pos.x * TILE_SIZE, pos.y * TILE_SIZE };
}
