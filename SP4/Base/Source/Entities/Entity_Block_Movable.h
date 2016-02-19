#ifndef ENTITY_BLOCK_MOVABLE_H
#define ENTITY_BLOCK_MOVABLE_H

#include "Vector3.h"
#include "EntityIPos.h"

class CEntity_Block_Movable : public CEntityIPos
{
public:
	CEntity_Block_Movable();
	CEntity_Block_Movable(int iXIndex, int iYIndex, CTilemap* cTilemap);
	~CEntity_Block_Movable();

	virtual bool DoColDir(MOVE_DIR m_MoveDir, std::vector<CEntityIPos*>* entityList);

	virtual void Update(const float dt, CPlayer* cPlayer);			// Update
	virtual void UpdateMovement(const float dt, CPlayer* cPlayer, std::vector<CEntityIPos*>* entityList);
};

#endif
