#include "EnemyZombie.h"

CEnemyZombie::CEnemyZombie()
{
	//m_cAStar = new AStar();
	std::cout << "NULLASTAR" << std::endl;
}

CEnemyZombie::CEnemyZombie(int iXIndex, int YIndex, CTilemap* cTilemap)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = YIndex;
	this->m_bAlive = true;
	this->m_cTilemap = cTilemap;
	m_cAStar = new AStar(cTilemap);
}

CEnemyZombie::~CEnemyZombie(void)
{
	delete m_cAStar;
}

/********************************************************************************
Update
********************************************************************************/
void CEnemyZombie::Update(const float dt, CPlayer* cPlayer)
{
	m_cAStar->Init(this->m_iXIndex, this->m_iYIndex, cPlayer->GetPos_x(), cPlayer->GetPos_y());
#if _DEBUG
	if (!m_cAStar->Search())
		std::cout<<"No Path found"<<std::endl;
#else
	m_cAStar->Search();
#endif
	m_cAStar->Reset();
}