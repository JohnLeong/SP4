#include "Entity_Coin.h"
#include "../Application.h"

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

	cAnim = new Animation();
	cAnim->Set(0, 7, 0, 0.5f);
	this->m_cSprite->m_anim = cAnim;
}

bool CEntity_Coin::DoColDir(MOVE_DIR m_MoveDir)
{
	//Add coin here
	Application::Sound.playSound("media/collect_coin_sound.mp3");
	m_cPlayerPtr->AddCoin(1);
	this->SetAlive(false);
	for (unsigned i = 0; i < Application::m_cPropertyList.size(); i++)
	{
		if (Application::m_cPropertyList[i]->GetTitle() == "Coin")
		{
			Application::m_cPropertyList[i]->ChangeValue(1);
		}
	}
	return false;
}

void CEntity_Coin::Update(const float dt)
{
	CEntityIPos::Update(dt);

	this->m_cSprite->Update(static_cast<double>(dt));
}

void CEntity_Coin::UpdateMovement(const float dt)
{

}

bool CEntity_Coin::AllowEnemyMovement(void)
{
	return true;
}
