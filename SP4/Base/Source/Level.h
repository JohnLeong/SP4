#ifndef LEVEL_H
#define LEVEL_H

#include "Tilemap.h"
#include "Entities\EnemyZombie.h"
#include "Entities\EnemySuperRetardZombie.h"
#include "Entities\Entity_Block_Movable.h"
#include "Entities\Entity_Key_Red.h"
#include "Entities\Entity_Key_Blue.h"
#include "Entities\Entity_Key_Green.h"
#include "Entities\Entity_Key_Yellow.h"
#include "Entities\Entity_Fire.h"
#include "Entities\Entity_Coin.h"
#include "Player\Player.h"
#include <string>
#include <vector>
#include "LuaScript.h"

class CLevel
{
public:
	enum ENTITY_TO_CREATE
	{
		ENTITY_KEY_RED,
		ENTITY_KEY_BLUE,
		ENTITY_KEY_GREEN,
	};
	CLevel(void);
	~CLevel(void);

	CTilemap* GetTilemap(void);
	bool LoadTilemap(std::string mapname);
	bool InitLua(std::string levelName);

	int GetPlayerStartPosX();
	int GetPlayerStartPosY();

	void Update(const float dt, CPlayer* cPlayer);
	void UpdateMovement(const float dt, CPlayer* cPlayer);

	//List of entities
	std::vector<CEntityIPos*> m_cEntityIPosList;
	//Main tile map
	CTilemap* m_cTilemap;
	CLuaScript* m_cLuascript;

	void SetDoMovements(bool bDoMovements);
	bool CheckPlayerCollisions(CPlayer* cPlayer);
	bool CheckEntityCollisions(CPlayer* cPlayer, int iXIndex, int iYIndex);

	bool IsMovementReady(void);
	void SetMovementReady(bool b);

	void SetPlayerPtr(CPlayer* cPlayer);

	//Generate entities
	CEnemyZombie* GenerateZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDING_OBJ_TYPE t);
	CEnemySuperRetardZombie* GenerateSuperRetardZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDING_OBJ_TYPE t);
	CEntity_Key_Red* GenerateRedKeyEntity(int iXIndex, int iYIndex);
	CEntity_Key_Blue* GenerateBlueKeyEntity(int iXIndex, int iYIndex);
	CEntity_Key_Green* GenerateGreenKeyEntity(int iXIndex, int iYIndex);
	CEntity_Key_Yellow* GenerateYellowKeyEntity(int iXIndex, int iYIndex);
	CEntity_Coin* GenerateCoinEntity(int iXIndex, int iYIndex);
	CEntity_Fire* GenerateFireEntity(int iXIndex, int iYIndex, CEntity_Fire::FIRE_STATE);
	CEntity_Block_Movable* GenerateMovableBlockEntity(int iXIndex, int iYIndex);

private:
	bool m_bDoMovements;
	int playerStartPosX, playerStartPosY, posX, posY, enemyHoldItem, maxNumberOfZombies, maxNumberOfRetardZombies, maxNumberOfBlocks, maxNumberOfCoins;
	bool m_bMovementReady;		//Controller for next player movement
	bool m_bDoTileCheck;			//Check tiles player and entities are standing on
	CPlayer* m_cPlayerPtr;

};

#endif