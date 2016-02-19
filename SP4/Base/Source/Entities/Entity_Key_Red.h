#ifndef ENTITY_KEY_RED_H
#define ENTITY_KEY_RED_H

#include "EntityIPos.h"

class CEntity_Key_Red : public CEntityIPos
{
public:
	CEntity_Key_Red();
	CEntity_Key_Red(int iXIndex, int iYIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, Animation* anim);
	~CEntity_Key_Red();

	virtual bool DoColDir(MOVE_DIR m_MoveDir, std::vector<CEntityIPos*>* entityList);

	virtual void Update(const float dt, CPlayer* cPlayer);			// Update
	virtual void UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList);
};

#endif
