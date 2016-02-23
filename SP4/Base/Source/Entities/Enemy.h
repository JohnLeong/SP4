#ifndef ENTITY_ENEMY_H
#define ENTITY_ENEMY_H

#include "../Tilemap.h"
#include "EntityIPos.h"

class CEnemy : public CEntityIPos
{
public:
	enum HOLDINGKEY_TYPE
	{
		HOLDING_KEY_NONE,
		HOLDING_KEY_RED,
		HOLDING_KEY_GREEN,
		HOLDING_KEY_BLUE,
	};
	CEnemy();
	~CEnemy(void);

	virtual void AddAnimation(Animation* cAnim, MOVE_DIR cMoveDir);
	virtual void Update(const float dt);		// Update

	virtual bool DoColDir(MOVE_DIR m_MoveDir);						//Do collision response in specified direction
	virtual	bool DoCurrentTileCollision();

protected:
	Animation* m_animationList[NUM_DIR];
	MOVE_DIR m_NextDir;

};

#endif