
#include "Tilemap.h"
#include <string>

class CLevel
{
public:
	CLevel(void);
	~CLevel(void);

	CTilemap* GetTilemap(void);
	bool InitTilemap(std::string mapname, int iNumTileX, int iNumTileY, float fTileSize);

private:
	CTilemap* m_cTilemap;
};
