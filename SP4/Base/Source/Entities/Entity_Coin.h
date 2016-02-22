#ifndef ENTITY_COIN_H
#define ENTITY_COIN_H

#include "EntityIPos.h"

class CEntity_Coin : public CEntityIPos
{
public:
	CEntity_Coin();
	CEntity_Coin(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_Coin();

	void InitAnimation();

	virtual bool DoColDir(MOVE_DIR m_MoveDir);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);
};

#endif
