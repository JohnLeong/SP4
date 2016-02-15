#include "Player.h"

CPlayer::CPlayer() :
playerPos(0)
{
	//playerPos.SetZero();
}


CPlayer::~CPlayer(void)
{
}

// Initialise this class instance
void CPlayer::Init(float playerPos_x, float playerPos_y)
{
	playerPos.Set(playerPos_x, playerPos_y, 0);
	
	 //Initialise the Avatar's movement flags
	for (int i = 0; i<255; i++){
		myKeys[i] = false;
	}
}

//Set position x of the player
void CPlayer::SetPos_x(float pos_x)
{
	playerPos.x = pos_x;
}

// Set position y of the player
void CPlayer::SetPos_y(float pos_y)
{
	playerPos.y = pos_y;
}

// Set position y of the player
void CPlayer::SetPos(Vector3 pos)
{
	playerPos = pos;
}

// Get position x of the player
float CPlayer::GetPos_x(void)
{
	return playerPos.x;
}

// Get position y of the player
float CPlayer::GetPos_y(void)
{
	return playerPos.y;
}

// Get position y of the player
Vector3 CPlayer::GetPos(void)
{
	return playerPos;
}

void CPlayer::MoveUpDown(const bool mode, CTilemap* tile)
{
	if (mode == true)
	{
		playerPos.y += tile->GetTileSize();
	}
	else if (mode == false)
	{
		playerPos.y -= tile->GetTileSize();
	}
}

void CPlayer::MoveLeftRight(const bool mode, CTilemap* tile)
{
	if (mode == true)
	{
		playerPos.x += tile->GetTileSize();
	}
	else if (mode == false)
	{
		playerPos.x -= tile->GetTileSize();
	}
}

/********************************************************************************
Update
********************************************************************************/
void CPlayer::Update()
{
}