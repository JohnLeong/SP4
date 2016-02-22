#ifndef ENTITY_ENEMY_ZOMBIE_H
#define ENTITY_ENEMY_ZOMBIE_H

#include "Enemy.h"
#include "../AStar.h"

//Zombie enemy which always tracks the player

class CEnemyZombie : public CEnemy
{
public:
	CEnemyZombie();
	CEnemyZombie(int iXIndex, int YIndex, CTilemap* cTilemap, SpriteAnimation* cSprite, CEntityIPos* cPlayerPtr, std::vector<CEntityIPos*>* cEntityList, CEntityIPos* cKeyPtr = NULL);
	~CEnemyZombie(void);

	void InitAnimation();
	virtual void Update(const float dt);			// Update
	virtual void UpdateMovement(const float dt);

private:
	AStar* m_cAStar;	//Astar for pathfinding to player
};

#endif