#include "Level.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

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
		//Skip if entity is not alive
		if (!(*entity)->IsAlive())
			continue;
		(*entity)->Update(dt);
		if ((*entity)->IsMoving())
			this->m_bMovementReady = false;
	}

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
		//Skip if entity is not alive
		if (!(*entity)->IsAlive())
			continue;
		(*entity)->UpdateMovement(dt);
	}
}

bool CLevel::CheckPlayerCollisionsCurrent(CPlayer* cPlayer)
{
	/*switch (m_cTilemap->GetTile(cPlayer->GetXIndex(), cPlayer->GetYIndex()).GetCollisionType())
	{
	case CTiledata::COL_ICE:
		std::cout << "ICE";
		if (m_cTilemap->GetTile(static_cast<int>(cPlayer->GetNextDirectionPos().x), static_cast<int>(cPlayer->GetNextDirectionPos().y)).GetCollisionType() == CTiledata::COL_BLOCK)
			return false;
		return true;
	default:
		return false;
	}*/
	return false;
}

bool CLevel::CheckPlayerCollisions(CPlayer* cPlayer)
{
	switch (cPlayer->GetNextDirection())
	{
	case CPlayer::PD_UP:
		if (m_cTilemap->GetTile(cPlayer->GetXIndex(), cPlayer->GetYIndex() - 1).GetCollisionType() == CTiledata::COL_BLOCK || 
			m_cTilemap->GetTile(cPlayer->GetXIndex(), cPlayer->GetYIndex() - 1).GetCollisionType() == CTiledata::COL_HOLE ||
			cPlayer->GetYIndex() - 1 <= 0)
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetXIndex(), cPlayer->GetYIndex() - 1))
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
		if (m_cTilemap->GetTile(cPlayer->GetXIndex(), cPlayer->GetYIndex() + 1).GetCollisionType() == CTiledata::COL_BLOCK || 
			m_cTilemap->GetTile(cPlayer->GetXIndex(), cPlayer->GetYIndex() + 1).GetCollisionType() == CTiledata::COL_HOLE || 
			cPlayer->GetYIndex() + 2 >= m_cTilemap->GetNumOfTiles_Height())
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetXIndex(), cPlayer->GetYIndex() + 1))
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
		if (m_cTilemap->GetTile(cPlayer->GetXIndex() + 1, cPlayer->GetYIndex()).GetCollisionType() == CTiledata::COL_BLOCK || 
			m_cTilemap->GetTile(cPlayer->GetXIndex() + 1, cPlayer->GetYIndex()).GetCollisionType() == CTiledata::COL_HOLE || 
			cPlayer->GetXIndex() + 2 >= m_cTilemap->GetNumOfTiles_Width())
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetXIndex() + 1, cPlayer->GetYIndex()))
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
		if (m_cTilemap->GetTile(cPlayer->GetXIndex() - 1, cPlayer->GetYIndex()).GetCollisionType() == CTiledata::COL_BLOCK || 
			m_cTilemap->GetTile(cPlayer->GetXIndex() - 1, cPlayer->GetYIndex()).GetCollisionType() == CTiledata::COL_HOLE || 
			cPlayer->GetXIndex() - 1 <= 0)
		{
			//cPlayer->SetNextDirection(CPlayer::PD_NONE);
			return false;
		}
		else
		{
			if (!CheckEntityCollisions(cPlayer, cPlayer->GetXIndex() - 1, cPlayer->GetYIndex()))
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
		if ((*entity)->GetXIndex() == iXIndex && (*entity)->GetYIndex() == iYIndex && (*entity)->IsAlive())
		{
			switch (cPlayer->GetNextDirection())
			{
			case CPlayer::PD_UP:
				return((*entity)->DoColDir(CEntityIPos::DIR_UP));
			case CPlayer::PD_DOWN:
				return((*entity)->DoColDir(CEntityIPos::DIR_DOWN));
			case CPlayer::PD_RIGHT:
				return((*entity)->DoColDir(CEntityIPos::DIR_RIGHT));
			case CPlayer::PD_LEFT:
				return((*entity)->DoColDir(CEntityIPos::DIR_LEFT));
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

void CLevel::SetPlayerPtr(CPlayer* cPlayer)
{
	this->m_cPlayerPtr = cPlayer;
}

CEnemyZombie* CLevel::GenerateZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDINGKEY_TYPE t)
{
	CEnemyZombie* zombie;
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("ZAMBIE", 4, 3);
	temp_mesh->textureID = LoadTGA("Image//Entities//explorer2.tga");
	switch (t)
	{
	case CEnemy::HOLDING_KEY_NONE:
		zombie = new CEnemyZombie(3, 3, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList);
		break;
	case CEnemy::HOLDING_KEY_RED:
		zombie = new CEnemyZombie(3, 3, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateRedKeyEntity(0, 0));
		break;
	case CEnemy::HOLDING_KEY_GREEN:
		break;
	case CEnemy::HOLDING_KEY_BLUE:
		break;
	default:
		break;
	}
	m_cEntityIPosList.push_back(zombie);
	return zombie;
}

CEntity_Key_Red* CLevel::GenerateRedKeyEntity(int iXIndex, int iYIndex)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("Key", 1, 11);
	temp_mesh->textureID = LoadTGA("Image//Entities//key.tga");
	CEntity_Key_Red* key = new CEntity_Key_Red(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), new Animation(0, 10, 0, 0.3f), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(key);
	return key;
}

CEntity_Coin* CLevel::GenerateCoinEntity(int iXIndex, int iYIndex)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("Key", 1, 8);
	temp_mesh->textureID = LoadTGA("Image//Entities//coin.tga");
	CEntity_Coin* coin = new CEntity_Coin(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(coin);
	return coin;
}