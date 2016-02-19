#include "EntityIPos.h"


CEntityIPos::CEntityIPos()
: m_fOffSetX(0.f)
, m_fOffSetY(0.f)
, m_MoveDir(DIR_NONE)
{
}


CEntityIPos::~CEntityIPos()
{
}

void CEntityIPos::SetXIndex(int iXIndex)
{
	this->m_iXIndex = iXIndex;
}

void CEntityIPos::SetYIndex(int iYIndex)
{
	this->m_iYIndex = iYIndex;
}

void CEntityIPos::SetPos(int iXIndex, int iYIndex)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
}

bool CEntityIPos::DoColDir(MOVE_DIR m_MoveDir, std::vector<CEntityIPos*>* entityList)
{
	return false;
}

int CEntityIPos::GetXIndex(void)
{
	return m_iXIndex;
}

int CEntityIPos::GetYIndex(void)
{
	return m_iYIndex;
}

float CEntityIPos::GetXOffset(void)
{
	return m_fOffSetX;
}

float CEntityIPos::GetYOffset(void)
{
	return m_fOffSetY;
}

Vector3 CEntityIPos::GetNextDirectionPos(void)
{
	switch (m_MoveDir)
	{
	case DIR_UP:
		return (Vector3(this->m_iXIndex, this->m_iYIndex - 1, 0));
	case DIR_DOWN:
		return (Vector3(this->m_iXIndex, this->m_iYIndex + 1, 0));
	case DIR_RIGHT:
		return (Vector3(this->m_iXIndex + 1, this->m_iYIndex, 0));
	case DIR_LEFT:
		return (Vector3(this->m_iXIndex - 1, this->m_iYIndex, 0));
	default:
		return (Vector3(this->m_iXIndex, this->m_iYIndex, 0));
	}
	return (Vector3(this->m_iXIndex, this->m_iYIndex, 0));
}

bool CEntityIPos::IsMoving(void)
{
	return (m_MoveDir != DIR_NONE);
}

/********************************************************************************
Update
********************************************************************************/
void CEntityIPos::Update(const float dt, CPlayer* cPlayer)
{
	switch (this->m_MoveDir)
	{
	case DIR_UP:
		if (this->m_fOffSetY + (dt * ENTITY_MOVE_SPEED) > m_cTilemap->GetTileSize())
		{
			this->m_fOffSetY = 0;
			--this->m_iYIndex;
			DoCurrentTileCollision();
			break;
		}
		this->m_fOffSetY += dt * ENTITY_MOVE_SPEED;
		break;
	case DIR_DOWN:
		if (this->m_fOffSetY - (dt * ENTITY_MOVE_SPEED) < -m_cTilemap->GetTileSize())
		{
			this->m_fOffSetY = 0;
			++this->m_iYIndex;
			DoCurrentTileCollision();
			break;
		}
		this->m_fOffSetY -= dt * ENTITY_MOVE_SPEED;
		break;
	case DIR_LEFT:
		if (this->m_fOffSetX - (dt * ENTITY_MOVE_SPEED) < -m_cTilemap->GetTileSize())
		{
			this->m_fOffSetX = 0;
			--this->m_iXIndex;
			DoCurrentTileCollision();
			break;
		}
		this->m_fOffSetX -= dt * ENTITY_MOVE_SPEED;
		break;
	case DIR_RIGHT:
		if (this->m_fOffSetX + (dt * ENTITY_MOVE_SPEED) > m_cTilemap->GetTileSize())
		{
			this->m_fOffSetX = 0;
			++this->m_iXIndex;
			DoCurrentTileCollision();
			break;
		}

		this->m_fOffSetX += dt * ENTITY_MOVE_SPEED;
		break;
	default:
		break;
	}
}

void CEntityIPos::UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList)
{

}

void CEntityIPos::DoCurrentTileCollision()
{
	switch (this->m_cTilemap->GetTile(this->m_iXIndex, this->m_iYIndex).GetCollisionType())
	{
	case CTiledata::COL_VOID:
		this->m_MoveDir = DIR_NONE;
		break;
	case CTiledata::COL_ICE:
		if (this->m_cTilemap->GetTile(GetNextDirectionPos().x, GetNextDirectionPos().y).GetCollisionType() == CTiledata::COL_BLOCK)
			this->m_MoveDir = DIR_NONE;
		break;
	default:
		break;
	}
}