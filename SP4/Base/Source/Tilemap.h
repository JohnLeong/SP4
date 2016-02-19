#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Tileinfo.h"
#include "Mesh.h"
#include "Graphics\SpriteAnimation.h"
using namespace std;

class CTilemap
{
public:
	CTilemap(void);
	~CTilemap(void);

	void Init(const int theNumOfTiles_Width, const int theNumOfTiles_Height, const float theTileSize = 25.f);
	bool LoadMap(const string mapName);
	int GetNumOfTiles_Height(void);		// Get the number of tiles for height of the screen
	int GetNumOfTiles_Width(void);		// Get the number of tiles for width of the screen
	float GetTileSize(void);
	CTiledata GetTile(int XIndex, int YIndex);
	void SetMeshArray(CTiledata::TILE_ID TileId, SpriteAnimation* sa, Animation* anim);	//Set the mesh for the specified tile index
	SpriteAnimation* GetTileSprite(CTiledata::TILE_ID TileId);

	vector<vector<CTiledata> > theScreenMap;

	void UpdateSprites(double dt);

private:
	float theTileSize;

	int theNumOfTiles_MapHeight;	// Number of tiles in the map's height
	int theNumOfTiles_MapWidth;		// Number of tiles in the map's width

	bool LoadFile(const string mapName);

	SpriteAnimation* meshArray[CTiledata::NUM_TILE];
};
