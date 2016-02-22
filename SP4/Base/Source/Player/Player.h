#pragma once
#include "Vector3.h"
#include "../Entities/EntityIPos.h"

class CPlayer : public CEntityIPos
{
public:
	CPlayer();
	~CPlayer(void);

	enum PlayerDirection
	{
		PD_UP,
		PD_DOWN,
		PD_LEFT,
		PD_RIGHT,
		PD_NONE,
		NUM_PLAYER_DIRECTION
	};

	enum PlayerAction
	{
		PA_IDLE_UP = 0,
		PA_IDLE_DOWN,
		PA_IDLE_LEFT,
		PA_IDLE_RIGHT,
		PA_WALK_UP,
		PA_WALK_DOWN,
		PA_WALK_LEFT,
		PA_WALK_RIGHT,
		NUM_PLAYER_ACTION,
	};

	void Init(CTilemap* cTilemap, int pos_x, int pos_y, SpriteAnimation* mesh, std::vector<CEntityIPos*>* cEntityList);		// Initialise this class instance

	// Update Movements
	bool MoveUpDown(const bool mode, CTilemap* tile);
	bool MoveLeftRight(const bool mode, CTilemap* tile);

	bool IsMoving(void);

	SpriteAnimation* GetSpriteAnimation(void);

	void Update(double dt, CTilemap* tile);								// Update

	void DoCurrentTileCollision(CTilemap* cTilemap);
	PlayerDirection GetDirection(void);

	PlayerDirection GetNextDirection(void);
	Vector3 GetNextDirectionPosition(void);
	void SetNextDirection(PlayerDirection);

	void AddAnimation(Animation* _anim, PlayerAction playerState);

	int GetCoins(void);
	void AddCoin(int iAmt);

	void Reset(void);

private:

	bool myKeys[255];

	bool moving;
	bool XYDirection;
	bool offSetDirectionX;
	bool offSetDirectionY;

	PlayerDirection direction;
	PlayerDirection m_NextDir;

	PlayerAction action;

	SpriteAnimation* sprites;

	Animation* m__animationList[NUM_PLAYER_ACTION]; 

	int m_iCoins;
	//Mesh* mesh;
};