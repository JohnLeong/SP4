#ifndef ENTITY_FIRE_H
#define ENTITY_FIRE_H

#include "EntityIPos.h"

class CEntity_Fire : public CEntityIPos
{
public:
	enum FIRE_STATE
	{
		STATE_01,
		STATE_02,
		STATE_03,
		STATE_04,
		STATE_05,		//Fire is active
		NUM_FIRE_STATE,
	};
public:
	CEntity_Fire();
	CEntity_Fire(int iXIndex, int iYIndex, FIRE_STATE cFire_State, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_Fire();

	void InitAnimation();
	void AddAnimation(Animation* cAnim, FIRE_STATE state);

	virtual bool DoColDir(MOVE_DIR m_MoveDir);
	virtual bool DeathOnEntry(void);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

	virtual bool AllowEnemyMovement(void);

private:
	Animation* m_animationList[NUM_FIRE_STATE];

	FIRE_STATE m_cFire_State;
};

#endif
