#include "Entity_Key_Red.h"
#include "../Application.h"

bool add_key_Red = false;

CEntity_Key_Red::CEntity_Key_Red()
{
}

CEntity_Key_Red::CEntity_Key_Red(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	this->m_cSprite = cSprite;
	this->m_cSprite->m_anim = anim;
}

CEntity_Key_Red::~CEntity_Key_Red()
{
}

bool CEntity_Key_Red::DoColDir(MOVE_DIR m_MoveDir)
{
	Application::Sound.playSound("../irrKlang/media/key_sound.mp3");
	this->m_bAlive = false;
	m_cPlayerPtr->AddKeys(1, 0);
	return false;
}

void CEntity_Key_Red::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Key_Red::UpdateMovement(const float dt)
{
}

bool CEntity_Key_Red::AllowEnemyMovement(void)
{
	return true;
}