#include "Player.h"

CPlayer::CPlayer()
: playerPosX(0)
, playerPosY(0)
, direction(PD_DOWN)
, action(PA_IDLE_DOWN)
, xOffSet(0.f)
, yOffSet(0.f)
{

}


CPlayer::~CPlayer(void)
{
}

// Initialise this class instance
void CPlayer::Init(int playerPos_x, int playerPos_y, SpriteAnimation* sprite)
{
	playerPosX = playerPos_x;
	playerPosY = playerPos_y;

	moving = false;

	//Initialise the Avatar's movement flags
	for (int i = 0; i < 255; i++){
		myKeys[i] = false;
	}

	Animation* _a;
	//Idle South
	_a = new Animation();
	_a->Set(1, 1, 0, 0.f);
	AddAnimation(_a, PA_IDLE_DOWN);

	//Idle East
	_a = new Animation();
	_a->Set(4, 4, 0, 0.f);
	AddAnimation(_a, PA_IDLE_UP);

	//Idle East
	_a = new Animation();
	_a->Set(7, 7, 0, 0.f);
	AddAnimation(_a, PA_IDLE_RIGHT);

	//Idle North
	_a = new Animation();
	_a->Set(10, 10, 0, 0.f);
	AddAnimation(_a, PA_IDLE_LEFT);

	//Walk South
	_a = new Animation();
	_a->Set(0, 2, 0, 0.8f);
	AddAnimation(_a, PA_WALK_DOWN);

	//Walk East
	_a = new Animation();
	_a->Set(3, 5, 0, 0.4f);
	AddAnimation(_a, PA_WALK_UP);

	//Walk East
	_a = new Animation();
	_a->Set(6, 8, 0, 0.4f);
	AddAnimation(_a, PA_WALK_RIGHT);

	//Walk North
	_a = new Animation();
	_a->Set(9, 11, 0, 0.4f);
	AddAnimation(_a, PA_WALK_LEFT);

	sprites = sprite;
}

//adds sprite animation depending on the state specified
void CPlayer::AddAnimation(Animation* _anim, PlayerAction playerState)
{
	m__animationList[playerState] = _anim;
}


SpriteAnimation* CPlayer::GetSpriteAnimation()
{
	return sprites;//mesh;
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

// Get position x of the player
float CPlayer::GetOffSet_x(void)
{
	return xOffSet;
}

// Get position y of the player
float CPlayer::GetOffSet_y(void)
{
	return yOffSet;
}

void CPlayer::MoveUpDown(const bool mode, CTilemap* tile)
{
	if (moving == false)
	{
		if (mode == true)
		{
			if (playerPosY == tile->GetNumOfTiles_Height() - 1 || CheckCollision(tile->GetTile(playerPosX, playerPosY + 1)) == COL_WALL)
			{
			}
			else
			{
				moving = true;
				offSetDirectionY = true;
				XYDirection = true;
				direction = PD_UP;
			}
		}
		else if (mode == false)
		{
			if (playerPosY == 0 || CheckCollision(tile->GetTile(playerPosX, playerPosY - 1)) == COL_WALL)
			{
			}
			else
			{
				moving = true;
				offSetDirectionY = false;
				XYDirection = true;
				direction = PD_DOWN;
			}
		}
	}
}

void CPlayer::MoveLeftRight(const bool mode, CTilemap* tile)
{
	if (moving == false)
	{
		if (mode == true)
		{
			if (playerPosX == tile->GetNumOfTiles_Width() - 1 || CheckCollision(tile->GetTile(playerPosX + 1, playerPosY)) == COL_WALL)
			{
			}
			else
			{
				moving = true;
				offSetDirectionX = true;
				XYDirection = false;
				direction = PD_RIGHT;
			}

		}
		else if (mode == false)
		{
			if (playerPosX == 0 || CheckCollision(tile->GetTile(playerPosX - 1, playerPosY)) == COL_WALL)
			{
			}
			else
			{
				moving = true;
				offSetDirectionX = false;
				XYDirection = false;
				direction = PD_LEFT;
			}
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
void CPlayer::Update(double dt, CTilemap* tile)
{

	if (moving == true)
	{
		if (XYDirection)
		{
			if (offSetDirectionY)
			{
				yOffSet += dt * 100;
				if (yOffSet > tile->GetTileSize())
				{
					yOffSet = 0;
					playerPosY += 1;
					moving = false;
				}
			}
			else
			{
				yOffSet -= dt * 100;
				if (yOffSet < -tile->GetTileSize())
				{
					yOffSet = 0;
					playerPosY -= 1;
					moving = false;
				}
			}
		}
		else
		{
			if (offSetDirectionX)
			{
				xOffSet += dt * 100;
				if (xOffSet > tile->GetTileSize())
				{
					xOffSet = 0;
					playerPosX += 1;
					moving = false;
				}
			}
			else
			{
				xOffSet -= dt * 100;
				if (xOffSet < -tile->GetTileSize())
				{
					xOffSet = 0;
					playerPosX -= 1;
					moving = false;
				}
			}
		}
	}

	if (direction == PD_DOWN)
	{
		if (moving == false)
		{
			action = PA_IDLE_DOWN;
		}
		else
		{
			action = PA_WALK_DOWN;
		}
	}
	else if (direction == PD_UP)
	{
		if (moving == false)
		{
			action = PA_IDLE_UP;
		}
		else
		{
			action = PA_WALK_UP;
		}
	}
	else if (direction == PD_RIGHT)
	{
		if (moving == false)
		{
			action = PA_IDLE_RIGHT;
		}
		else
		{
			action = PA_WALK_RIGHT;
		}
	}
	else if (direction == PD_LEFT)
	{
		if (moving == false)
		{
			action = PA_IDLE_LEFT;
		}
		else
		{
			action = PA_WALK_LEFT;
		}
	}

	//update animation
	if (sprites)
	{
		sprites->m_anim = m__animationList[action];
		sprites->Update(dt);
	}
}