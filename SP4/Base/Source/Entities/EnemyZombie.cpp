#include "EnemyZombie.h"

CEnemyZombie::CEnemyZombie()
{
	//m_cAStar = new AStar();
	std::cout << "NULLASTAR" << std::endl;
}

CEnemyZombie::CEnemyZombie(int iXIndex, int YIndex, CTilemap* cTilemap, SpriteAnimation* cSprite)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = YIndex;
	this->m_bAlive = true;
	this->m_cTilemap = cTilemap;
	m_cAStar = new AStar(cTilemap);
	this->m_cSprite = cSprite;
	InitAnimation();
}

CEnemyZombie::~CEnemyZombie(void)
{
	delete m_cAStar;
}

void CEnemyZombie::InitAnimation()
{
	Animation* cAnim;

	cAnim = new Animation();
	cAnim->Set(1, 1, 0, 0.f);
	AddAnimation(cAnim, DIR_IDLE_DOWN);

	//Idle East
	cAnim = new Animation();
	cAnim->Set(4, 4, 0, 0.f);
	AddAnimation(cAnim, DIR_IDLE_UP);

	//Idle East
	cAnim = new Animation();
	cAnim->Set(7, 7, 0, 0.f);
	AddAnimation(cAnim, DIR_IDLE_RIGHT);

	//Idle North
	cAnim = new Animation();
	cAnim->Set(10, 10, 0, 0.f);
	AddAnimation(cAnim, DIR_IDLE_LEFT);

	//Walk South
	cAnim = new Animation();
	cAnim->Set(0, 2, 0, 0.8f);
	AddAnimation(cAnim, DIR_DOWN);

	//Walk East
	cAnim = new Animation();
	cAnim->Set(3, 5, 0, 0.4f);
	AddAnimation(cAnim, DIR_UP);

	//Walk East
	cAnim = new Animation();
	cAnim->Set(6, 8, 0, 0.4f);
	AddAnimation(cAnim, DIR_RIGHT);

	//Walk North
	cAnim = new Animation();
	cAnim->Set(9, 11, 0, 0.4f);
	AddAnimation(cAnim, DIR_LEFT);
}

/********************************************************************************
Update
********************************************************************************/
void CEnemyZombie::Update(const float dt, CPlayer* cPlayer)
{
	CEnemy::Update(dt, cPlayer);
}

void CEnemyZombie::UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList)
{
	if (this->m_iXIndex == cPlayer->GetPos_x() && this->m_iYIndex == cPlayer->GetPos_y())
		return;
	m_cAStar->Init(this->m_iXIndex, this->m_iYIndex, cPlayer->GetPos_x(), cPlayer->GetPos_y(), entityList);

	switch (m_cAStar->Search())
	{
	case AStar::DIR_UP:
		this->m_MoveDir = CEntityIPos::DIR_UP;
		this->m_AnimDir = CEntityIPos::DIR_UP;
		break;
	case AStar::DIR_DOWN:
		this->m_MoveDir = CEntityIPos::DIR_DOWN;
		this->m_AnimDir = CEntityIPos::DIR_DOWN;
		break;
	case AStar::DIR_LEFT:
		this->m_MoveDir = CEntityIPos::DIR_LEFT;
		this->m_AnimDir = CEntityIPos::DIR_LEFT;
		break;
	case AStar::DIR_RIGHT:
		this->m_MoveDir = CEntityIPos::DIR_RIGHT;
		this->m_AnimDir = CEntityIPos::DIR_RIGHT;
		break;
	case AStar::DIR_NONE:
		break;
	default:
		break;
	}
	
	m_cAStar->Reset();
}