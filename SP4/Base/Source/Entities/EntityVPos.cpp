#include "EntityVPos.h"


CEntityVPos::CEntityVPos()
: pos(0.f, 0.f, 0.f)
{
}


CEntityVPos::~CEntityVPos()
{
}

float CEntityVPos::GetXPos(void)
{
	return pos.x;
}

float CEntityVPos::GetYPos(void)
{
	return pos.y;
}

Vector3 CEntityVPos::GetPos(void)
{
	return pos;
}

void CEntityVPos::SetXPos(float x)
{
	this->pos.x = x;
}

void CEntityVPos::SetYPos(float y)
{
	this->pos.y = y;
}

void CEntityVPos::SetPos(Vector3 pos)
{
	this->pos = pos;
}

void CEntityVPos::Update(const float dt)
{
}