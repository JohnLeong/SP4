#pragma once
#include "Vector3.h"
#include "../Tilemap.h"


class CPlayer
{
public:
	CPlayer();
	~CPlayer(void);

	void Init(int pos_x, int pos_y);									// Initialise this class instance

	void SetPos_x(int pos_x);							// Set position x of the player
	void SetPos_y(int pos_y);							// Set position y of the player

	// Update Movements
	void MoveUpDown(const bool mode, CTilemap* tile);
	void MoveLeftRight(const bool mode, CTilemap* tile);

	int GetPos_x(void);									// Get position x of the player
	int GetPos_y(void);									// Get position y of the player

	void Update();								// Update

private:
	// Hero's information
	int playerPosX, playerPosY;

	bool myKeys[255];
};