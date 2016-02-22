#include "Entity_Coin.h"


CEntity_Coin::CEntity_Coin()
{
}

CEntity_Coin::CEntity_Coin(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList)
{
	this->m_iXIndex = iXIndex;
	this->m_iYIndex = iYIndex;
	this->m_cTilemap = cTilemap;
	this->m_cPlayerPtr = cPlayerPtr;
	this->m_cEntityList = cEntityList;
	this->m_cSprite = cSprite;
	InitAnimation();
}

CEntity_Coin::~CEntity_Coin()
{
}


void CEntity_Coin::InitAnimation()
{
	Animation* cAnim;
}

bool CEntity_Coin::DoColDir(MOVE_DIR m_MoveDir)
{
	//Add coin here
	m_cPlayerPtr->AddCoin(1);
	return false;
}

void CEntity_Coin::Update(const float dt)
{
	//CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Coin::UpdateMovement(const float dt)
{

}