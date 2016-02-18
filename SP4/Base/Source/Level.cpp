#include "Level.h"

CLevel::CLevel(void)
: m_bDoMovements(false)
{
}

CLevel::~CLevel(void)
{
}

CTilemap* CLevel::GetTilemap(void)
{
	return m_cTilemap;
}

bool CLevel::InitTilemap(std::string mapname, int iNumTileX, int iNumTileY, float fTileSize)
{
	/*if (m_cTilemap)
		delete m_cTilemap;*/

	m_cTilemap = new CTilemap();
	m_cTilemap->Init(iNumTileX, iNumTileY, fTileSize);

	return(m_cTilemap->LoadMap(mapname));
}

void CLevel::SetDoMovements(bool bDoMovements)
{
	this->m_bDoMovements = bDoMovements;
}

void CLevel::Update(const float dt, CPlayer* cPlayer)
{
	for (std::vector<CEntityIPos*>::iterator entity = m_cEntityIPosList.begin(); entity != m_cEntityIPosList.end(); entity++)
	{
		(*entity)->Update(dt, cPlayer);
	}
	if (this->m_bDoMovements)
	{
		UpdateMovement(dt, cPlayer);
		this->m_bDoMovements = false;
	}
}

void CLevel::UpdateMovement(const float dt, CPlayer* cPlayer)
{
	for (int i = 0; i < this->m_cTilemap->GetNumOfTiles_Height(); i++)
	{
		for (int k = 0; k < this->m_cTilemap->GetNumOfTiles_Width(); k++)
		{
			this->m_cTilemap->theScreenMap[i][k].SetTint(false);
		}
	}
	for (std::vector<CEntityIPos*>::iterator entity = m_cEntityIPosList.begin(); entity != m_cEntityIPosList.end(); entity++)
	{
		(*entity)->UpdateMovement(dt, cPlayer);
	}
}

void CLevel::CheckEntityCollisions(CPlayer* cPlayer)
{

}