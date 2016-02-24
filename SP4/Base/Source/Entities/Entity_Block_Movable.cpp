#include "Entity_Block_Movable.h"


CEntity_Block_Movable::CEntity_Block_Movable()
{
}

CEntity_Block_Movable::CEntity_Block_Movable(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cSprite = cSprite;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	Animation* cAnim = new Animation(0, 0, 0, 1.f);
	cSprite->m_anim = cAnim;
}

CEntity_Block_Movable::~CEntity_Block_Movable()
{
}

bool CEntity_Block_Movable::DoColDir(MOVE_DIR m_MoveDir)
{
	int iIndexCheckX, iIndexCheckY;
	switch (m_MoveDir)
	{
	case DIR_UP:
		iIndexCheckX = this->m_iXIndex;
		iIndexCheckY = this->m_iYIndex - 1;
		break;
	case DIR_DOWN:
		iIndexCheckX = this->m_iXIndex;
		iIndexCheckY = this->m_iYIndex + 1;
		break;
	case DIR_RIGHT:
		iIndexCheckX = this->m_iXIndex + 1;
		iIndexCheckY = this->m_iYIndex;
		break;
	case DIR_LEFT:
		iIndexCheckX = this->m_iXIndex - 1;
		iIndexCheckY = this->m_iYIndex;
		break;
	default:
		std::cout << "NULL Collision Direction" << std::endl;
		break;
	}

	if (!this->m_cTilemap->AllowCollision(iIndexCheckX, iIndexCheckY))//->GetTile(iIndexCheckX, iIndexCheckY).GetCollisionType() == CTiledata::COL_BLOCK)
	{
		if (this->m_cTilemap->GetTile(iIndexCheckX, iIndexCheckY).GetCollisionType() != CTiledata::COL_HOLE)
			return true;
	}
	for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
	{
		if ((*entity)->GetXIndex() == iIndexCheckX && (*entity)->GetYIndex() == iIndexCheckY && (*entity)->IsAlive())
		{
			return true;
		}
	}
	//for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
	//	(*entity)->SetRecalculate(true);
	this->m_MoveDir = m_MoveDir;

	this->m_cTilemap->theScreenMap[static_cast<int>(GetNextDirectionPos().x)][static_cast<int>(GetNextDirectionPos().y)].SetTint(true);
	return false;
}

void CEntity_Block_Movable::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Block_Movable::UpdateMovement(const float dt)
{
}

bool CEntity_Block_Movable::DoCurrentTileCollision()
{
	if (CEntityIPos::DoCurrentTileCollision())
		return true;
	switch (this->m_cTilemap->GetTile(this->m_iXIndex, this->m_iYIndex).GetCollisionType())
	{
	case CTiledata::COL_RUNE:
		this->m_MoveDir = DIR_NONE;
		return false;
	case CTiledata::COL_HOLE:
		this->m_MoveDir = DIR_NONE;
		this->m_bAlive = false;
		this->m_cTilemap->theScreenMap[this->m_iXIndex][this->m_iYIndex].ChangeIdState();
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
			(*entity)->SetRecalculate(true);
		return false;
	case CTiledata::COL_WIND_UP:
		this->m_MoveDir = DIR_UP;
		if (static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().x) == static_cast<int>(this->GetNextDirectionPos().x)
			&& static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().y) == static_cast<int>(this->GetNextDirectionPos().y))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
			{
				this->m_MoveDir = DIR_NONE;
				return true;
			}
		}
		return false;
	case CTiledata::COL_WIND_DOWN:
		this->m_MoveDir = DIR_DOWN;
		if (static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().x) == static_cast<int>(this->GetNextDirectionPos().x)
			&& static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().y) == static_cast<int>(this->GetNextDirectionPos().y))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
			{
				this->m_MoveDir = DIR_NONE;
				return true;
			}
		}
		return false;
	case CTiledata::COL_WIND_LEFT:
		this->m_MoveDir = DIR_LEFT;
		if (static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().x) == static_cast<int>(this->GetNextDirectionPos().x)
			&& static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().y) == static_cast<int>(this->GetNextDirectionPos().y))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
			{
				this->m_MoveDir = DIR_NONE;
				return true;
			}
		}
		return false;
	case CTiledata::COL_WIND_RIGHT:
		this->m_MoveDir = DIR_RIGHT;
		if (static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().x) == static_cast<int>(this->GetNextDirectionPos().x)
			&& static_cast<int>(this->m_cPlayerPtr->GetNextDirectionPos().y) == static_cast<int>(this->GetNextDirectionPos().y))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		if (!m_cTilemap->AllowCollision(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)))
		{
			this->m_MoveDir = DIR_NONE;
			return true;
		}
		for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
		{
			if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
			{
				this->m_MoveDir = DIR_NONE;
				return true;
			}
		}
		return false;
	default:
		return false;
	}
}

bool CEntity_Block_Movable::AllowEnemyMovement(void)
{
	return false;
}