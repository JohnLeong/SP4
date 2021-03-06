#ifndef ENTITY_BLOCK_MOVABLE_H
#define ENTITY_BLOCK_MOVABLE_H

#include "Vector3.h"
#include "EntityIPos.h"

class CEntity_Block_Movable : public CEntityIPos
{
public:
	CEntity_Block_Movable();
	CEntity_Block_Movable(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_Block_Movable();

	virtual bool DoColDir(MOVE_DIR m_MoveDir);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

	virtual	bool DoCurrentTileCollision();
	virtual bool AllowEnemyMovement(void);
};

#endif
