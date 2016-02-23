#ifndef ENTITY_KEY_YELLOW_H
#define ENTITY_KEY_YELLOW_H

#include "EntityIPos.h"

class CEntity_Key_Yellow : public CEntityIPos
{
public:
	CEntity_Key_Yellow();
	CEntity_Key_Yellow(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_Key_Yellow();

	virtual bool DoColDir(MOVE_DIR m_MoveDir);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

};

#endif
