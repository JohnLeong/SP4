#include "Entity_Key_Green.h"


CEntity_Key_Green::CEntity_Key_Green()
{
}

CEntity_Key_Green::CEntity_Key_Green(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	this->m_cSprite = cSprite;
	this->m_cSprite->m_anim = anim;
}

CEntity_Key_Green::~CEntity_Key_Green()
{
}

bool CEntity_Key_Green::DoColDir(MOVE_DIR m_MoveDir)
{
	this->m_bAlive = false;
	return false;
}

void CEntity_Key_Green::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Key_Green::UpdateMovement(const float dt)
{
}

bool CEntity_Key_Green::AllowEnemyMovement(void)
{
	return true;
}