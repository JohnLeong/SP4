#include "Entity_Key_Red.h"


CEntity_Key_Red::CEntity_Key_Red()
{
}

CEntity_Key_Red::CEntity_Key_Red(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cSprite = cSprite;
	this->m_cSprite->m_anim = anim;
}

CEntity_Key_Red::~CEntity_Key_Red()
{
}

bool CEntity_Key_Red::DoColDir(MOVE_DIR m_MoveDir, std::vector<CEntityIPos*>* entityList)
{
	this->m_bAlive = false;
	return false;
}

void CEntity_Key_Red::Update(const float dt, CPlayer* cPlayer)
{
	CEntityIPos::Update(dt, cPlayer);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Key_Red::UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList)
{
}