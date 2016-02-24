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
	while (m_cEntityIPosList.size() > 0)
	{
		CEntityIPos* entity = m_cEntityIPosList.back();
		delete entity;
		m_cEntityIPosList.pop_back();
	}
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
	string addPosX = "PosX";
	string addPosY = "PosY";
	string addHold = "Hold";

	m_cLuascript = new CLuaScript(levelName);
	m_cPlayerPtr->SetXIndex(m_cLuascript->getIntVariable("playerPosX"));
	m_cPlayerPtr->SetYIndex(m_cLuascript->getIntVariable("playerPosY"));
	maxNumberOfZombies = m_cLuascript->getIntVariable("maxNumOfZombies");

	for (int i = 0; i < maxNumberOfZombies; i++)
	{
		int currentZombie = i + 1;
		ostringstream convertor;
		string getZombie = "zombie";
		convertor << currentZombie;
		getZombie.append(convertor.str());

		getZombie += addPosX;
		enemyStartPosX = m_cLuascript->getIntVariable(getZombie);
		getZombie.erase(getZombie.begin() + 7, getZombie.end());

		getZombie += addPosY;
		enemyStartPosY = m_cLuascript->getIntVariable(getZombie);
		getZombie.erase(getZombie.begin() + 7, getZombie.end());

		getZombie += addHold;
		enemyHoldItem = m_cLuascript->getIntVariable(getZombie);

		if (enemyHoldItem == 1)
		{
			GenerateZombieEntity(enemyStartPosX, enemyStartPosY, CEnemy::HOLDING_COIN);
		}
		else if (enemyHoldItem == 2)
		{
			GenerateZombieEntity(enemyStartPosX, enemyStartPosY, CEnemy::HOLDING_KEY_BLUE);
		}
		else if (enemyHoldItem == 3)
		{
			GenerateZombieEntity(enemyStartPosX, enemyStartPosY, CEnemy::HOLDING_KEY_GREEN);
		}
		else if (enemyHoldItem == 4)
		{
			GenerateZombieEntity(enemyStartPosX, enemyStartPosY, CEnemy::HOLDING_KEY_RED);
		}
		else if (enemyHoldItem == 0)
		{
			GenerateZombieEntity(enemyStartPosX, enemyStartPosY, CEnemy::HOLDING_NONE);
		}
	}
	delete m_cLuascript;
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

bool CLevel::CheckPlayerCollisions(CPlayer* cPlayer)
{
	int iXCheckIndex, iYCheckIndex;
	switch (cPlayer->GetNextDirection())
	{
	case CPlayer::PD_UP:
		if (cPlayer->GetYIndex() - 1 <= 0)
			return false;
		iXCheckIndex = cPlayer->GetXIndex();
		iYCheckIndex = cPlayer->GetYIndex() - 1;
		break;
	case CPlayer::PD_DOWN:
		if (cPlayer->GetYIndex() + 2 >= m_cTilemap->GetNumOfTiles_Height())
			return false;
		iXCheckIndex = cPlayer->GetXIndex();
		iYCheckIndex = cPlayer->GetYIndex() + 1;
		break;
	case CPlayer::PD_RIGHT:
		if (cPlayer->GetXIndex() + 2 >= m_cTilemap->GetNumOfTiles_Width())
			return false;
		iXCheckIndex = cPlayer->GetXIndex() + 1;
		iYCheckIndex = cPlayer->GetYIndex();
		break;
	case CPlayer::PD_LEFT:
		if (cPlayer->GetXIndex() - 1 <= 0)
			return false;
		iXCheckIndex = cPlayer->GetXIndex() - 1;
		iYCheckIndex = cPlayer->GetYIndex();
		break;
	case CPlayer::PD_NONE:
		return false;
	default:
		iXCheckIndex = cPlayer->GetXIndex();
		iYCheckIndex = cPlayer->GetYIndex();
		break;
	}

	if (!m_cTilemap->AllowCollision(iXCheckIndex, iYCheckIndex))
		return false;
	else
	{
		if (!CheckEntityCollisions(cPlayer, iXCheckIndex, iYCheckIndex))
		{
			switch (cPlayer->GetNextDirection())
			{
			case CPlayer::PD_UP:
				cPlayer->MoveUpDown(true, m_cTilemap);
				return true;
			case CPlayer::PD_DOWN:
				cPlayer->MoveUpDown(false, m_cTilemap);
				return true;
			case CPlayer::PD_RIGHT:
				cPlayer->MoveLeftRight(true, m_cTilemap);
				return true;
			case CPlayer::PD_LEFT:
				cPlayer->MoveLeftRight(false, m_cTilemap);
				return true;
			default:
				break;
			}
		}
		return false;
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
				return ((*entity)->DoColDir(CEntityIPos::DIR_UP));
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

CEnemyZombie* CLevel::GenerateZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDING_OBJ_TYPE t)
{
	CEnemyZombie* zombie;
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("ZAMBIE", 4, 3);
	temp_mesh->textureID = LoadTGA("Image//Entities//explorer2.tga");
	switch (t)
	{
	case CEnemy::HOLDING_NONE:
		zombie = new CEnemyZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList);
		break;
	case CEnemy::HOLDING_KEY_RED:
		zombie = new CEnemyZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateRedKeyEntity(0, 0));
		break;
	case CEnemy::HOLDING_KEY_GREEN:
		zombie = new CEnemyZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateGreenKeyEntity(0, 0));
		break;
	case CEnemy::HOLDING_KEY_BLUE:
		zombie = new CEnemyZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateBlueKeyEntity(0, 0));
		break;
	case CEnemy::HOLDING_COIN:
		zombie = new CEnemyZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateCoinEntity(0, 0));
		break;
	default:
		std::cout << "Enemy generation error";
		break;
	}
	m_cEntityIPosList.push_back(zombie);
	return zombie;
}

