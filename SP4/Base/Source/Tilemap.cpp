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

void CTilemap::Init(int theNumOfTiles_Width, const int theNumOfTiles_Height, float theTileSize)
{
	this->theTileSize			= theTileSize;

	theNumOfTiles_MapHeight = theNumOfTiles_Height;
	theNumOfTiles_MapWidth = theNumOfTiles_Width;

	theScreenMap.resize(theNumOfTiles_MapWidth);
	for (int i = 0; i < theNumOfTiles_MapWidth; ++i)
		theScreenMap[i].resize(theNumOfTiles_Height);
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
			//if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				//if (theLineCounter == 0)
				//{
				//	string token;
				//	istringstream iss(aLineOfText);
				//	while(getline(iss, token, ','))
				//	{
				//		//Get total number of colums
				//		theMaxNumOfColumns = atoi(token.c_str());
				//	}
				//}
				//else
				{
					int theColumnCounter = 0;

					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						//Cast to Tile Id enum
						theScreenMap[theColumnCounter][theLineCounter].SetTileId(static_cast<CTiledata::TILE_ID>(atoi(token.c_str())));
						//Get Collision type based on tile id
						theScreenMap[theColumnCounter][theLineCounter].SetCollisionType(GetCollisionTypeFromId(theScreenMap[theColumnCounter][theLineCounter].GetTileId()));
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

float CTilemap::GetTileSize(void)
{
	return theTileSize;
}

void CTilemap::SetMeshArray(CTiledata::TILE_ID TileId, SpriteAnimation* sa, Animation* anim)
{
	meshArray[TileId] = sa;
	meshArray[TileId]->m_anim = anim;
}

SpriteAnimation* CTilemap::GetTileSprite(CTiledata::TILE_ID TileId)
{
	return (meshArray[TileId]);
}

void CTilemap::UpdateSprites(double dt)
{
	for (int i = 0; i < CTiledata::NUM_TILE; ++i)
	{
		if (meshArray[i] == NULL)
			continue;
		meshArray[i]->Update(dt);
	}
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

bool CTilemap::AllowCollision(int iXIndex, int iYIndex)
{
	if (theScreenMap[iXIndex][iYIndex].GetCollisionType() == CTiledata::COL_BLOCK ||
		theScreenMap[iXIndex][iYIndex].GetCollisionType() == CTiledata::COL_HOLE ||
		theScreenMap[iXIndex][iYIndex].GetCollisionType() == CTiledata::COL_LOCK_RED ||
		theScreenMap[iXIndex][iYIndex].GetCollisionType() == CTiledata::COL_LOCK_BLUE ||
		theScreenMap[iXIndex][iYIndex].GetCollisionType() == CTiledata::COL_LOCK_GREEN ||
		theScreenMap[iXIndex][iYIndex].GetCollisionType() == CTiledata::COL_LOCK_YELLOW)
		return false;
	return true;
}