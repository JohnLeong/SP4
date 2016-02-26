#ifndef ENTITY_KEY_BLUE_H
#define ENTITY_KEY_BLUE_H

#include "EntityIPos.h"

class CEntity_Key_Blue : public CEntityIPos
{
public:
	CEntity_Key_Blue();
	CEntity_Key_Blue(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_Key_Blue();

	virtual bool DoColDir(MOVE_DIR m_MoveDir);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);


	virtual bool AllowEnemyMovement(void);
};

#endif
