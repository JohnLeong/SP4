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
	CEntityIPos::Update(dt, cPlayer);
}

void CEnemyZombie::UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*> entityList)
{
	if (this->m_iXIndex == cPlayer->GetPos_x() && this->m_iYIndex == cPlayer->GetPos_y())
		return;
	m_cAStar->Init(this->m_iXIndex, this->m_iYIndex, cPlayer->GetPos_x(), cPlayer->GetPos_y(), &entityList);

	switch (m_cAStar->Search())
	{
	case AStar::DIR_UP:
		this->m_MoveDir = CEntityIPos::DIR_UP;
		break;
	case AStar::DIR_DOWN:
		this->m_MoveDir = CEntityIPos::DIR_DOWN;
		break;
	case AStar::DIR_LEFT:
		this->m_MoveDir = CEntityIPos::DIR_LEFT;
		break;
	case AStar::DIR_RIGHT:
		this->m_MoveDir = CEntityIPos::DIR_RIGHT;
		break;
	case AStar::DIR_NONE:
		break;
	default:
		break;
	}
	
	m_cAStar->Reset();
}