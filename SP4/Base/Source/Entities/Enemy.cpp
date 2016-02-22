#include "Enemy.h"

CEnemy::CEnemy()
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

	this->m_cSprite->m_anim = m_animationList[this->m_AnimDir];
	this->m_cSprite->Update(static_cast<double>(dt));
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
				if (static_cast<int>(GetNextDirectionPos().x) == (*entity)->GetXIndex() && static_cast<int>(GetNextDirectionPos().y) == (*entity)->GetYIndex())
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
	default:
		this->m_MoveDir = DIR_NONE;
		return false;
	}
}