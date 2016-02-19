#ifndef ENTITY_ENEMY_H
#define ENTITY_ENEMY_H

#include "../Tilemap.h"
#include "EntityIPos.h"

class CEnemy : public CEntityIPos
{
public:
	CEnemy();
	~CEnemy(void);

	virtual void AddAnimation(Animation* cAnim, MOVE_DIR cMoveDir);
	virtual void Update(const float dt, CPlayer* cPlayer);		// Update

	Animation* m_animationList[NUM_DIR];
};

#endif