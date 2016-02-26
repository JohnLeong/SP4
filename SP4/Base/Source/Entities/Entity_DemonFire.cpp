#include "Entity_DemonFire.h"


CEntity_DemonFire::CEntity_DemonFire()
{
}

CEntity_DemonFire::CEntity_DemonFire(int iXIndex, int iYIndex, FIRE_STATE cFire_State, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	this->m_cSprite = cSprite;
	this->m_cFire_State = cFire_State;
	InitAnimation();
}

CEntity_DemonFire::~CEntity_DemonFire()
{
}


void CEntity_DemonFire::InitAnimation()
{
	Animation* cAnim;

	cAnim = new Animation();
	cAnim->Set(5, 5, 1, 1.f);
	AddAnimation(cAnim, STATE_01);

	cAnim = new Animation();
	cAnim->Set(0, 4, 0, 0.1f);
	AddAnimation(cAnim, STATE_02);

	this->m_cSprite->m_anim = m_animationList[m_cFire_State];
}

void CEntity_DemonFire::AddAnimation(Animation* cAnim, FIRE_STATE state)
{
	m_animationList[state] = cAnim;
}

bool CEntity_DemonFire::DoColDir(MOVE_DIR m_MoveDir)
{

	return false;
}

bool CEntity_DemonFire::DeathOnEntry(void)
{
	if (m_cFire_State == STATE_02)	//State will be 05 when player moves to this tile
		return true;
	else return false;
}

void CEntity_DemonFire::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_DemonFire::UpdateMovement(const float dt)
{
	//Change animation to play based on state
	switch (this->m_cFire_State)
	{
	case STATE_01:
		this->m_cFire_State = STATE_02;
		this->m_cSprite->m_anim = m_animationList[STATE_02];
		break;
	case STATE_02:
		this->m_cFire_State = STATE_01;
		this->m_cSprite->m_anim = m_animationList[STATE_01];
		break;
	default:
		break;
	}
}

bool CEntity_DemonFire::AllowEnemyMovement(void)
{
	return true;
}