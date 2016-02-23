#include "Enemy.h"

CEnemy::CEnemy()
: m_NextDir(DIR_NONE)
{
}

CEnemy::~CEnemy(void)
{
}

void CEnemy::AddAnimation(Animation* cAnim, MOVE_DIR cMoveDir)
{
	m_animationList[cMoveDir] = cAnim;
}

/********************************************************************************
Update
********************************************************************************/
void CEnemy::Update(const float dt)
{
	CEntityIPos::Update(dt);

	if (this->m_iXIndex == this->m_cPlayerPtr->GetXIndex() && this->m_iYIndex == this->m_cPlayerPtr->GetYIndex())
		m_cPlayerPtr->SetAlive(false);

	this->m_cSprite->m_anim = m_animationList[this->m_AnimDir];
	this->m_cSprite->Update(static_cast<double>(dt));
}

bool CEnemy::DoColDir(MOVE_DIR m_MoveDir)
{
	m_cPlayerPtr->SetAlive(false);
	return false;
}

bool CEnemy::DoCurrentTileCollision()
{
	switch (this->m_cTilemap->GetTile(this->m_iXIndex, this->m_iYIndex).GetCollisionType())
	{
	case CTiledata::COL_VOID:
		this->m_MoveDir = DIR_NONE;
		return false;
	case CTiledata::COL_ICE:
		if (this->m_cTilemap->GetTile(static_cast<int>(GetNextDirectionPos().x), static_cast<int>(GetNextDirectionPos().y)).GetCollisionType() != CTiledata::COL_BLOCK)
		{
			for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
			{
				if ((*entity) == this)
					continue;
				if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex() && !(*entity)->AllowEnemyMovement())
				{
					this->m_MoveDir = DIR_NONE;
					return false;
				}
			}
			return true;
		}
		this->m_MoveDir = DIR_NONE;
		return false;
	case CTiledata::COL_HOLE:
		this->m_MoveDir = DIR_NONE;
		return false;
	case CTiledata::COL_WIND_UP:
		this->m_MoveDir = DIR_UP;
		return false;
	case CTiledata::COL_WIND_DOWN:
		this->m_MoveDir = DIR_DOWN;
		return false;
	case CTiledata::COL_WIND_LEFT:
		this->m_MoveDir = DIR_LEFT;
		return false;
	case CTiledata::COL_WIND_RIGHT:
		this->m_MoveDir = DIR_RIGHT;
		return false;
	case CTiledata::COL_RUNE:
		this->m_MoveDir = DIR_NONE;
		this->SetAlive(false);
		this->m_cTilemap->theScreenMap[this->m_iXIndex][this->m_iYIndex].ChangeIdState();	//Change tile to normal tile
		if (this->m_cObjPtr != NULL)
		{
			this->m_cObjPtr->SetAlive(true);
			this->m_cObjPtr->SetPos(this->m_iXIndex, this->m_iYIndex);
		}
		return false;
	default:
		this->m_MoveDir = DIR_NONE;
		return false;
	}
}

bool CEnemy::DeathOnEntry(void)
{
	return true;
}