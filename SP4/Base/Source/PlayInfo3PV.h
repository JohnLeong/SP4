#pragma once
#include "Vector3.h"
#include "Mesh.h"

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

	// Initialise this class instance
	void Init(void);

	// Set Model
	bool SetModel( Mesh* theAvatarMesh );

	// Returns true if the player is on ground
	bool isOnGround(void);
	// Returns true if the player is jumping upwards
	bool isJumpUpwards(void);
	// Returns true if the player is on freefall
	bool isFreeFall(void);
	// Set the player's status to free fall mode
	void SetOnFreeFall(bool isOnFreeFall);
	// Set the player to jumping upwards
	void SetToJumpUpwards(bool isOnJumpUpwards);
	// Stop the player's movement
	void SetToStop(void);
	// Set position x of the player
	void SetPos_x(float pos_x);
	// Set position y of the player
	void SetPos_y(float pos_y);
	// Set position z of the player
	void SetPos_z(float pos_y);
	// Set Jumpspeed of the player
	void SetJumpspeed(float jumpspeed);

	// Update Movements
	void MoveFrontBack(const bool mode, const float timeDiff);
	void MoveLeftRight(const bool mode, const float timeDiff);
	virtual void TurnLeft(const double dt);
	virtual void TurnRight(const double dt);
	virtual void LookUp(const double dt);
	virtual void LookDown(const double dt);

	virtual void Pitch(const double dt);
	virtual void Yaw(const double dt);

	// Get position x of the player
	float GetPos_x(void);
	// Get position y of the player
	float GetPos_y(void);
	// Get position z of the player
	float GetPos_z(void);
	// Get position of the player
	Vector3 GetPosition();
	// Get direction of the player
	Vector3 GetDirection();
	// Get Jumpspeed of the player
	float GetJumpspeed(void);

	// Update Jump Upwards
	void UpdateJumpUpwards();
	// Update FreeFall
	void UpdateFreeFall();
	// Update
	void UpdateMovement(const unsigned char key, const bool status = true);
	// Update
	void Update(double dt);

	// Reset the avatar to default settings
	void Reset();

	// Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder, 
					   const int topBorder, const int bottomBorder, 
					   float timeDiff);

	// Avatar's Mesh
	Mesh*	theAvatarMesh;

	void ReloadCurrentWep(void);
	void ReloadPaintGun(void);
	void ReloadActGun(void);
	void ChangeWeapon(void);
	bool GetCurrentWep(void);
	int GetCurrentWepAmmo(void);
	void Shoot(void);

	bool m_bReloading;
	bool m_bCanShoot;

private:
	// Hero's information
	Vector3 curPosition;
	Vector3 curDirection;
	float jumpspeed;

	bool myKeys[255];

	int m_iPaintGunAmmo;
	int m_iActGunAmmo;
	bool m_bCurrentWeapon;	//true = paintgun, false = actgun
	float m_fReloadTimer;
	float m_fShootTimer;
};

