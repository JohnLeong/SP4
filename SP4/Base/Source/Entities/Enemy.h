#include "../Tilemap.h"
#include "EntityIPos.h"

class CEnemy : public CEntityIPos
{
public:
	CEnemy();
	~CEnemy(void);

	virtual void Update(const float dt, CPlayer* cPlayer);		// Update
};