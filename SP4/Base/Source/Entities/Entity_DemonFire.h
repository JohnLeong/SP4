#ifndef ENTITY_DEMONFIRE_H
#define ENTITY_DEMONFIRE_H

#include "EntityIPos.h"

class CEntity_DemonFire : public CEntityIPos
{
public:
	enum FIRE_STATE
	{
		STATE_01,
		STATE_02,		//Fire is active
		NUM_FIRE_STATE,
	};
public:
	CEntity_DemonFire();
	CEntity_DemonFire(int iXIndex, int iYIndex, FIRE_STATE cFire_State, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList);
	~CEntity_DemonFire();

	void InitAnimation();
	void AddAnimation(Animation* cAnim, FIRE_STATE state);

	virtual bool DoColDir(MOVE_DIR m_MoveDir);

	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

	virtual bool AllowEnemyMovement(void);

private:
	Animation* m_animationList[NUM_FIRE_STATE];

	FIRE_STATE m_cFire_State;
};

#endif
