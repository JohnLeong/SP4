#ifndef ENTITY_ENEMY_SUPER_ZOMBIE_H
#define ENTITY_ENEMY_SUPER_ZOMBIE_H

#include "Enemy.h"
#include "../AStar.h"

//Zombie enemy which always tracks the player

class CEnemySuperRetardZombie : public CEnemy
{
public:
	CEnemySuperRetardZombie();
	CEnemySuperRetardZombie(int iXIndex, int YIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList, CEntityIPos* cKeyPtr = NULL);
	~CEnemySuperRetardZombie(void);

	void InitAnimation();
	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

	virtual bool DeathOnEntry(void);

private:
	AStar* m_cAStar;	//Astar for pathfinding to player

	bool m_bMovementToggle;
};

#endif