#include "Enemy.h"

class CEnemyZombie : public CEnemy
{
public:
	CEnemyZombie();
	~CEnemyZombie(void);

	virtual void Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer);			// Update

private:
};