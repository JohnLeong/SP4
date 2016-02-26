#include "EntityIPos.h"
#include <math.h>
#include "MyMath.h"


CEntityIPos::CEntityIPos()
: m_fOffSetX(0.f)
, m_fOffSetY(0.f)
, m_MoveDir(DIR_NONE)
, m_AnimDir(DIR_IDLE_DOWN)
, m_bHoldingObj(false)
, m_bRecalculate(true)
, m_fDeathOffSetX(DEATH_ANIM_START_OFFSET_X)
, m_fDeathOffSetY(0.f)
{
	m_bDeathDir = Math::RandIntMinMax(0, 1);
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

float CEntityIPos::GetRenderPosX(void)
{
	if (m_bAlive)
		return ((static_cast<float>(this->m_iXIndex) * m_cTilemap->GetTileSize()) + m_fOffSetX);
	else
	{
		if (m_bDeathDir)
			return ((static_cast<float>(this->m_iXIndex) * m_cTilemap->GetTileSize()) + m_fOffSetX + m_fDeathOffSetX - DEATH_ANIM_START_OFFSET_X);
		else
			return ((static_cast<float>(this->m_iXIndex) * m_cTilemap->GetTileSize()) + m_fOffSetX - (m_fDeathOffSetX - DEATH_ANIM_START_OFFSET_X));
	}
		
}

float CEntityIPos::GetRenderPosY(void)
{
	if (m_bAlive)
		return ((static_cast<float>(this->m_iYIndex) * -m_cTilemap->GetTileSize()) + m_fOffSetY);
	else
		return ((static_cast<float>(this->m_iYIndex) * -m_cTilemap->GetTileSize()) + m_fOffSetY - m_fDeathOffSetY);
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
	if (!m_bAlive)
	{
		m_fDeathOffSetX += dt * DEATH_ANIM_SPEED_X;
		//m_fDeathOffSetY = (0.04 * (m_fDeathOffSetX * m_fDeathOffSetX)) + (0.03 * m_fDeathOffSetX) + 1;
		m_fDeathOffSetY = (((m_fDeathOffSetX * m_fDeathOffSetX) - (2 * m_fDeathOffSetX) - 3) * 0.1) - DEATH_ANIM_OFFSET_Y;
		//m_fDeathOffSetY = Math::RadianToDegree(sin(cos(m_fDeathOffSetX)));
		if (m_fDeathOffSetY > DEATH_ANIM_CUTOFF_Y)
			m_bActive = false;
		return;
	}
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
		DoCurrentTileCollision();
		break;
	}
}

void CEntityIPos::UpdateMovement(const float dt)
{

}

bool CEntityIPos::DoCurrentTileCollision()
{
	switch (this->m_cTilemap->GetTile(this->m_iXIndex, this->m_iYIndex).GetCollisionType())
	{
	case CTiledata::COL_VOID:
		this->m_MoveDir = DIR_NONE;
		return false;
	case CTiledata::COL_ICE:
		if (this->m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
		{
			for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
			{
				if ((*entity) == this || !(*entity)->IsAlive())
					continue;
				if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
				{
					this->m_MoveDir = DIR_NONE;
					return false;
				}
			}
			m_cTilemap->theScreenMap[static_cast<int>(GetNextDirectionPos().x)][static_cast<int>(GetNextDirectionPos().y)].SetTint(true);
			return true;
		}
		this->m_MoveDir = DIR_NONE;
		return false;
	default:
		return false;
	}
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

//Get the number of red keys
int CEntityIPos::GetKeys_Red(void)
{
	return -1;
}

//Get the number of blue keys
int CEntityIPos::GetKeys_Blue(void)
{
	return -1;
}

//Get the number of green keys
int CEntityIPos::GetKeys_Green(void)
{
	return -1;
}

//Get the number of yyellow keys
int CEntityIPos::GetKeys_Yellow(void)
{
	return -1;
}

void CEntityIPos::AddKeys(int iAmt, int type)
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

void CEntityIPos::SetRecalculate(bool b)
{
	this->m_bRecalculate = b;
}