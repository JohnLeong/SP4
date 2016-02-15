#include "Player.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer(void)
{
}

// Initialise this class instance
void CPlayer::Init(float playerPos_x, float playerPos_y)
{
	curPosition.Set(playerPos_x, playerPos_y);

	// Initialise the Avatar's movement flags
	for (int i = 0; i<255; i++){
		myKeys[i] = false;
	}
}

// Set position x of the player
void CPlayer::SetPos_x(float pos_x)
{
	curPosition.x = pos_x;
}

// Set position y of the player
void CPlayer::SetPos_y(float pos_y)
{
	curPosition.y = pos_y;
}

// Set position y of the player
void CPlayer::SetPos(Vector2 pos)
{
	curPosition = pos;
}

// Get position x of the player
float CPlayer::GetPos_x(void)
{
	return curPosition.x;
}

// Get position y of the player
float CPlayer::GetPos_y(void)
{
	return curPosition.y;
}

// Get position y of the player
Vector2 CPlayer::GetPos(void)
{
	return curPosition;
}

void CPlayer::MoveUpDown(const bool mode)
{

}

void CPlayer::MoveLeftRight(const bool mode)
{

}

/********************************************************************************
Update
********************************************************************************/
void CPlayer::Update()
{
	// WASD movement
	if (myKeys['w'] == true)
	{
		MoveUpDown(false);
	}
	else
	{
		//		MoveVel_W = 0.0f;
	}
	if (myKeys['s'] == true)
	{
		MoveUpDown(true);
	}
	else
	{
		//		MoveVel_S = 0.0f;
	}
	if (myKeys['a'] == true)
	{
		MoveLeftRight(true);
	}
	else
	{
		//		MoveVel_A = 0.0f;
	}
	if (myKeys['d'] == true)
	{
		MoveLeftRight(false);
	}
	else
	{
		//		MoveVel_D = 0.0f;
	}
}