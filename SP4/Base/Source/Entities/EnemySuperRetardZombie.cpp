#include "EnemySuperRetardZombie.h"
#include "../Application.h"

CEnemySuperRetardZombie::CEnemySuperRetardZombie()
: m_bMovementToggle(false)
{
	//m_cAStar = new AStar();
	std::cout << "NULLASTAR" << std::endl;
}

CEnemySuperRetardZombie::CEnemySuperRetardZombie(int iXIndex, int YIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList, CEntityIPos* cKeyPtr)
: m_bMovementToggle(false)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = YIndex;
	this->m_bAlive = true;
	this->m_cTilemap = cTilemap;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	m_cAStar = new AStar(cTilemap);
	this->m_cSprite = cSprite;
	this->m_cObjPtr = cKeyPtr;
	if (cKeyPtr != NULL)
		this->m_cObjPtr->SetAlive(false);
	this->m_bHoldingObj = true;
	InitAnimation();
}

CEnemySuperRetardZombie::~CEnemySuperRetardZombie(void)
{
	delete m_cAStar;
}

void CEnemySuperRetardZombie::InitAnimation()
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
void CEnemySuperRetardZombie::Update(const float dt)
{
	CEnemy::Update(dt);
}

void CEnemySuperRetardZombie::UpdateMovement(const float dt)
{
	m_bMovementToggle = !m_bMovementToggle;
	if (!m_bMovementToggle)
		return;

	if (this->m_iXIndex == m_cPlayerPtr->GetXIndex() && this->m_iYIndex == m_cPlayerPtr->GetYIndex())
		return;

	if (this->m_iXIndex == static_cast<int>(m_cPlayerPtr->GetNextDirectionPos().x) && this->m_iYIndex == static_cast<int>(m_cPlayerPtr->GetNextDirectionPos().y))
		return;

	m_cAStar->Init(static_cast<int>(this->GetNextDirectionPos().x), static_cast<int>(this->GetNextDirectionPos().y), m_cPlayerPtr->GetXIndex(), m_cPlayerPtr->GetYIndex(), this->m_cEntityList);

	switch (m_cAStar->Search())
	{
	case AStar::DIR_UP:
		this->m_NextDir = CEntityIPos::DIR_UP;
		this->m_MoveDir = this->m_NextDir;
		this->m_AnimDir = this->m_NextDir;
		break;
	case AStar::DIR_DOWN:
		this->m_NextDir = CEntityIPos::DIR_DOWN;
		this->m_MoveDir = this->m_NextDir;
		this->m_AnimDir = this->m_NextDir;
		break;
	case AStar::DIR_LEFT:
		this->m_NextDir = CEntityIPos::DIR_LEFT;
		this->m_MoveDir = this->m_NextDir;
		this->m_AnimDir = this->m_NextDir;
		break;
	case AStar::DIR_RIGHT:
		this->m_NextDir = CEntityIPos::DIR_RIGHT;
		this->m_MoveDir = this->m_NextDir;
		this->m_AnimDir = this->m_NextDir;
		break;
	case AStar::DIR_NONE:
		this->m_NextDir = CEntityIPos::DIR_NONE;
		break;
	default:
		break;
	}

	m_cAStar->Reset();
	Application::m_bPauseDT = true;
}

bool CEnemySuperRetardZombie::DeathOnEntry(void)
{
	return CEnemy::DeathOnEntry();
}