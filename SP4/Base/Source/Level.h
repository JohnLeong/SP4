#include "Tilemap.h"
#include "Entities\EnemyZombie.h"
#include "Entities\Entity_Block_Movable.h"
#include <string>
#include <vector>

class CLevel
{
public:
	CLevel(void);
	~CLevel(void);

	CTilemap* GetTilemap(void);
	bool InitTilemap(std::string mapname, int iNumTileX, int iNumTileY, float fTileSize);
	void Update(const float dt, CPlayer* cPlayer);
	void UpdateMovement(const float dt, CPlayer* cPlayer);

	//List of entities
	std::vector<CEntityIPos*> m_cEntityIPosList;
	//Main tile map
	CTilemap* m_cTilemap;

	void SetDoMovements(bool bDoMovements);
	void CheckEntityCollisions(CPlayer* cPlayer);
private:
	bool m_bDoMovements;

};
