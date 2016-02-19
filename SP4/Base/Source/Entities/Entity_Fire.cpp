#include "Entity_Fire.h"


CEntity_Fire::CEntity_Fire()
{
}

CEntity_Fire::CEntity_Fire(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cSprite = cSprite;
	this->m_cSprite->m_anim = anim;
}

CEntity_Fire::~CEntity_Fire()
{
}

bool CEntity_Fire::DoColDir(MOVE_DIR m_MoveDir, std::vector<CEntityIPos*>* entityList)
{
	return false;
}

void CEntity_Fire::Update(const float dt, CPlayer* cPlayer)
{
	CEntityIPos::Update(dt, cPlayer);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Fire::UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList)
{
}