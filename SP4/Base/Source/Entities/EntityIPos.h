#ifndef ENTITYIPOS_H
#define ENTITYIPOS_H

#include "Entity.h"

//Entity class for entities using index based position

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

	virtual float GetXOffset(void);
	virtual float GetYOffset(void);

	Vector3 GetNextDirectionPos(void);

	virtual bool IsMoving(void);

	virtual void Update(const float dt);		// Update
	virtual void UpdateMovement(const float dt);

	virtual	bool DoCurrentTileCollision(void);

	virtual bool AllowEnemyMovement(void);

	//For player
	virtual int GetCoins(void);
	virtual void AddCoin(int iAmt);

	//For enemy
	virtual bool IsHoldingKey(void);

	CEntityIPos* m_cKeyPtr;

protected:
	int m_iXIndex;			//X Index
	int m_iYIndex;			//Y Index

	float m_fOffSetX;		//Render offset for translation in X axis
	float m_fOffSetY;		//Render offset for translation in Y axis

	MOVE_DIR m_MoveDir;		//Current movement direction of entity
	MOVE_DIR m_AnimDir;

	CEntityIPos* m_cPlayerPtr;							//Pointer to player
	std::vector<CEntityIPos*>* m_cEntityList;		//Pointer to list of entities
	bool m_bHoldingKey;
};

#endif