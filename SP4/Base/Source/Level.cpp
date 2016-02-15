#include "Level.h"

CLevel::CLevel(void)
{
}

CLevel::~CLevel(void)
{
}

CTilemap* CLevel::GetTilemap(void)
{
	return m_cTilemap;
}

bool CLevel::InitTilemap(std::string mapname, int iNumTileX, int iNumTileY, float fTileSize)
{
	/*if (m_cTilemap)
		delete m_cTilemap;*/

	m_cTilemap = new CTilemap();
	m_cTilemap->Init(iNumTileX, iNumTileY, fTileSize);

	return(m_cTilemap->LoadMap(mapname));
}