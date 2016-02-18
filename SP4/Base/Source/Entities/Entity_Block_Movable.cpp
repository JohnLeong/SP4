#include "Entity_Block_Movable.h"


CEntity_Block_Movable::CEntity_Block_Movable()
{
}

CEntity_Block_Movable::CEntity_Block_Movable(int iXIndex, int iYIndex)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
}

CEntity_Block_Movable::~CEntity_Block_Movable()
{
}

void CEntity_Block_Movable::Update(const float dt, CPlayer* cPlayer)
{
	switch (this->m_MoveDir)
	{
	case DIR_UP:
		--this->m_iYIndex;
		this->m_MoveDir = DIR_NONE;
		break;
	case DIR_DOWN:
		++this->m_iYIndex;
		this->m_MoveDir = DIR_NONE;
		break;
	case DIR_LEFT:
		--this->m_iXIndex;
		this->m_MoveDir = DIR_NONE;
		break;
	case DIR_RIGHT:
		++this->m_iXIndex;
		this->m_MoveDir = DIR_NONE;
		break;
	default:
		break;
	}
}

void CEntity_Block_Movable::UpdateMovement(const float dt, CPlayer* cPlayer)
{
	int iIndexCheckX, iIndexCheckY;
	switch (cPlayer->GetDirection())
	{
	case CPlayer::PD_UP:
		iIndexCheckX = cPlayer->GetPos_x();	iIndexCheckY = cPlayer->GetPos_y() - 1;
		break;
	case CPlayer::PD_DOWN:
		iIndexCheckX = cPlayer->GetPos_x();	iIndexCheckY = cPlayer->GetPos_y() + 1;
		break;
	case CPlayer::PD_LEFT:
		iIndexCheckX = cPlayer->GetPos_x() - 1;	iIndexCheckY = cPlayer->GetPos_y();
		break;
	case CPlayer::PD_RIGHT:
		iIndexCheckX = cPlayer->GetPos_x() + 1;	iIndexCheckY = cPlayer->GetPos_y();
		break;
	default:
		std::cout << "NO DIRECTION FOUND" << std::endl;
		break;
	}
	if (iIndexCheckX == this->m_iXIndex && iIndexCheckY == this->m_iYIndex)
	{
		switch (cPlayer->GetDirection())
		{
		case CPlayer::PD_UP:
			this->m_MoveDir = DIR_UP;
			break;
		case CPlayer::PD_DOWN:
			this->m_MoveDir = DIR_DOWN;
			break;
		case CPlayer::PD_LEFT:
			this->m_MoveDir = DIR_LEFT;
			break;
		case CPlayer::PD_RIGHT:
			this->m_MoveDir = DIR_RIGHT;
			break;
		default:
			std::cout << "NO DIRECTION FOUND" << std::endl;
			break;
		}
	}
}