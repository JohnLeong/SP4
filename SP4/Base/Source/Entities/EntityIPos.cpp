#include "EntityIPos.h"


CEntityIPos::CEntityIPos()
: m_fOffSetX(0.f)
, m_fOffSetY(0.f)
, m_MoveDir(DIR_NONE)
, m_AnimDir(DIR_IDLE_DOWN)
, m_bHoldingObj(false)
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

bool CEntityIPos::DoColDir(MOVE_DIR m_MoveDir)
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
		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex - 1), 0));
	case DIR_DOWN:
		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex + 1), 0));
	case DIR_RIGHT:
		return (Vector3(static_cast<float>(this->m_iXIndex + 1), static_cast<float>(this->m_iYIndex), 0));
	case DIR_LEFT:
		return (Vector3(static_cast<float>(this->m_iXIndex - 1), static_cast<float>(this->m_iYIndex), 0));
	default:
		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex), 0));
	}
	return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex), 0));
}

bool CEntityIPos::IsMoving(void)
{
	if (m_MoveDir == DIR_NONE)
		return false;
	else
		return true;
	///return (m_MoveDir != DIR_NONE);
}

/********************************************************************************
Update
********************************************************************************/
void CEntityIPos::Update(const float dt)
{
	switch (this->m_MoveDir)
	{
	case DIR_UP:
		if (this->m_fOffSetY + (dt * ENTITY_MOVE_SPEED) > m_cTilemap->GetTileSize())
		{
			this->m_fOffSetY = 0;
			--this->m_iYIndex;
			if (DoCurrentTileCollision())
				m_AnimDir = DIR_IDLE_UP;
			break;
		}
		this->m_fOffSetY += dt * ENTITY_MOVE_SPEED;
		break;
	case DIR_DOWN:
		if (this->m_fOffSetY - (dt * ENTITY_MOVE_SPEED) < -m_cTilemap->GetTileSize())
		{
			this->m_fOffSetY = 0;
			++this->m_iYIndex;
			if (DoCurrentTileCollision())
				m_AnimDir = DIR_IDLE_DOWN;
			break;
		}
		this->m_fOffSetY -= dt * ENTITY_MOVE_SPEED;
		break;
	case DIR_LEFT:
		if (this->m_fOffSetX - (dt * ENTITY_MOVE_SPEED) < -m_cTilemap->GetTileSize())
		{
			this->m_fOffSetX = 0;
			--this->m_iXIndex;
			if (DoCurrentTileCollision())
				m_AnimDir = DIR_IDLE_LEFT;
			break;
		}
		this->m_fOffSetX -= dt * ENTITY_MOVE_SPEED;
		break;
	case DIR_RIGHT:
		if (this->m_fOffSetX + (dt * ENTITY_MOVE_SPEED) > m_cTilemap->GetTileSize())
		{
			this->m_fOffSetX = 0;
			++this->m_iXIndex;
			if (DoCurrentTileCollision())
				m_AnimDir = DIR_IDLE_RIGHT;
			break;
		}

		this->m_fOffSetX += dt * ENTITY_MOVE_SPEED;
		break;
	default:
		break;
	}
}

void CEntityIPos::UpdateMovement(const float dt)
{

}

bool CEntityIPos::DoCurrentTileCollision()
{
	return false;
}

bool CEntityIPos::AllowEnemyMovement(void)
{
	return false;
}

bool CEntityIPos::DeathOnEntry(void)
{
	return false;
}

int CEntityIPos::GetCoins(void)
{
	return -1;
}

void CEntityIPos::AddCoin(int iAmt)
{

}

bool CEntityIPos::IsHoldingObj(void)
{
	return this->m_bHoldingObj;
}

CEntityIPos* CEntityIPos::GetHoldingObj(void)
{
	return this->m_cObjPtr;
}