#include "EnemyZombie.h"

CEnemyZombie::CEnemyZombie()
{
	m_cAStar = new AStar();
}


CEnemyZombie::~CEnemyZombie(void)
{
}

/********************************************************************************
Update
********************************************************************************/
void CEnemyZombie::Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer)
{
	m_cAStar->Init(this->m_iXIndex, this->m_iYIndex, cPlayer->GetPos_x(), cPlayer->GetPos_y(), cTilemap);
	m_cAStar->Search();
	m_cAStar->Reset();
}