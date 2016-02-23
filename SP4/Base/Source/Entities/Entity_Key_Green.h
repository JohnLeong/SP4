#ifndef ENTITY_KEY_GREEN_H
#define ENTITY_KEY_GREEN_H

#include "EntityIPos.h"

class CEntity_Key_Green : public CEntityIPos
{
public:
	CEntity_Key_Green();
	CEntity_Key_Green(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_Key_Green();

	virtual bool DoColDir(MOVE_DIR m_MoveDir);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

};

#endif
