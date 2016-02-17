#include "Entity.h"


CEntity::CEntity()
: m_bAlive(true)
, m_iCurrent_health(0)
, m_iMax_health(0)
{
}


CEntity::~CEntity()
{
}

void CEntity::SetHealth(int h)
{
	this->m_iCurrent_health = h;
}

void CEntity::SetMaxHealth(int h)
{
	this->m_iMax_health = h;
}

void CEntity::DeductHealth(int h)
{
	this->m_iCurrent_health -= h;
}

int CEntity::GetHealth(void)
{
	return m_iCurrent_health;
}

int CEntity::GetMaxHealth(void)
{
	return m_iMax_health;
}

void CEntity::SetSprite(SpriteAnimation* sa)
{
	this->m_cSprite = sa;
}

SpriteAnimation* CEntity::GetSprite(void)
{
	return m_cSprite;
}

void CEntity::Update(const float dt, CPlayer* cPlayer)
{
}