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

bool PointCmp(POINT pos1, POINT pos2)
{
	return (pos1.x == pos2.x && pos1.y == pos2.y);
}
