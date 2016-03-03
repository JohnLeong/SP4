#ifndef ENTITY_ENEMY_ZOMBIE_H
#define ENTITY_ENEMY_ZOMBIE_H

#include "Enemy.h"
#include "../AStar.h"

/*
\brief
Normal zombie - moves whenever player moves
*/

class CEnemyZombie : public CEnemy
{
public:
	CEnemyZombie();
	CEnemyZombie(int iXIndex, int YIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList, CEntityIPos* cKeyPtr = NULL);
	~CEnemyZombie(void);

	void InitAnimation();
	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

	virtual bool DeathOnEntry(void);

private:
	AStar* m_cAStar;	//Astar for pathfinding to player
};

#endif