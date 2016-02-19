#include "Entity_Block_Movable.h"


CEntity_Block_Movable::CEntity_Block_Movable()
{
}

CEntity_Block_Movable::CEntity_Block_Movable(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cSprite = cSprite;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	Animation* cAnim = new Animation(0, 0, 0, 1.f);
	cSprite->m_anim = cAnim;
}

CEntity_Block_Movable::~CEntity_Block_Movable()
{
}

bool CEntity_Block_Movable::DoColDir(MOVE_DIR m_MoveDir)
{
	int iIndexCheckX, iIndexCheckY;
	switch (m_MoveDir)
	{
	case DIR_UP:
		iIndexCheckX = this->m_iXIndex;
		iIndexCheckY = this->m_iYIndex - 1;
		break;
	case DIR_DOWN:
		iIndexCheckX = this->m_iXIndex;
		iIndexCheckY = this->m_iYIndex + 1;
		break;
	case DIR_RIGHT:
		iIndexCheckX = this->m_iXIndex + 1;
		iIndexCheckY = this->m_iYIndex;
		break;
	case DIR_LEFT:
		iIndexCheckX = this->m_iXIndex - 1;
		iIndexCheckY = this->m_iYIndex;
		break;
	default:
		std::cout << "NULL Collision Direction" << std::endl;
		break;
	}
	if (this->m_cTilemap->GetTile(iIndexCheckX, iIndexCheckY).GetCollisionType() != CTiledata::COL_VOID &&
		this->m_cTilemap->GetTile(iIndexCheckX, iIndexCheckY).GetCollisionType() != CTiledata::COL_ICE)
		return true;
	for (std::vector<CEntityIPos*>::iterator entity = (*m_cEntityList).begin(); entity != (*m_cEntityList).end(); entity++)
	{
		if ((*entity)->GetXIndex() == iIndexCheckX && (*entity)->GetYIndex() == iIndexCheckY && (*entity)->IsAlive())
		{
			return true;
		}
	}
	this->m_MoveDir = m_MoveDir;
	return false;
}

void CEntity_Block_Movable::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Block_Movable::UpdateMovement(const float dt)
{
	//int iIndexCheckX, iIndexCheckY;
	////Collision check
	//switch (cPlayer->GetDirection())
	//{
	//case CPlayer::PD_UP:
	//	iIndexCheckX = cPlayer->GetPos_x();	iIndexCheckY = cPlayer->GetPos_y() - 1;
	//	break;
	//case CPlayer::PD_DOWN:
	//	iIndexCheckX = cPlayer->GetPos_x();	iIndexCheckY = cPlayer->GetPos_y() + 1;
	//	break;
	//case CPlayer::PD_LEFT:
	//	iIndexCheckX = cPlayer->GetPos_x() - 1;	iIndexCheckY = cPlayer->GetPos_y();
	//	break;
	//case CPlayer::PD_RIGHT:
	//	iIndexCheckX = cPlayer->GetPos_x() + 1;	iIndexCheckY = cPlayer->GetPos_y();
	//	break;
	//default:
	//	std::cout << "NO DIRECTION FOUND" << std::endl;
	//	break;
	//}
	////Set move direction based on player direction
	//if (iIndexCheckX == this->m_iXIndex && iIndexCheckY == this->m_iYIndex)
	//{
	//	switch (cPlayer->GetDirection())
	//	{
	//	case CPlayer::PD_UP:
	//		this->m_MoveDir = DIR_UP;
	//		break;
	//	case CPlayer::PD_DOWN:
	//		this->m_MoveDir = DIR_DOWN;
	//		break;
	//	case CPlayer::PD_LEFT:
	//		this->m_MoveDir = DIR_LEFT;
	//		break;
	//	case CPlayer::PD_RIGHT:
	//		this->m_MoveDir = DIR_RIGHT;
	//		break;
	//	default:
	//		std::cout << "NO DIRECTION FOUND" << std::endl;
	//		break;
	//	}
	//}
}