#include "Player.h"

CPlayer::CPlayer()
: direction(PD_DOWN)
, action(PA_IDLE_DOWN)
, m_NextDir(PD_NONE)
{

}


CPlayer::~CPlayer(void)
{
}

// Initialise this class instance
void CPlayer::Init(CTilemap* cTilemap, int playerPos_x, int playerPos_y, SpriteAnimation* sprite, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_cTilemap = cTilemap;
	this->m_cEntityList = cEntityList;
	m_iXIndex = playerPos_x;
	m_iYIndex = playerPos_y;

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

bool CPlayer::MoveUpDown(const bool mode, CTilemap* tile)
{
	if (moving == false)
	{
		if (mode == true)
		{//Up
			moving = true;
			offSetDirectionY = true;
			XYDirection = true;
			return true;
		}
		else if (mode == false)
		{
			moving = true;
			offSetDirectionY = false;
			XYDirection = true;
			return true;
		}
	}
	return false;
}

bool CPlayer::MoveLeftRight(const bool mode, CTilemap* tile)
{
	if (moving == false)
	{
		if (mode == true)
		{//Right
			moving = true;
			offSetDirectionX = true;
			XYDirection = false;
			return true;
		}
		else if (mode == false)
		{//Left
			moving = true;
			offSetDirectionX = false;
			XYDirection = false;
			return true;
		}
	}
	return false;
}

CPlayer::PlayerDirection CPlayer::GetDirection(void)
{
	return this->direction;
}

CPlayer::PlayerDirection CPlayer::GetNextDirection(void)
{
	return this->m_NextDir;
}

Vector3 CPlayer::GetNextDirectionPosition(void)
{
	switch (m_NextDir)
	{
	case PD_UP:
		return (Vector3(this->m_iXIndex, this->m_iYIndex - 1, 0));
	case PD_DOWN:
		return (Vector3(this->m_iXIndex, this->m_iYIndex + 1, 0));
	case PD_RIGHT:
		return (Vector3(this->m_iXIndex + 1, this->m_iYIndex, 0));
	case PD_LEFT:
		return (Vector3(this->m_iXIndex - 1, this->m_iYIndex, 0));
	default:
		return (Vector3(this->m_iXIndex, this->m_iYIndex, 0));
	}
	return (Vector3(this->m_iXIndex, this->m_iYIndex, 0));
}

bool CPlayer::IsMoving(void)
{
	return moving;
}

void CPlayer::SetNextDirection(CPlayer::PlayerDirection p)
{
	this->m_NextDir = p;
	this->direction = p;
}

void CPlayer::DoCurrentTileCollision(CTilemap* cTilemap)
{
	switch (cTilemap->GetTile(this->m_iXIndex, this->m_iYIndex).GetCollisionType())
	{
	case CTiledata::COL_VOID:
		moving = false;
		break;
	case CTiledata::COL_ICE:
		if (cTilemap->GetTile(GetNextDirectionPosition().x, GetNextDirectionPosition().y).GetCollisionType() != CTiledata::COL_BLOCK)
		{
			for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
			{
				if (static_cast<int>(GetNextDirectionPosition().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPosition().y) == (*entity)->GetYIndex())
				{
					moving = false;
					break;
				}
			}
		}
		else
			moving = false;
		break;
	case CTiledata::COL_HAZARD:
		//Do player death here
		moving = false;
		break;
	case CTiledata::COL_BLOCK:
		std::cout << "ERMAHGAD COLLISION ERROR" << std::endl;
		break;
	default:
		break;
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
				this->m_fOffSetY += dt * ENTITY_MOVE_SPEED;
				if (this->m_fOffSetY > tile->GetTileSize())
				{
					this->m_fOffSetY = 0;
					m_iYIndex -= 1;
					DoCurrentTileCollision(tile);
				}
			}
			else
			{
				m_fOffSetY -= dt * ENTITY_MOVE_SPEED;
				if (m_fOffSetY < -tile->GetTileSize())
				{
					m_fOffSetY = 0;
					m_iYIndex += 1;
					DoCurrentTileCollision(tile);
				}
			}
		}
		else
		{
			if (offSetDirectionX)
			{
				m_fOffSetX += dt * ENTITY_MOVE_SPEED;
				if (m_fOffSetX > tile->GetTileSize())
				{
					m_fOffSetX = 0;
					m_iXIndex += 1;
					DoCurrentTileCollision(tile);
				}
			}
			else
			{
				m_fOffSetX -= dt * ENTITY_MOVE_SPEED;
				if (m_fOffSetX < -tile->GetTileSize())
				{
					m_fOffSetX = 0;
					m_iXIndex -= 1;
					DoCurrentTileCollision(tile);
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