#include "Tileinfo.h"

CTiledata::COLLISION_TYPE GetCollisionTypeFromId(CTiledata::TILE_ID id)
{
	switch (id)
	{
	case CTiledata::TILE_VOID:
		return CTiledata::COL_BLOCK;
		break;
	case CTiledata::TILE_WALL_STONE_01:
		return CTiledata::COL_BLOCK;
		break;
	default:
		return CTiledata::COL_VOID;
		break;
	}
}
