#include "Tilemap.h"
#include "Entities\EnemyZombie.h"
#include <string>
#include <vector>

class CLevel
{
public:
	CLevel(void);
	~CLevel(void);

	CTilemap* GetTilemap(void);
	bool InitTilemap(std::string mapname, int iNumTileX, int iNumTileY, float fTileSize);

	//List of entities
	std::vector<CEntityIPos*> m_cEntityIPosList;
	//Main tile map
	CTilemap* m_cTilemap;
private:


};
