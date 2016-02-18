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

int CLevel::GetPlayerStartPosX()
{
	return playerStartPosX;
}

int CLevel::GetPlayerStartPosY()
{
	return playerStartPosY;
}

bool CLevel::InitLua(std::string levelName)
{
	m_cluascript = new CLuaScript(levelName);
	playerStartPosX = m_cluascript->getIntVariable("playerPosX ");
	playerStartPosY = m_cluascript->getIntVariable("playerPosY ");
	maxNumberOfEnemies = m_cluascript->getIntVariable("maxNumOfEnemies");
	for (int i = 0; i < maxNumberOfEnemies; i++)
	{
		int currentEnemy = i + 1;
		ostringstream convertor;
		string getEnemy = "enemy";
		convertor << currentEnemy;
		getEnemy.append(convertor.str());
		m_cluascript->getNsetEnemyVariables(getEnemy);
	}
	return true;
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
