#include "Entity_Hazard_Moving.h"


CEntity_Hazard_Moving::CEntity_Hazard_Moving()
: m_fMoveDist(10.f)
{
	this->m_Origin = this->pos;
}


CEntity_Hazard_Moving::~CEntity_Hazard_Moving()
{
}

void CEntity_Hazard_Moving::Init(Vector3 pos, bool MoveDir, float m_fMoveDist)
{
	this->pos = pos;
	if (MoveDir)
		this->m_MoveDir = DIR_UP_DOWN;
	else
		this->m_MoveDir = DIR_LEFT_RIGHT;
	this->m_fMoveDist = m_fMoveDist;
}

void CEntity_Hazard_Moving::Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer)
{
	if (m_MoveDir == CEntity_Hazard_Moving::DIR_LEFT_RIGHT)
	{
		if ((this->pos - this->m_Origin).LengthSquared() > m_fMoveDist * m_fMoveDist)
		{
			m_bDir = !m_bDir;
		}
		if (m_bDir)//right
		{
			this->pos.x += dt * Entity_Hazard_Moving_Speed;
		}
		else//left
		{
			this->pos.x -= dt * Entity_Hazard_Moving_Speed;
		}
	}
	else
	{
		if ((this->pos - this->m_Origin).LengthSquared() > m_fMoveDist * m_fMoveDist)
		{
			m_bDir = !m_bDir;
		}
		if (m_bDir)//up
		{
			this->pos.y += dt * Entity_Hazard_Moving_Speed;
		}
		else//down
		{
			this->pos.y -= dt * Entity_Hazard_Moving_Speed;
		}
	}
}