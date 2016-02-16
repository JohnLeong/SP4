#include "Tilemap.h"
#include "Entities\Entity.h"
#include <string>
#include <vector>

class CLevel
{
public:
	CLevel(void);
	~CLevel(void);

	CTilemap* GetTilemap(void);
	bool InitTilemap(std::string mapname, int iNumTileX, int iNumTileY, float fTileSize);

private:
	//Main tile map
	CTilemap* m_cTilemap;
	//List of entities
	std::vector<CEntity*> m_cEntityList;
};
