#pragma once
#include "Vector3.h"
#include "../Tilemap.h"


class CPlayer
{
public:
	CPlayer();
	~CPlayer(void);

	void Init(float pos_x, float pos_y);									// Initialise this class instance

	void SetPos_x(float pos_x);							// Set position x of the player
	void SetPos_y(float pos_y);							// Set position y of the player
	void SetPos(Vector3 playerPos);						// Set position x of the player

	// Update Movements
	void MoveUpDown(const bool mode, CTilemap* tile);
	void MoveLeftRight(const bool mode, CTilemap* tile);

	float GetPos_x(void);									// Get position x of the player
	float GetPos_y(void);									// Get position y of the player
	Vector3 GetPos();								// Get position of the pl`ayer

	void Update();								// Update

private:
	// Hero's information
	Vector3 playerPos;

	bool myKeys[255];
};