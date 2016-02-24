#ifndef ENTITY_ENEMY_H
#define ENTITY_ENEMY_H

#include "../Tilemap.h"
#include "EntityIPos.h"


class CEnemy : public CEntityIPos
{
public:
	enum HOLDING_OBJ_TYPE
	{
		HOLDING_NONE,
		HOLDING_KEY_RED,
		HOLDING_KEY_GREEN,
		HOLDING_KEY_BLUE,
		HOLDING_KEY_YELLOW,
		HOLDING_COIN,
	};
	CEnemy();
	~CEnemy(void);

	virtual void AddAnimation(Animation* cAnim, MOVE_DIR cMoveDir);
	virtual void Update(const float dt);		// Update

	virtual bool DoColDir(MOVE_DIR m_MoveDir);						//Do collision response in specified direction
	virtual	bool DoCurrentTileCollision();

	virtual bool DeathOnEntry(void);

protected:
	Animation* m_animationList[NUM_DIR];
	MOVE_DIR m_NextDir;

};

#endif