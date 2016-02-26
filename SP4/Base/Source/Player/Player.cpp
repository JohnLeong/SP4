#include "Player.h"

CPlayer::CPlayer()
: direction(PD_DOWN)
, action(PA_IDLE_DOWN)
, m_NextDir(PD_NONE)
, m_iCoins(0)
, m_iKeys_red(0)
, m_iKeys_blue(0)
, m_iKeys_green(0)
, m_iKeys_yellow(0)
, m_bHasReachedEndLevel(false)
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
	_a->Set(0, 2, 0, 0.15f);
	AddAnimation(_a, PA_WALK_DOWN);

	//Walk East
	_a = new Animation();
	_a->Set(3, 5, 0, 0.15f);
	AddAnimation(_a, PA_WALK_UP);

	//Walk East
	_a = new Animation();
	_a->Set(6, 8, 0, 0.15f);
	AddAnimation(_a, PA_WALK_RIGHT);

	//Walk North
	_a = new Animation();
	_a->Set(9, 11, 0, 0.15f);
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

//Vector3 CPlayer::GetNextDirectionPosition(void)
//{
//	switch (m_NextDir)
//	{
//	case PD_UP:
//		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex - 1), 0));
//	case PD_DOWN:
//		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex + 1), 0));
//	case PD_RIGHT:
//		return (Vector3(static_cast<float>(this->m_iXIndex + 1), static_cast<float>(this->m_iYIndex), 0));
//	case PD_LEFT:
//		return (Vector3(static_cast<float>(this->m_iXIndex - 1), static_cast<float>(this->m_iYIndex), 0));
//	default:
//		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex), 0));
//	}
//	return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex), 0));
//}

Vector3 CPlayer::GetNextDirectionPos(void)
{
	switch (m_NextDir)
	{
	case PD_UP:
		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex - 1), 0));
	case PD_DOWN:
		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex + 1), 0));
	case PD_RIGHT:
		return (Vector3(static_cast<float>(this->m_iXIndex + 1), static_cast<float>(this->m_iYIndex), 0));
	case PD_LEFT:
		return (Vector3(static_cast<float>(this->m_iXIndex - 1), static_cast<float>(this->m_iYIndex), 0));
	default:
		return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex), 0));
	}
	return (Vector3(static_cast<float>(this->m_iXIndex), static_cast<float>(this->m_iYIndex), 0));
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
	for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
	{
		if ((*entity)->GetXIndex() == this->m_iXIndex && (*entity)->GetYIndex() == this->m_iYIndex && (*entity)->DeathOnEntry() && (*entity)->IsAlive())
		{
			moving = false;
			this->SetAlive(false);
			return;
		}
	}
	switch (cTilemap->GetTile(this->m_iXIndex, this->m_iYIndex).GetCollisionType())
	{
	case CTiledata::COL_VOID:
		moving = false;
		break;
	case CTiledata::COL_ICE:
		if (cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
		{
			for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
			{
				if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
				{
					switch (m_NextDir)
					{
					case CPlayer::PD_UP:
						if ((*entity)->DoColDir(CEntityIPos::DIR_UP))
							moving = false;
						break;
					case CPlayer::PD_DOWN:
						if ((*entity)->DoColDir(CEntityIPos::DIR_DOWN))
							moving = false;
						break;
					case CPlayer::PD_RIGHT:
						if ((*entity)->DoColDir(CEntityIPos::DIR_RIGHT))
							moving = false;
						break;
					case CPlayer::PD_LEFT:
						if ((*entity)->DoColDir(CEntityIPos::DIR_LEFT))
							moving = false;
						break;
					default:
						break;
					}

					break;
				}
			}
		}
		else
			moving = false;
		break;
	case CTiledata::COL_HAZARD:
		this->m_bAlive = false;
		moving = false;
		break;
	case CTiledata::COL_WIND_UP:
		moving = false;
		m_NextDir = PD_UP;
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
			break;
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex() && (*entity)->IsAlive())
			{
				if ((*entity)->DoColDir(CEntityIPos::DIR_UP))
					moving = false;
				else
					MoveUpDown(true, cTilemap);
				return;
			}
		}
		MoveUpDown(true, cTilemap);
		break;
	case CTiledata::COL_WIND_DOWN:
		moving = false;
		m_NextDir = PD_DOWN;
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
			break;
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex() && (*entity)->IsAlive())
			{
				if ((*entity)->DoColDir(CEntityIPos::DIR_DOWN))
					moving = false;
				else
					MoveUpDown(false, cTilemap);
				return;
			}
		}
		MoveUpDown(false, cTilemap);
		break;
	case CTiledata::COL_WIND_LEFT:
		moving = false;
		m_NextDir = PD_LEFT;
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
			break;
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex() && (*entity)->IsAlive())
			{
				if ((*entity)->DoColDir(CEntityIPos::DIR_LEFT))
					moving = false;
				else
					MoveLeftRight(false, cTilemap);
				return;
			}
		}
		MoveLeftRight(false, cTilemap);
		break;
	case CTiledata::COL_WIND_RIGHT:
		moving = false;
		m_NextDir = PD_RIGHT;
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
			break;
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex() && (*entity)->IsAlive())
			{
				if ((*entity)->DoColDir(CEntityIPos::DIR_RIGHT))
					moving = false;
				else
					MoveLeftRight(true, cTilemap);
				return;
			}
		}
		MoveLeftRight(true, cTilemap);
		break;
	case CTiledata::COL_BLOCK:
		std::cout << "ERMAHGAD COLLISION ERROR" << std::endl;
		break;
	case CTiledata::COL_ENDLEVEL:
		moving = false;
		m_bHasReachedEndLevel = true;
		break;
	default:
		moving = false;
		break;
	}
}

