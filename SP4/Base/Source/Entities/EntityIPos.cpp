#include "EntityIPos.h"


CEntityIPos::CEntityIPos()
{
}


CEntityIPos::~CEntityIPos()
{
}

void CEntityIPos::SetXIndex(float iXIndex)
{
	this->m_iXIndex = iXIndex;
}

void CEntityIPos::SetYIndex(float iYIndex)
{
	this->m_iYIndex = iYIndex;
}

void CEntityIPos::SetPos(int iXIndex, int iYIndex)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
}

int CEntityIPos::GetXIndex(void)
{
	return m_iXIndex;
}

int CEntityIPos::GetYIndex(void)
{
	return m_iYIndex;
}

/********************************************************************************
Update
********************************************************************************/
void CEntityIPos::Update(const float dt, CPlayer* cPlayer)
{

}

void CEntityIPos::UpdateMovement(const float dt, CPlayer* cPlayer)
{

}