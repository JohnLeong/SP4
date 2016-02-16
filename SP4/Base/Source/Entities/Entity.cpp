#include "Entity.h"


CGameEntity::CGameEntity()
: pos(0.f, 0.f, 0.f)
{
}


CGameEntity::~CGameEntity()
{
}

float CGameEntity::GetXPos(void)
{
	return pos.x;
}

float CGameEntity::GetYPos(void)
{
	return pos.y;
}

void CGameEntity::SetXPos(float x)
{
	this->pos.x = x;
}

void CGameEntity::SetYPos(float y)
{
	this->pos.y = y;
}

void CGameEntity::SetHealth(int h)
{
	this->current_health = h;
}

void CGameEntity::SetMaxHealth(int h)
{
	this->max_health = h;
}

void CGameEntity::DeductHealth(int h)
{
	this->current_health -= h;
}

int CGameEntity::GetHealth(void)
{
	return current_health;
}

int CGameEntity::GetMaxHealth(void)
{
	return max_health;
}

void CGameEntity::Update(const float dt)
{
}