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
void CEnemy::Update(const float dt, CPlayer* cPlayer)
{
	CEntityIPos::Update(dt, cPlayer);

	this->m_cSprite->m_anim = m_animationList[this->m_AnimDir];
	this->m_cSprite->Update(static_cast<double>(dt));
}