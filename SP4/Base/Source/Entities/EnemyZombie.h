#include "Enemy.h"
#include "../AStar.h"

class CEnemyZombie : public CEnemy
{
public:
	CEnemyZombie();
	~CEnemyZombie(void);

	virtual void Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer);			// Update

private:
	AStar* m_cAStar;
};