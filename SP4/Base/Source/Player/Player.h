#pragma once
#include "Vector3.h"
#include "../Tilemap.h"
#include "../Graphics/SpriteAnimation.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer(void);

	enum CollisionReponse
	{
		COL_FLOOR,
		COL_WALL,
		NUM_COL
	};

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

	void Init(int pos_x, int pos_y, SpriteAnimation* mesh);		// Initialise this class instance

	void SetPos_x(int pos_x);							// Set position x of the player
	void SetPos_y(int pos_y);							// Set position y of the player

	// Update Movements
	bool MoveUpDown(const bool mode, CTilemap* tile);
	bool MoveLeftRight(const bool mode, CTilemap* tile);

	int GetPos_x(void);									// Get position x of the player
	int GetPos_y(void);									// Get position y of the player

	float GetOffSet_x(void);
	float GetOffSet_y(void);

	SpriteAnimation* GetSpriteAnimation(void);

	void Update(double dt, CTilemap* tile);								// Update

	CollisionReponse CheckCollision(CTiledata tileData);
	PlayerDirection GetDirection(void);

	PlayerDirection GetNextDirection(void);
	void SetNextDirection(PlayerDirection);

	void AddAnimation(Animation* _anim, PlayerAction playerState);

private:
	// Hero's information
	int playerPosX, playerPosY;

	float xOffSet, yOffSet;

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

	//Mesh* mesh;
};