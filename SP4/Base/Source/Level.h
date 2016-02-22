#include "Tilemap.h"
#include "Entities\EnemyZombie.h"
#include "Entities\Entity_Block_Movable.h"
#include "Entities\Entity_Key_Red.h"
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
	bool InitTilemap(int iNumTileX, int iNumTileY, float fTileSize);
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
	CLuaScript* m_cluascript;

	void SetDoMovements(bool bDoMovements);
	bool CheckPlayerCollisions(CPlayer* cPlayer);
	bool CheckPlayerCollisionsCurrent(CPlayer* cPlayer);
	bool CheckEntityCollisions(CPlayer* cPlayer, int iXIndex, int iYIndex);

	bool IsMovementReady(void);
	void SetMovementReady(bool b);

	void SetPlayerPtr(CPlayer* cPlayer);

	CEnemyZombie* GenerateZombieEntity(int iXIndex, int iYIndex, CEnemy::HOLDINGKEY_TYPE t);
	CEntity_Key_Red* GenerateRedKeyEntity(int iXIndex, int iYIndex);
	CEntity_Coin* GenerateCoinEntity(int iXIndex, int iYIndex);

private:
	bool m_bDoMovements;
	int playerStartPosX, playerStartPosY, maxNumberOfEnemies;
	bool m_bMovementReady;		//Controller for next player movement
	bool m_bDoTileCheck;			//Check tiles player and entities are standing on
	CPlayer* m_cPlayerPtr;
};