CEnemySuperRetardZombie* CLevel::GenerateSuperRetardZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDING_OBJ_TYPE t)
{
	CEnemySuperRetardZombie* zombie;
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("ZAMBIE", 4, 3);
	temp_mesh->textureID = LoadTGA("Image//Entities//explorer2.tga");
	switch (t)
	{
	case CEnemy::HOLDING_NONE:
		zombie = new CEnemySuperRetardZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList);
		break;
	case CEnemy::HOLDING_KEY_RED:
		zombie = new CEnemySuperRetardZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateRedKeyEntity(0, 0));
		break;
	case CEnemy::HOLDING_KEY_GREEN:
		zombie = new CEnemySuperRetardZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateGreenKeyEntity(0, 0));
		break;
	case CEnemy::HOLDING_KEY_BLUE:
		zombie = new CEnemySuperRetardZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateBlueKeyEntity(0, 0));
		break; 
	case CEnemy::HOLDING_COIN:
		zombie = new CEnemySuperRetardZombie(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList, GenerateCoinEntity(0, 0));
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
	temp_mesh->textureID = LoadTGA("Image//Entities//key_red.tga");
	CEntity_Key_Red* key = new CEntity_Key_Red(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), new Animation(0, 10, 0, 0.3f), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(key);
	return key;
}

CEntity_Key_Blue* CLevel::GenerateBlueKeyEntity(int iXIndex, int iYIndex)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("Key", 1, 11);
	temp_mesh->textureID = LoadTGA("Image//Entities//key_blue.tga");
	CEntity_Key_Blue* key = new CEntity_Key_Blue(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), new Animation(0, 10, 0, 0.3f), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(key);
	return key;
}

CEntity_Key_Green* CLevel::GenerateGreenKeyEntity(int iXIndex, int iYIndex)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("Key", 1, 11);
	temp_mesh->textureID = LoadTGA("Image//Entities//key_green.tga");
	CEntity_Key_Green* key = new CEntity_Key_Green(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), new Animation(0, 10, 0, 0.3f), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(key);
	return key;
}

CEntity_Key_Yellow* CLevel::GenerateYellowKeyEntity(int iXIndex, int iYIndex)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("Key", 1, 11);
	temp_mesh->textureID = LoadTGA("Image//Entities//key_yellow.tga");
	CEntity_Key_Yellow* key = new CEntity_Key_Yellow(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), new Animation(0, 10, 0, 0.3f), this->m_cPlayerPtr, &m_cEntityIPosList);
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

CEntity_Fire* CLevel::GenerateFireEntity(int iXIndex, int iYIndex, CEntity_Fire::FIRE_STATE cFireState)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("FIYAH", 2, 5);
	temp_mesh->textureID = LoadTGA("Image//Entities//fire.tga");

	CEntity_Fire* fire = new CEntity_Fire(iXIndex, iYIndex, cFireState, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(fire);
	return fire;
}

CEntity_Block_Movable* CLevel::GenerateMovableBlockEntity(int iXIndex, int iYIndex)
{
	Mesh* temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("Box", 1, 1);
	temp_mesh->textureID = LoadTGA("Image//Entities//box.tga");

	CEntity_Block_Movable* entity = new CEntity_Block_Movable(iXIndex, iYIndex, this->m_cTilemap, dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayerPtr, &m_cEntityIPosList);
	m_cEntityIPosList.push_back(entity);

	return entity;
}