#include "Tilemap.h"
#include "Entities\EnemyZombie.h"
#include "Entities\Entity_Block_Movable.h"
#include <string>
#include <vector>
#include "LuaScript.h"
class CLevel
{
public:
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

private:
	bool m_bDoMovements;
	int playerStartPosX, playerStartPosY, maxNumberOfEnemies;
	bool m_bMovementReady;		//Controller for next player movement
	bool m_bDoTileCheck;			//Check tiles player and entities are standing on
};
