#include "Tilemap.h"

CTilemap::CTilemap(void)
:theNumOfTiles_MapHeight(0)
, theNumOfTiles_MapWidth(0)
, theTileSize(0)
{
	theScreenMap.clear();
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

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
					//if ( theMaxNumOfColumns != theNumOfTiles_MapWidth)
						//return false;
				}
				else
				{
					int theColumnCounter = 0;

					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						theScreenMap[theLineCounter][theColumnCounter++] = atoi(token.c_str());
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
