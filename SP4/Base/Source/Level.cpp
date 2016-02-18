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

	if (CheckPlayerCollisions(cPlayer))
		m_bDoMovements = true;

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
			this->m_cTilemap->theScreenMap[k][i].SetTint(false);
		}
	}
	for (std::vector<CEntityIPos*>::iterator entity = m_cEntityIPosList.begin(); entity != m_cEntityIPosList.end(); entity++)
	{
		(*entity)->UpdateMovement(dt, cPlayer, m_cEntityIPosList);
	}
}

bool CLevel::CheckPlayerCollisions(CPlayer* cPlayer)
{
	switch (cPlayer->GetNextDirection())
	{
	case CPlayer::PD_UP:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x(), cPlayer->GetPos_y() - 1).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_y() - 1 <= 0)
		{
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x(), cPlayer->GetPos_y() - 1))
			{
				cPlayer->MoveUpDown(true, m_cTilemap);
				cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	case CPlayer::PD_DOWN:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x(), cPlayer->GetPos_y() + 1).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_y() + 2 >= m_cTilemap->GetNumOfTiles_Height())
		{
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x(), cPlayer->GetPos_y() + 1))
			{
				cPlayer->MoveUpDown(false, m_cTilemap);
				cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	case CPlayer::PD_RIGHT:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x() + 1, cPlayer->GetPos_y()).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_x() + 2 >= m_cTilemap->GetNumOfTiles_Width())
		{
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x() + 1, cPlayer->GetPos_y()))
			{
				cPlayer->MoveLeftRight(true, m_cTilemap);
				cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	case CPlayer::PD_LEFT:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x() - 1, cPlayer->GetPos_y()).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_x() - 1 <= 0)
		{
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x() - 1, cPlayer->GetPos_y()))
			{
				cPlayer->MoveLeftRight(false, m_cTilemap);
				cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	default:
		break;
	}
	cPlayer->SetNextDirection(CPlayer::PD_NONE);
	return false;
}

bool CLevel::CheckEntityCollisions(CPlayer* cPlayer, int iXIndex, int iYIndex)
{
	for (std::vector<CEntityIPos*>::iterator entity = m_cEntityIPosList.begin(); entity != m_cEntityIPosList.end(); entity++)
	{
		if ((*entity)->GetXIndex() == iXIndex && (*entity)->GetYIndex() == iYIndex)
		{
			switch (cPlayer->GetNextDirection())
			{
			case CPlayer::PD_UP:
				if (!CheckEntityCollisions(cPlayer, (*entity)->GetXIndex(), (*entity)->GetYIndex() - 1) && m_cTilemap->GetTile((*entity)->GetXIndex(), (*entity)->GetYIndex() - 1).GetCollisionType() == CTiledata::COL_VOID)
				{
					(*entity)->DoColDir(CEntityIPos::DIR_UP);
					return false;
				}
				return true;
			case CPlayer::PD_DOWN:
				if (!CheckEntityCollisions(cPlayer, (*entity)->GetXIndex(), (*entity)->GetYIndex() + 1) && m_cTilemap->GetTile((*entity)->GetXIndex(), (*entity)->GetYIndex() + 1).GetCollisionType() == CTiledata::COL_VOID)
				{
					(*entity)->DoColDir(CEntityIPos::DIR_DOWN);
					return false;
				}
				return true;
			case CPlayer::PD_RIGHT:
				if (!CheckEntityCollisions(cPlayer, (*entity)->GetXIndex() + 1, (*entity)->GetYIndex()) && m_cTilemap->GetTile((*entity)->GetXIndex() + 1, (*entity)->GetYIndex()).GetCollisionType() == CTiledata::COL_VOID)
				{
					(*entity)->DoColDir(CEntityIPos::DIR_RIGHT);
					return false;
				}
				return true;
			case CPlayer::PD_LEFT:
				if (!CheckEntityCollisions(cPlayer, (*entity)->GetXIndex() - 1, (*entity)->GetYIndex()) && m_cTilemap->GetTile((*entity)->GetXIndex() - 1, (*entity)->GetYIndex()).GetCollisionType() == CTiledata::COL_VOID)
				{
					(*entity)->DoColDir(CEntityIPos::DIR_LEFT);
					return false;
				}
				return true;
			default:
				break;
			}
		}
	}
	return false;
}