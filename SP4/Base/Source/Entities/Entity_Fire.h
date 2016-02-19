#ifndef ENTITY_FIRE_H
#define ENTITY_FIRE_H

#include "EntityIPos.h"

class CEntity_Fire : public CEntityIPos
{
public:
	CEntity_Fire();
	CEntity_Fire(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim);
	~CEntity_Fire();

	virtual bool DoColDir(MOVE_DIR m_MoveDir, std::vector<CEntityIPos*>* entityList);

	virtual void Update(const float dt, CPlayer* cPlayer);			// Update
	virtual void UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList);
};

#endif
