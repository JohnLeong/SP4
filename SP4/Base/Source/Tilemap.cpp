#include "Tilemap.h"

CTilemap::CTilemap(void)
:theNumOfTiles_MapHeight(0)
, theNumOfTiles_MapWidth(0)
, theTileSize(0)
{
	theScreenMap.clear();
	for (int i = 0; i < CTiledata::NUM_TILE; ++i)
	{
		meshArray[i] = NULL;
	}
}

CTilemap::~CTilemap(void)
{
	theScreenMap.clear();
}

void CTilemap::Init(int theNumOfTiles_Height, int theNumOfTiles_Width, float theTileSize)
{
	this->theTileSize			= theTileSize;

	theNumOfTiles_MapHeight = theNumOfTiles_Height;
	theNumOfTiles_MapWidth = theNumOfTiles_Width;

	theScreenMap.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		theScreenMap[i].resize(theNumOfTiles_MapWidth);
}

bool CTilemap::LoadMap(const string mapName)
{
	if (LoadFile(mapName) == true)
	{
		printf("Map (%s) has been successfully loaded!\n", mapName.c_str());
		return true;
	}

	
	return false;
}

bool CTilemap::LoadFile(const string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	ifstream file(mapName.c_str());
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			string aLineOfText = "";
			getline(file, aLineOfText);

			if  (theLineCounter>=theNumOfTiles_MapHeight)
				break;

			//Do not read if line is commented out
			if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						//Get total number of colums
						theMaxNumOfColumns = atoi(token.c_str());
					}
				}
				else
				{
					int theColumnCounter = 0;

					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						//Cast to Tile Id enum
						theScreenMap[theLineCounter][theColumnCounter].SetTileId(static_cast<CTiledata::TILE_ID>(atoi(token.c_str())));
						//Get Collision type based on tile id
						theScreenMap[theLineCounter][theColumnCounter].SetCollisionType(GetCollisionTypeFromId(theScreenMap[theLineCounter][theColumnCounter].GetTileId()));
						++theColumnCounter;
					}
				}
			}

			theLineCounter++;
		}
	}
	return true;
}

int CTilemap::GetNumOfTiles_Height(void)
{
	return theNumOfTiles_MapHeight;
}

int CTilemap::GetNumOfTiles_Width(void)
{
	return theNumOfTiles_MapWidth;
}

int CTilemap::GetTileSize(void)
{
	return theTileSize;
}

CTiledata CTilemap::GetTile(int XIndex, int YIndex)
{
	if (XIndex >= theNumOfTiles_MapWidth || YIndex >= theNumOfTiles_MapHeight)
	{
		std::cout << "Tile map out of range"<<std::endl;
		return theScreenMap[0][0];
	}
	return theScreenMap[XIndex][YIndex];
}