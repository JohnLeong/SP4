#include "Player.h"

CPlayer::CPlayer() 
:playerPosX(0)
,playerPosY(0)
{
	//playerPos.SetZero();
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
		playerPosY += 1;
	}
	else if (mode == false)
	{
		playerPosY -= 1;
	}
}

void CPlayer::MoveLeftRight(const bool mode, CTilemap* tile)
{
	if (mode == true)
	{
		playerPosX += 1;
	}
	else if (mode == false)
	{
		playerPosX -= 1;
	}
}

/********************************************************************************
Update
********************************************************************************/
void CPlayer::Update()
{
}