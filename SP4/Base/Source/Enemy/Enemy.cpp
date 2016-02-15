#include "Enemy.h"

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy(void)
{
}

// Initialise this class instance
void CEnemy::Init(float enemyPos_x, float enemyPos_y)
{
	curPosition.Set(enemyPos_x, enemyPos_y);

	// Initialise the Avatar's movement flags
	for (int i = 0; i<255; i++){
		myKeys[i] = false;
	}
}

// Set position x of the player
void CEnemy::SetPos_x(float pos_x)
{
	curPosition.x = pos_x;
}

// Set position y of the player
void CEnemy::SetPos_y(float pos_y)
{
	curPosition.y = pos_y;
}

// Set position y of the player
void CEnemy::SetPos(Vector2 pos)
{
	curPosition = pos;
}

// Get position x of the player
float CEnemy::GetPos_x(void)
{
	return curPosition.x;
}

// Get position y of the player
float CEnemy::GetPos_y(void)
{
	return curPosition.y;
}

// Get position y of the player
Vector2 CEnemy::GetPos(void)
{
	return curPosition;
}

void CEnemy::MoveUpDown(const bool mode)
{

}

void CEnemy::MoveLeftRight(const bool mode)
{

}

/********************************************************************************
Update
********************************************************************************/
void CEnemy::Update()
{

}