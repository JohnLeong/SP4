#include "Tiledata.h"

CTiledata::CTiledata(void)
: m_iTileId(TILE_NULL)
, m_iCollisionType(COL_NULL)
, m_bTint(false)
{
}

CTiledata::CTiledata(TILE_ID TileId, COLLISION_TYPE CollisionType)
: m_iTileId(TILE_NULL)
, m_iCollisionType(COL_NULL)
, m_bTint(false)
{
	this->m_iTileId = TileId;
	this->m_iCollisionType = CollisionType;
}

CTiledata::~CTiledata(void)
{
}

void CTiledata::SetTileId(CTiledata::TILE_ID TileId)
{
	this->m_iTileId = TileId;
}

void CTiledata::SetCollisionType(CTiledata::COLLISION_TYPE CollisionType)
{
	this->m_iCollisionType = CollisionType;
}

void CTiledata::SetTint(bool b)
{
	this->m_bTint = b;
}

CTiledata::TILE_ID CTiledata::GetTileId(void)
{
	return m_iTileId;
}

CTiledata::COLLISION_TYPE CTiledata::GetCollisionType(void)
{
	return m_iCollisionType;
}

bool CTiledata::IsTinted(void)
{
	return m_bTint;
}

void CTiledata::ChangeIdState(void)
{
	switch (this->m_iTileId)
	{
	case TILE_HOLE_STONE_01:
		this->m_iTileId = TILE_FLOOR_STONE_01;
		this->m_iCollisionType = COL_VOID;
		break;
	case TILE_RUNE:
		this->m_iTileId = TILE_RUNE_USED;
		this->m_iCollisionType = COL_VOID;
		break;
	default:
		break;
	}
}