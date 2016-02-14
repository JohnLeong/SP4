#pragma once
#include "Vector3.h"
#include "Mesh.h"
#include "Mtx44.h"
#include "Camera3.h"

class CPlayInfo3PV
{
public:
	CPlayInfo3PV(void);
	virtual ~CPlayInfo3PV(void);

	enum GEOMETRY_TYPE
	{
		GEO_AVATAR,
		NUM_GEOMETRY,
	};
	Camera3 camera;
	void Init(void);									// Initialise this class instance

	bool SetModel( Mesh* theAvatarMesh );				// Set Model
	bool isOnGround(void);								// Returns true if the player is on ground
	bool isJumpUpwards(void);							// Returns true if the player is jumping upwards
	bool isFreeFall(void);								// Returns true if the player is on freefall
	
	void SetOnFreeFall(bool isOnFreeFall);				// Set the player's status to free fall mode
	void SetToJumpUpwards(bool isOnJumpUpwards);		// Set the player to jumping upwards
	void SetToStop(void);								// Stop the player's movement
	void SetPos_x(float pos_x);							// Set position x of the player
	void SetPos_y(float pos_y);							// Set position y of the player
	void SetPos_z(float pos_y);							// Set position z of the player
	void SetJumpspeed(int jumpspeed);					// Set Jumpspeed of the player

	// Update Movements
	void MoveFrontBack(const bool mode, const float timeDiff);
	void MoveLeftRight(const bool mode, const float timeDiff);

	float GetPos_x(void);									// Get position x of the player
	float GetPos_y(void);									// Get position y of the player
	float GetPos_z(void);									// Get position z of the player
	int GetJumpspeed(void);								// Get Jumpspeed of the player
	
	Vector3 GetPosition();								// Get position of the player
	Vector3 GetDirection();								// Get direction of the player
		
	void UpdateJumpUpwards();							// Update Jump Upward
	void UpdateFreeFall();								// Update FreeFall
	void UpdateMovement(const unsigned char key,		// Update
		const bool status = true);
	void Update(double dt);								// Update


	Mesh*	theAvatarMesh;								// Avatar's Mesh

	float acceleration;
	float velocity;

private:
	// Hero's information
	Vector3 curPosition;
	Vector3 curDirection;	// curDirection = TransformationMatrix * curDirection;
							// TransformationMatrix = [cos -sin 0 0]
							//						  [ 0    0  1 0]
							//						  [sin  cos 0 0]
							//						  [ 0    0  0 1]

	Mtx44 camRotation;
	int jumpspeed;
	bool myKeys[255];

	Vector3 up, right;
};

