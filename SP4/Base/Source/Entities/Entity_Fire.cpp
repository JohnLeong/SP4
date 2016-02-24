#include "Entity_Fire.h"


CEntity_Fire::CEntity_Fire()
{
}

CEntity_Fire::CEntity_Fire(int iXIndex, int iYIndex, FIRE_STATE cFire_State, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
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

CEntity_Fire::~CEntity_Fire()
{
}


void CEntity_Fire::InitAnimation()
{
	Animation* cAnim;

	cAnim = new Animation();
	cAnim->Set(5, 5, 1, 1.f);
	AddAnimation(cAnim, STATE_01);

	cAnim = new Animation();
	cAnim->Set(6, 6, 1, 1.f);
	AddAnimation(cAnim, STATE_02);

	cAnim = new Animation();
	cAnim->Set(7, 7, 1, 1.f);
	AddAnimation(cAnim, STATE_03);

	cAnim = new Animation();
	cAnim->Set(8, 8, 1, 1.5f);
	AddAnimation(cAnim, STATE_04);

	cAnim = new Animation();
	cAnim->Set(0, 4, 0, 0.1f);
	AddAnimation(cAnim, STATE_05);

	this->m_cSprite->m_anim = m_animationList[m_cFire_State];
}

void CEntity_Fire::AddAnimation(Animation* cAnim, FIRE_STATE state)
{
	m_animationList[state] = cAnim;
}

bool CEntity_Fire::DoColDir(MOVE_DIR m_MoveDir)
{
	if (m_cFire_State == STATE_04)	//State will be 05 when player moves to this tile
		m_cPlayerPtr->SetAlive(false);
	return false;
}

void CEntity_Fire::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Fire::UpdateMovement(const float dt)
{
	//Change animation to play based on state
	switch (this->m_cFire_State)
	{
	case STATE_01:
		this->m_cFire_State = STATE_03;
		this->m_cSprite->m_anim = m_animationList[STATE_03];
		break;
	case STATE_02:
		this->m_cFire_State = STATE_03;
		this->m_cSprite->m_anim = m_animationList[STATE_03];
		break;
	case STATE_03:
		this->m_cFire_State = STATE_05;
		this->m_cSprite->m_anim = m_animationList[STATE_05];
		break;
	case STATE_04:
		this->m_cFire_State = STATE_05;
		this->m_cSprite->m_anim = m_animationList[STATE_05];
		break;
	case STATE_05:
		this->m_cFire_State = STATE_01;
		this->m_cSprite->m_anim = m_animationList[STATE_01];
		break;
	default:
		break;
	}
}

bool CEntity_Fire::AllowEnemyMovement(void)
{
	return true;
}