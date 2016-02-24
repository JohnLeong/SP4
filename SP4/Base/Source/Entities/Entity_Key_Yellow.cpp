#include "Entity_Key_Yellow.h"


CEntity_Key_Yellow::CEntity_Key_Yellow()
{
}

CEntity_Key_Yellow::CEntity_Key_Yellow(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	this->m_cSprite = cSprite;
	this->m_cSprite->m_anim = anim;
}

CEntity_Key_Yellow::~CEntity_Key_Yellow()
{
}

bool CEntity_Key_Yellow::DoColDir(MOVE_DIR m_MoveDir)
{
	this->m_bAlive = false;
	m_cPlayerPtr->AddKeys(1, 3);
	return false;
}

void CEntity_Key_Yellow::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Key_Yellow::UpdateMovement(const float dt)
{
}

bool CEntity_Key_Yellow::AllowEnemyMovement(void)
{
	return true;
}