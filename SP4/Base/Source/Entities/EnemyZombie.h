#include "Enemy.h"
#include "../AStar.h"

//Zombie enemy which always tracks the player

class CEnemyZombie : public CEnemy
{
public:
	CEnemyZombie();
	CEnemyZombie(int iXIndex, int YIndex, CTilemap* cTilemap);	
	~CEnemyZombie(void);

	virtual void Update(const float dt, CPlayer* cPlayer);			// Update
	virtual void UpdateMovement(const float dt, CPlayer* cPlayer);

private:
	AStar* m_cAStar;	//Astar for pathfinding to player
};