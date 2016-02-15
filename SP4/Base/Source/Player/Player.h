#pragma once
#include "Vector2.h"


class CPlayer
{
	CPlayer();
	~CPlayer(void);

	void Init(float pos_x, float pos_y);									// Initialise this class instance

	void SetPos_x(float pos_x);							// Set position x of the player
	void SetPos_y(float pos_y);							// Set position y of the player
	void SetPos(Vector2 playerPos);							// Set position x of the player

	// Update Movements
	void MoveUpDown(const bool mode);
	void MoveLeftRight(const bool mode);

	float GetPos_x(void);									// Get position x of the player
	float GetPos_y(void);									// Get position y of the player
	Vector2 GetPos();								// Get position of the player

	void Update();								// Update

private:
	// Hero's information
	Vector2 curPosition;
	bool myKeys[255];
};