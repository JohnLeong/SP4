#include "Tileinfo.h"

CTiledata::COLLISION_TYPE GetCollisionTypeFromId(CTiledata::TILE_ID id)
{
	switch (id)
	{
	case CTiledata::TILE_VOID:
	case CTiledata::TILE_WALL_STONE_01:
		return CTiledata::COL_BLOCK;
		break;
	case CTiledata::TILE_FLOOR_STONE_01:
		return CTiledata::COL_VOID;
		break;
	case CTiledata::TILE_FLOOR_ICE_01:
		return CTiledata::COL_ICE;
	case CTiledata::TILE_HOLE_STONE_01:
		return CTiledata::COL_HOLE;
	default:
		return CTiledata::COL_VOID;
		break;
	}
}
