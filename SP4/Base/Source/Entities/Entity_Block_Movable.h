#ifndef ENTITY_BLOCK_MOVABLE_H
#define ENTITY_BLOCK_MOVABLE_H

#include "Vector3.h"
#include "EntityIPos.h"

#define Entity_Hazard_Moving_Speed 10.f

class CEntity_Block_Movable : public CEntityIPos
{
public:
	CEntity_Block_Movable();
	CEntity_Block_Movable(int iXIndex, int iYIndex);
	~CEntity_Block_Movable();

	virtual void Update(const float dt, CPlayer* cPlayer);			// Update
	virtual void UpdateMovement(const float dt, CPlayer* cPlayer);
	
private:
	enum MOVE_DIR
	{
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_NONE,
	};

	MOVE_DIR m_MoveDir;
};

#endif
