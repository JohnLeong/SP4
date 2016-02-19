#include "Level.h"

CLevel::CLevel(void)
: m_bDoMovements(false)
, m_bMovementReady(true)
, m_bDoTileCheck(false)
{
}

CLevel::~CLevel(void)
{
}

CTilemap* CLevel::GetTilemap(void)
{
	return m_cTilemap;
}

bool CLevel::InitTilemap(int iNumTileX, int iNumTileY, float fTileSize)
{
	/*if (m_cTilemap)
		delete m_cTilemap;*/

	m_cTilemap = new CTilemap();
	m_cTilemap->Init(iNumTileX, iNumTileY, fTileSize);

	return true;
}

bool CLevel::LoadTilemap(std::string mapname)
{
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
	if (m_bMovementReady)
	{
		if (CheckPlayerCollisions(cPlayer))
			m_bDoMovements = true;
	}

	this->m_bMovementReady = true;

	if (cPlayer->IsMoving())
		this->m_bMovementReady = false;
	else
		cPlayer->SetNextDirection(CPlayer::PD_NONE);

	for (std::vector<CEntityIPos*>::iterator entity = m_cEntityIPosList.begin(); entity != m_cEntityIPosList.end(); entity++)
	{
		(*entity)->Update(dt, cPlayer);
		if ((*entity)->IsMoving())
			this->m_bMovementReady = false;
	}

	//if (this->m_bMovementReady == true && this->m_bDoTileCheck)
	//{
	//	m_bDoTileCheck = false;
	//	if (CheckPlayerCollisionsCurrent(cPlayer))
	//	{
	//		m_bMovementReady = false;
	//		switch (cPlayer->GetNextDirection())
	//		{
	//		case CPlayer::PD_UP:
	//			cPlayer->MoveUpDown(true, m_cTilemap);
	//			break;
	//		case CPlayer::PD_DOWN:
	//			cPlayer->MoveUpDown(false, m_cTilemap);
	//			break;
	//		case CPlayer::PD_LEFT:
	//			cPlayer->MoveLeftRight(false, m_cTilemap);
	//			break;
	//		case CPlayer::PD_RIGHT:
	//			cPlayer->MoveLeftRight(true, m_cTilemap);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		cPlayer->SetNextDirection(CPlayer::PD_NONE);
	//	}
	//}

	if (this->m_bDoMovements)
	{
		UpdateMovement(dt, cPlayer);
		this->m_bDoMovements = false;
		this->m_bDoTileCheck = true;
	}

	m_cTilemap->UpdateSprites(static_cast<double>(dt));
}

void CLevel::UpdateMovement(const float dt, CPlayer* cPlayer)
{
	//Reset tile tint
	for (int i = 0; i < this->m_cTilemap->GetNumOfTiles_Height(); i++)
	{
		for (int k = 0; k < this->m_cTilemap->GetNumOfTiles_Width(); k++)
		{
			this->m_cTilemap->theScreenMap[k][i].SetTint(false);
		}
	}
	for (std::vector<CEntityIPos*>::iterator entity = m_cEntityIPosList.begin(); entity != m_cEntityIPosList.end(); entity++)
	{
		(*entity)->UpdateMovement(dt, cPlayer, &this->m_cEntityIPosList);
	}
}

bool CLevel::CheckPlayerCollisionsCurrent(CPlayer* cPlayer)
{
	switch (m_cTilemap->GetTile(cPlayer->GetPos_x(), cPlayer->GetPos_y()).GetCollisionType())
	{
	case CTiledata::COL_ICE:
		std::cout << "ICE";
		if (m_cTilemap->GetTile(cPlayer->GetNextDirectionPos().x, cPlayer->GetNextDirectionPos().y).GetCollisionType() == CTiledata::COL_BLOCK)
			return false;
		return true;
	default:
		return false;
	}
	return false;
}

bool CLevel::CheckPlayerCollisions(CPlayer* cPlayer)
{
	switch (cPlayer->GetNextDirection())
	{
	case CPlayer::PD_UP:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x(), cPlayer->GetPos_y() - 1).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_y() - 1 <= 0)
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x(), cPlayer->GetPos_y() - 1))
			{
				cPlayer->MoveUpDown(true, m_cTilemap);
				//cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	case CPlayer::PD_DOWN:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x(), cPlayer->GetPos_y() + 1).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_y() + 2 >= m_cTilemap->GetNumOfTiles_Height())
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x(), cPlayer->GetPos_y() + 1))
			{
				cPlayer->MoveUpDown(false, m_cTilemap);
				//cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	case CPlayer::PD_RIGHT:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x() + 1, cPlayer->GetPos_y()).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_x() + 2 >= m_cTilemap->GetNumOfTiles_Width())
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x() + 1, cPlayer->GetPos_y()))
			{
				cPlayer->MoveLeftRight(true, m_cTilemap);
				//cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		break;
	case CPlayer::PD_LEFT:
		if (m_cTilemap->GetTile(cPlayer->GetPos_x() - 1, cPlayer->GetPos_y()).GetCollisionType() == CTiledata::COL_BLOCK || cPlayer->GetPos_x() - 1 <= 0)
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetPos_x() - 1, cPlayer->GetPos_y()))
			{
				cPlayer->MoveLeftRight(false, m_cTilemap);
				//cPlayer->SetNextDirection(CPlayer::PD_NONE);
				return true;
			}
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
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
				return((*entity)->DoColDir(CEntityIPos::DIR_UP, &this->m_cEntityIPosList));
			case CPlayer::PD_DOWN:
				return((*entity)->DoColDir(CEntityIPos::DIR_DOWN, &this->m_cEntityIPosList));
			case CPlayer::PD_RIGHT:
				return((*entity)->DoColDir(CEntityIPos::DIR_RIGHT, &this->m_cEntityIPosList));
			case CPlayer::PD_LEFT:
				return((*entity)->DoColDir(CEntityIPos::DIR_LEFT, &this->m_cEntityIPosList));
			default:
				break;
			}
		}
	}
	return false;
}

bool CLevel::IsMovementReady(void)
{
	return this->m_bMovementReady;
}

void CLevel::SetMovementReady(bool b)
{
	this->m_bMovementReady = b;
}