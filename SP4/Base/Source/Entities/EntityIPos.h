#ifndef ENTITYIPOS_H
#define ENTITYIPOS_H

#include "Entity.h"

/*
\brief
Base class for all game entities using index based position
*/

class CEntityIPos : public CEntity
{
public:
	enum MOVE_DIR
	{
		DIR_UP = 0,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_IDLE_UP,
		DIR_IDLE_DOWN,
		DIR_IDLE_LEFT,
		DIR_IDLE_RIGHT,
		NUM_DIR,
		DIR_NONE
	};

public:
	CEntityIPos();
	~CEntityIPos();

	virtual void SetXIndex(int iXIndex);							// Set position x of the player
	virtual void SetYIndex(int iYIndex);							// Set position y of the player
	virtual void SetPos(int iXIndex, int iYIndex);					// Set position x of the player
	virtual bool DoColDir(MOVE_DIR m_MoveDir);						//Do collision response in specified direction

	virtual int GetXIndex(void);									// Get position x of the player
	virtual int GetYIndex(void);									// Get position y of the player

	virtual float GetXOffset(void);									// Get offset x of the player
	virtual float GetYOffset(void);									// Get offset y of the player

	virtual float GetRenderPosX(void);
	virtual float GetRenderPosY(void);

	virtual Vector3 GetNextDirectionPos(void);						//Get next movement direction of this entity

	virtual bool IsMoving(void);

	virtual void Update(const float dt);							//Update
	virtual void UpdateMovement(const float dt);					//Update movement

	virtual	bool DoCurrentTileCollision(void);						//Do collision check with tilemap and entities for current position

	virtual bool AllowEnemyMovement(void);							//Return true if enemies are able to path through this entity
	virtual bool DeathOnEntry(void);								//Return true if this entity kills player on collision

	//For player
	virtual int GetCoins(void);
	virtual void AddCoin(int iAmt);

	virtual int GetKeys_Red(void);
	virtual int GetKeys_Blue(void);
	virtual int GetKeys_Yellow(void);
	virtual int GetKeys_Green(void);

	virtual void AddKeys(int iAmt, int type);
	//For enemy
	virtual bool IsHoldingObj(void);
	virtual CEntityIPos* GetHoldingObj(void);
	virtual void SetRecalculate(bool b);

protected:
	int m_iXIndex;			//X Index position of entity
	int m_iYIndex;			//Y Index position of entity

	float m_fOffSetX;		//Render offset for translation in X axis
	float m_fOffSetY;		//Render offset for translation in Y axis

	float m_fDeathOffSetX;	//X axis Translation offset for death animation
	float m_fDeathOffSetY;	//Y axis Translation offset for death animation

	MOVE_DIR m_MoveDir;		//Current movement direction of entity
	MOVE_DIR m_AnimDir;		//Current animation direction to display

	CEntityIPos* m_cPlayerPtr;							//Player pointer to access player propeties
	CEntityIPos* m_cObjPtr;								//Pointer to object this entity is holding
	std::vector<CEntityIPos*>* m_cEntityList;			//Pointer to list of entities
	bool m_bHoldingObj;									//true = holding object, false = not holding object
	bool m_bRecalculate;								//recalculate movements (pathfinding etc)
	bool m_bDeathDir;									//Death animation direction - left || right
};

#endif