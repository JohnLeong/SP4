#include "Player.h"

CPlayer::CPlayer() 
:playerPosX(0)
,playerPosY(0)
{
}


CPlayer::~CPlayer(void)
{
}

// Initialise this class instance
void CPlayer::Init(int playerPos_x, int playerPos_y)
{
	playerPosX = playerPos_x;
	playerPosY = playerPos_y;
	
	 //Initialise the Avatar's movement flags
	for (int i = 0; i<255; i++){
		myKeys[i] = false;
	}
}

//Set position x of the player
void CPlayer::SetPos_x(int pos_x)
{
	playerPosX = pos_x;
}

// Set position y of the player
void CPlayer::SetPos_y(int pos_y)
{
	playerPosY = pos_y;
}

// Get position x of the player
int CPlayer::GetPos_x(void)
{
	return playerPosX;
}

// Get position y of the player
int CPlayer::GetPos_y(void)
{
	return playerPosY;
}

void CPlayer::MoveUpDown(const bool mode, CTilemap* tile)
{
	if (mode == true)
	{
		if (playerPosY == tile->GetNumOfTiles_Height() - 1 || CheckCollision(tile->GetTile(playerPosX, playerPosY + 1)) == COL_WALL)
		{
		}
		else
		{
			playerPosY += 1;
		}
	}
	else if (mode == false)
	{
		if (playerPosY == 0 || CheckCollision(tile->GetTile(playerPosX, playerPosY - 1)) == COL_WALL)
		{
		}
		else
		{
			playerPosY -= 1;
		}
	}
}

void CPlayer::MoveLeftRight(const bool mode, CTilemap* tile)
{
	if (mode == true)
	{
		if (playerPosX == tile->GetNumOfTiles_Width() - 1 || CheckCollision(tile->GetTile(playerPosX + 1, playerPosY)) == COL_WALL)
		{
		}
		else
		{
			playerPosX += 1;
		}	
	}
	else if (mode == false)
	{
		if (playerPosX == 0 || CheckCollision(tile->GetTile(playerPosX - 1, playerPosY)) == COL_WALL)
		{
		}
		else
		{
			playerPosX -= 1;
		}
	}
}

CPlayer::CollisionReponse CPlayer::CheckCollision(CTiledata tileData)
{
	if (tileData.GetCollisionType() == tileData.COL_BLOCK)
	{
		return COL_WALL;
	}
	else
	{
		return COL_FLOOR;
	}
}

/********************************************************************************
Update
********************************************************************************/
void CPlayer::Update()
{
}