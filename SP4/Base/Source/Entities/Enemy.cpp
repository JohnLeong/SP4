#include "Enemy.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy(void)
{
}

void CEnemy::SetXIndex(float iXIndex)
{
	this->m_iXIndex = iXIndex;
}

void CEnemy::SetYIndex(float iYIndex)
{
	this->m_iYIndex = iYIndex;
}

void CEnemy::SetPos(int iXIndex, int iYIndex)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
}

int CEnemy::GetXIndex(void)
{
	return m_iXIndex;
}

int CEnemy::GetYIndex(void)
{
	return m_iYIndex;
}

/********************************************************************************
Update
********************************************************************************/
void CEnemy::Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer)
{

}