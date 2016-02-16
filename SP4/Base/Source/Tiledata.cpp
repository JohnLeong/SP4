#include "Tiledata.h"

CTiledata::CTiledata(void)
: m_iTileId(TILE_NULL)
, m_iCollisionType(COL_NULL)
{
}

CTiledata::CTiledata(TILE_ID TileId, COLLISION_TYPE CollisionType)
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

CTiledata::TILE_ID CTiledata::GetTileId(void)
{
	return m_iTileId;
}

CTiledata::COLLISION_TYPE CTiledata::GetCollisionType(void)
{
	return m_iCollisionType;
}