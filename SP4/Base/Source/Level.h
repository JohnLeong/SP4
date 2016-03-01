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
#include "Entities\Entity_DemonFire.h"
#include "Entities\Entity_Coin.h"
#include "Entities\Entity_TextBox.h"
#include "Player\Player.h"
#include <string>
#include <vector>
#include "LuaScript.h"

class CLevel
{
public:

	CLevel(void);
	~CLevel(void);

	CTilemap* GetTilemap(void);
	bool LoadTilemap(std::string mapname);
	bool InitLua(std::string levelName);

	int GetPlayerStartPosX();
	int GetPlayerStartPosY();

	void Update(const float dt, CPlayer* cPlayer);
	void UpdateMovement(const float dt, CPlayer* cPlayer);

	void Reset(void);
	void Exit(void);

	//List of entities
	std::vector<CEntityIPos*> m_cEntityIPosList;
	std::vector<CTextBox*> m_cTextBoxList;
	//Main tile map
	CTilemap* m_cTilemap;
	CLuaScript* m_cLuascript;

	void SetDoMovements(bool bDoMovements);
	bool CheckPlayerCollisions(CPlayer* cPlayer);
	bool CheckEntityCollisions(CPlayer* cPlayer, int iXIndex, int iYIndex);

	bool IsMovementReady(void);
	void SetMovementReady(bool b);

	void SetPlayerPtr(CPlayer* cPlayer);

	int GetNumberOfMoves(void);			//Return number of moves player has taken
	int GetTotalCoins(void);			//Return total amount of coins in level
	int GetSmallestMoves(void);			//Return minimum amount of steps taken to complete level

	int CalculateScore(void);
	int GetNumStars(void);

	void SetLevelName(std::string name);

	//Generate entities
	CEnemyZombie* GenerateZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDING_OBJ_TYPE t);
	CEnemySuperRetardZombie* GenerateSuperRetardZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDING_OBJ_TYPE t);

	CEntity_Key_Red* GenerateRedKeyEntity(int iXIndex, int iYIndex);
	CEntity_Key_Blue* GenerateBlueKeyEntity(int iXIndex, int iYIndex);
	CEntity_Key_Green* GenerateGreenKeyEntity(int iXIndex, int iYIndex);
	CEntity_Key_Yellow* GenerateYellowKeyEntity(int iXIndex, int iYIndex);

	CEntity_Coin* GenerateCoinEntity(int iXIndex, int iYIndex);
	CEntity_Fire* GenerateFireEntity(int iXIndex, int iYIndex, CEntity_Fire::FIRE_STATE);
	CEntity_DemonFire* GenerateDemonFireEntity(int iXIndex, int iYIndex, CEntity_DemonFire::FIRE_STATE);
	CEntity_Block_Movable* GenerateMovableBlockEntity(int iXIndex, int iYIndex);

	CTextBox* GenerateTextBoxEntity(int iXIndex, int iYIndex, std::string text);
private:
	bool m_bDoMovements;
	int playerStartPosX, playerStartPosY, posX, posY, enemyHoldItem, maxNumberOfCurrentEntity, initialStage;
	bool m_bMovementReady;		//Controller for next player movement
	bool m_bDoTileCheck;			//Check tiles player and entities are standing on
	bool m_bPanicMode;
	CPlayer* m_cPlayerPtr;
	int m_iPlayerMoves;			//Total amount of moves the player has taken
	int m_iTotalCoins;
	int m_iMinMoves;
	int m_iStars;
	std::string m_strLevelName;
};

#endif