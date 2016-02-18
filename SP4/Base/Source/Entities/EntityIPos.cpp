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

void CEntityIPos::DoColDir(MOVE_DIR m_MoveDir)
{
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

/********************************************************************************
Update
********************************************************************************/
void CEntityIPos::Update(const float dt, CPlayer* cPlayer)
{
	switch (this->m_MoveDir)
	{
	case DIR_UP:
		this->m_fOffSetY += dt * 100;
		if (this->m_fOffSetY > m_cTilemap->GetTileSize())
		{
			this->m_fOffSetY = 0;
			--this->m_iYIndex;
			this->m_MoveDir = DIR_NONE;
		}
		break;
	case DIR_DOWN:
		this->m_fOffSetY -= dt * 100;
		if (this->m_fOffSetY < -m_cTilemap->GetTileSize())
		{
			this->m_fOffSetY = 0;
			++this->m_iYIndex;
			this->m_MoveDir = DIR_NONE;
		}
		break;
	case DIR_LEFT:
		this->m_fOffSetX -= dt * 100;
		if (this->m_fOffSetX < -m_cTilemap->GetTileSize())
		{
			this->m_fOffSetX = 0;
			--this->m_iXIndex;
			this->m_MoveDir = DIR_NONE;
		}
		break;
	case DIR_RIGHT:
		this->m_fOffSetX += dt * 100;
		if (this->m_fOffSetX > m_cTilemap->GetTileSize())
		{
			this->m_fOffSetX = 0;
			++this->m_iXIndex;
			this->m_MoveDir = DIR_NONE;
		}
		break;
	default:
		break;
	}
}

void CEntityIPos::UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*> entityList)
{

}