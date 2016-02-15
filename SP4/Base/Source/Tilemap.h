#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class CTilemap
{
public:
	CTilemap(void);
	~CTilemap(void);

	void Init(const int theNumOfTiles_Height, const int theNumOfTiles_Width, const float theTileSize=25.f);
	bool LoadMap(const string mapName);
	int GetNumOfTiles_Height(void);		// Get the number of tiles for height of the screen
	int GetNumOfTiles_Width(void);		// Get the number of tiles for width of the screen
	int GetTileSize(void);

	vector<vector<int> > theScreenMap;

private:
	int theTileSize;

	int theNumOfTiles_MapHeight;	// Number of tiles in the map's height
	int theNumOfTiles_MapWidth;		// Number of tiles in the map's width

	bool LoadFile(const string mapName);
};