/********************************************************************************
Update
********************************************************************************/
void CPlayer::Update(double dt, CTilemap* tile)
{
	if (!m_bAlive)
	{
		m_fDeathOffSetX += dt * 80.f;
		m_fDeathOffSetY = (((m_fDeathOffSetX * m_fDeathOffSetX) - (2 * m_fDeathOffSetX) - 3) * 0.1) - 67;

		if (m_fDeathOffSetY > 300)
			m_bActive = false;
		return;
	}
	if (moving == true)
	{
		if (XYDirection)
		{
			if (offSetDirectionY)
			{
				this->m_fOffSetY += static_cast<float>(dt)* ENTITY_MOVE_SPEED;
				if (this->m_fOffSetY > tile->GetTileSize())
				{
					this->m_fOffSetY = 0;
					m_iYIndex -= 1;
					DoCurrentTileCollision(tile);
				}
			}
			else
			{
				m_fOffSetY -= static_cast<float>(dt)* ENTITY_MOVE_SPEED;
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
				m_fOffSetX += static_cast<float>(dt) * ENTITY_MOVE_SPEED;
				if (m_fOffSetX > tile->GetTileSize())
				{
					m_fOffSetX = 0;
					m_iXIndex += 1;
					DoCurrentTileCollision(tile);
				}
			}
			else
			{
				m_fOffSetX -= static_cast<float>(dt)* ENTITY_MOVE_SPEED;
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

int CPlayer::GetCoins(void)
{
	return m_iCoins;
}
//Get the number of red keys
int CPlayer::GetKeys_Red(void)
{
	return m_iKeys_red;
}
//Get the number of blue keys
int CPlayer::GetKeys_Blue(void)
{
	return m_iKeys_blue;
}
//Get the number of green keys
int CPlayer::GetKeys_Green(void)
{
	return m_iKeys_green;
}
//Get the number of yyellow keys
int CPlayer::GetKeys_Yellow(void)
{
	return m_iKeys_yellow;
}

void CPlayer::Reset(void)
{
	this->m_iCoins = 0;
	this->m_iKeys_red = 0;
	this->m_iKeys_blue = 0;
	this->m_iKeys_yellow = 0;
	this->m_iKeys_green = 0;
}

void CPlayer::AddKeys(int iAmt, int type)
{
	//0 = red keys, 1 = blue keys, 2 = green keys, 3 = yellow keys
	switch (type) 
	{
	case 0:
		//add to red keys
		this->m_iKeys_red += iAmt;
		break;

	case 1:
		//add to blue keys
		this->m_iKeys_blue += iAmt;
		break;

	case 2:
		//add to green keys
		this->m_iKeys_green += iAmt;
		break;

	case 3:
		//add to yellow keys
		this->m_iKeys_yellow += iAmt;
		break;
	}

}

void CPlayer::AddCoin(int iAmt)
{
	this->m_iCoins += iAmt;
}

bool CPlayer::GetHasReachedEndLevel(void)
{
	return m_bHasReachedEndLevel;
}

void CPlayer::UseItem(ITEM_SLOT item)
{
	switch (item)
	{
	case CPlayer::SLOT_01:
		if (m_iKeys_green > 0)
		{
			if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex + 1).GetCollisionType() == CTiledata::COL_LOCK_GREEN)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex + 1].ChangeIdState();
				--m_iKeys_green;
			}
			else if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex - 1).GetCollisionType() == CTiledata::COL_LOCK_GREEN)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex - 1].ChangeIdState();
				--m_iKeys_green;
			}
			else if (m_cTilemap->GetTile(m_iXIndex + 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_GREEN)
			{
				m_cTilemap->theScreenMap[m_iXIndex + 1][m_iYIndex].ChangeIdState();
				--m_iKeys_green;
			}
			else if (m_cTilemap->GetTile(m_iXIndex - 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_GREEN)
			{
				m_cTilemap->theScreenMap[m_iXIndex - 1][m_iYIndex].ChangeIdState();
				--m_iKeys_green;
			}
		}
		break;
	case CPlayer::SLOT_02:
		if (m_iKeys_yellow > 0)
		{
			if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex + 1).GetCollisionType() == CTiledata::COL_LOCK_YELLOW)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex + 1].ChangeIdState();
				--m_iKeys_yellow;
			}
			else if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex - 1).GetCollisionType() == CTiledata::COL_LOCK_YELLOW)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex - 1].ChangeIdState();
				--m_iKeys_yellow;
			}
			else if (m_cTilemap->GetTile(m_iXIndex + 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_YELLOW)
			{
				m_cTilemap->theScreenMap[m_iXIndex + 1][m_iYIndex].ChangeIdState();
				--m_iKeys_yellow;
			}
			else if (m_cTilemap->GetTile(m_iXIndex - 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_YELLOW)
			{
				m_cTilemap->theScreenMap[m_iXIndex - 1][m_iYIndex].ChangeIdState();
				--m_iKeys_yellow;
			}
		}
		break;
	case CPlayer::SLOT_03:
		if (m_iKeys_blue > 0)
		{
			if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex + 1).GetCollisionType() == CTiledata::COL_LOCK_BLUE)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex + 1].ChangeIdState();
				--m_iKeys_blue;
			}
			else if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex - 1).GetCollisionType() == CTiledata::COL_LOCK_BLUE)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex - 1].ChangeIdState();
				--m_iKeys_blue;
			}
			else if (m_cTilemap->GetTile(m_iXIndex + 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_BLUE)
			{
				m_cTilemap->theScreenMap[m_iXIndex + 1][m_iYIndex].ChangeIdState();
				--m_iKeys_blue;
			}
			else if (m_cTilemap->GetTile(m_iXIndex - 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_BLUE)
			{
				m_cTilemap->theScreenMap[m_iXIndex - 1][m_iYIndex].ChangeIdState();
				--m_iKeys_blue;
			}
		}
		break;
	case CPlayer::SLOT_04:
		if (m_iKeys_red > 0)
		{
			if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex + 1).GetCollisionType() == CTiledata::COL_LOCK_RED)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex + 1].ChangeIdState();
				--m_iKeys_red;
			}
			else if (m_cTilemap->GetTile(m_iXIndex, m_iYIndex - 1).GetCollisionType() == CTiledata::COL_LOCK_RED)
			{
				m_cTilemap->theScreenMap[m_iXIndex][m_iYIndex - 1].ChangeIdState();
				--m_iKeys_red;
			}
			else if (m_cTilemap->GetTile(m_iXIndex + 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_RED)
			{
				m_cTilemap->theScreenMap[m_iXIndex + 1][m_iYIndex].ChangeIdState();
				--m_iKeys_red;
			}
			else if (m_cTilemap->GetTile(m_iXIndex - 1, m_iYIndex).GetCollisionType() == CTiledata::COL_LOCK_RED)
			{
				m_cTilemap->theScreenMap[m_iXIndex - 1][m_iYIndex].ChangeIdState();
				--m_iKeys_red;
			}
		}
		break;
	default:
		break;
	}
}