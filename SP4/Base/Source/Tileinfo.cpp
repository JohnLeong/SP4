#include "Tileinfo.h"

CTiledata::COLLISION_TYPE GetCollisionTypeFromId(CTiledata::TILE_ID id)
{
	switch (id)
	{
	case CTiledata::TILE_VOID:
	case CTiledata::TILE_WALL_STONE_01:
		return CTiledata::COL_BLOCK;
	case CTiledata::TILE_FLOOR_STONE_01:
		return CTiledata::COL_VOID;
	case CTiledata::TILE_FLOOR_ICE_01:
		return CTiledata::COL_ICE;
	case CTiledata::TILE_HOLE_STONE_01:
		return CTiledata::COL_HOLE;
	case CTiledata::TILE_WIND_UP:
		return CTiledata::COL_WIND_UP;
	case CTiledata::TILE_WIND_DOWN:
		return CTiledata::COL_WIND_DOWN;
	case CTiledata::TILE_WIND_LEFT:
		return CTiledata::COL_WIND_LEFT;
	case CTiledata::TILE_WIND_RIGHT:
		return CTiledata::COL_WIND_RIGHT;
	case CTiledata::TILE_RUNE:
		return CTiledata::COL_RUNE;
	case CTiledata::TILE_DOOR_RED:
		return CTiledata::COL_LOCK_RED;
	case CTiledata::TILE_DOOR_BLUE:
		return CTiledata::COL_LOCK_BLUE;
	case CTiledata::TILE_DOOR_GREEN:
		return CTiledata::COL_LOCK_GREEN;
	case CTiledata::TILE_DOOR_YELLOW:
		return CTiledata::COL_LOCK_YELLOW;
	case CTiledata::TILE_MONKEY:
	case CTiledata::TILE_STAIRCASE:
		return CTiledata::COL_ENDLEVEL;
	default:
		return CTiledata::COL_VOID;
		break;
	}
}
