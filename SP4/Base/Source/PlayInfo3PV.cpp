#include "PlayInfo3PV.h"
#include "MeshBuilder.h"
#include "Mtx44.h"
#include "Application.h"

#define MaxPaintgunAmmo 5
#define MaxActgunAmmo 5
#define ShootCD 0.2f
#define ReloadCD 1.f

CPlayInfo3PV::CPlayInfo3PV(void)
	: theAvatarMesh(NULL)
	, jumpspeed(0)
	, m_bCurrentWeapon(true)
{
	Init();
}


CPlayInfo3PV::~CPlayInfo3PV(void)
{
	if (theAvatarMesh)
	{
		delete theAvatarMesh;
		theAvatarMesh = NULL;
	}
}

// Initialise this class instance
void CPlayInfo3PV::Init(void)
{
	curPosition.Set( 0, 0, 0);
	curDirection.Set( 0, 0, 1 );

	// Initialise the Avatar's movement flags
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}

	ReloadActGun();
	ReloadPaintGun();

	m_fReloadTimer = 0.f;
	m_fShootTimer = 0.f;
	m_bReloading = false;;
	m_bCanShoot = true;
}

// Set Model
bool CPlayInfo3PV::SetModel( Mesh* theAvatarMesh )
{
	this->theAvatarMesh = theAvatarMesh;
	if (this->theAvatarMesh == NULL)
		return false;

	return true;
}

// Returns true if the player is on ground
bool CPlayInfo3PV::isOnGround(void)
{
	return true;
}

// Returns true if the player is jumping upwards
bool CPlayInfo3PV::isJumpUpwards(void)
{
	return true;
}

// Returns true if the player is on freefall
bool CPlayInfo3PV::isFreeFall(void)
{
	return true;
}

// Set the player's status to free fall mode
void CPlayInfo3PV::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void CPlayInfo3PV::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true)
	{
		jumpspeed = 15;
	}
}

// Set position x of the player
void CPlayInfo3PV::SetPos_x(float pos_x)
{
	curPosition.x = pos_x;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_y(float pos_y)
{
	curPosition.y = pos_y;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_z(float pos_z)
{
	curPosition.z = pos_z;
}

// Set Jumpspeed of the player
void CPlayInfo3PV::SetJumpspeed(float jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

// Stop the player's movement
void CPlayInfo3PV::SetToStop(void)
{
	jumpspeed = 0;
}

/********************************************************************************
 Hero Move Up Down
 ********************************************************************************/
void CPlayInfo3PV::MoveFrontBack(const bool mode, const float timeDiff)
{
	if (mode)
	{
		curPosition -= curDirection.Normalized() * 200.f * timeDiff;
		curPosition.y = 0.f;
		//curDirection += curPosition;
	}
	else
	{
		curPosition += curDirection.Normalized() * 200.f * timeDiff;
		curPosition.y = 0.f;
		//curDirection += curPosition;
	}
}

/********************************************************************************
 Hero Move Left Right
 ********************************************************************************/
void CPlayInfo3PV::MoveLeftRight(const bool mode, const float timeDiff)
{
	Vector3 view = (curDirection).Normalized();
	Mtx44 rotation;
	float yaw = 90.f;

	if (mode)
		yaw = 90.f;
	else
		yaw = -90.f;

	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	view.y = 0.f;
	curPosition.x = curPosition.x + view.x *  timeDiff * 200.f;
	curPosition.z = curPosition.z + view.z *  timeDiff * 200.f;
}

void CPlayInfo3PV::TurnLeft(const double dt)
{
	Vector3 view = curDirection;
	//float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	float yaw = (float)(-200 * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	curDirection = view;
	curDirection.Normalize();
}

void CPlayInfo3PV::TurnRight(const double dt)
{
	Vector3 view = curDirection;
	//float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	float yaw = (float)(-200 * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	curDirection = view;
	curDirection.Normalize();
}

void CPlayInfo3PV::Pitch(const double dt)
{
	if (Application::camera_pitch > 0.0)
		LookUp(-Application::camera_pitch * dt);
	else if (Application::camera_pitch < 0.0)
		LookDown(-Application::camera_pitch * dt);
}

void CPlayInfo3PV::Yaw(const double dt)
{
	if (Application::camera_yaw > 0.0)
		TurnRight(Application::camera_yaw * dt);
	else if (Application::camera_yaw < 0.0)
		TurnLeft(Application::camera_yaw * dt);
}

void CPlayInfo3PV::LookUp(const double dt)
{
	//Vector3 view = curDirection;
	////float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	//float yaw = (float)(-200.f * (float)dt);
	//Mtx44 rotation;
	//rotation.SetToRotation(yaw, 1, 0, 0);
	//view = rotation * view;
	//curDirection = view;
	//curDirection.Normalize();
	
	//curDirection.x = ((curDirection.x) * cos(10)) - ((-curDirection.y) * sin(10));
	//curDirection.y = ((-curDirection.y) * cos(10)) - ((curDirection.x) * sin(10));
	Vector3 view = (curDirection).Normalized();
	Mtx44 rotation;
	float yaw = 90.f;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;

	Vector3 view2 = curDirection;
	float yaw2 = (float)(-200.f * (float)dt);
	Mtx44 rotation2;
	rotation2.SetToRotation(yaw2, view.x, view.y, view.z);
	view2 = rotation2 * view2;
	curDirection = view2;
	curDirection.Normalize();
}

void CPlayInfo3PV::LookDown(const double dt)
{
	//Vector3 view = curDirection;
	////float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);

	Vector3 view = (curDirection).Normalized();
	Mtx44 rotation;
	float yaw = 90.f;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;

	Vector3 view2 = curDirection;
	float yaw2 = (float)(-200.f * (float)dt);
	Mtx44 rotation2;
	rotation2.SetToRotation(yaw2, view.x, view.y, view.z);
	view2 = rotation2 * view2;
	curDirection = view2;
	curDirection.Normalize();

}

// Get position x of the player
float CPlayInfo3PV::GetPos_x(void)
{
	return curPosition.x;
}

// Get position y of the player
float CPlayInfo3PV::GetPos_y(void)
{
	return curPosition.y;
}

// Get position y of the player
float CPlayInfo3PV::GetPos_z(void)
{
	return curPosition.z;
}

// Get position of the player
Vector3 CPlayInfo3PV::GetPosition()
{
	return curPosition;
}

// Get direction of the player
Vector3 CPlayInfo3PV::GetDirection()
{
	return curDirection;
}

// Get Jumpspeed of the player
float CPlayInfo3PV::GetJumpspeed(void)
{
	return jumpspeed;
}

// Update Jump Upwards
void CPlayInfo3PV::UpdateJumpUpwards()
{
	curPosition.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
	}
}

// Update FreeFall
void CPlayInfo3PV::UpdateFreeFall()
{
	curPosition.y += jumpspeed;
	jumpspeed += 1;
}

// Constrain the position of the Hero to within the border
void CPlayInfo3PV::ConstrainHero(const int leftBorder, const int rightBorder, 
								  const int topBorder, const int bottomBorder, 
								  float timeDiff)
{
	if (curPosition.x < leftBorder)
	{
		curPosition.x = leftBorder;
	}
	else if (curPosition.x > rightBorder)
	{
		curPosition.x = rightBorder;
	}

	if (curPosition.y < topBorder)
		curPosition.y = topBorder;
	else if (curPosition.y > bottomBorder)
		curPosition.y = bottomBorder;
}


/********************************************************************************
 Update Movement
 ********************************************************************************/
void CPlayInfo3PV::UpdateMovement(const unsigned char key, const bool status)
{
	myKeys[key] = status;
}

/********************************************************************************
 Update
 ********************************************************************************/
void CPlayInfo3PV::Update(double dt)
{
	// WASD movement
	if (myKeys['w'] == true)
	{
		MoveFrontBack( false, dt );
	}
	else
	{
//		MoveVel_W = 0.0f;
	}
	if (myKeys['s'] == true)
	{
		MoveFrontBack( true, dt );
	}
	else
	{
//		MoveVel_S = 0.0f;
	}
	if (myKeys['a'] == true)
	{
		MoveLeftRight( true, dt );
	}
	else
	{
//		MoveVel_A = 0.0f;
	}
	if (myKeys['d'] == true)
	{
		MoveLeftRight( false, dt );
	}
	else
	{
//		MoveVel_D = 0.0f;
	}

	// Rotation
	/*
	if ( myKeys[VK_UP] == true)
	{
		LookUp( dt );
	}
	if (myKeys[VK_DOWN] == true)
	{
		LookUp( -dt );
	}
	if (myKeys[VK_LEFT] == true)
	{
		TurnLeft( -dt );
	}
	if (myKeys[VK_RIGHT] == true)
	{
		TurnRight( dt );
	}

	// Jump
	if (myKeys[32] == true)
	{
		Jump( dt );
		myKeys[32]	= false;
	}
	UpdateJump(dt);

	//Update the camera direction based on mouse move
	// left-right rotate
	if ( Application::camera_yaw != 0 )
		Yaw( dt );
	if ( Application::camera_pitch != 0 )
		Pitch( dt );

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	*/

	if (Application::camera_yaw != 0)
		Yaw(dt);
	if (Application::camera_pitch != 0)
		Pitch(dt);

	if (!m_bCanShoot)
	{
		m_fShootTimer -= dt;
		if (m_fShootTimer < 0.f)
			m_bCanShoot = true;
	}
	if (m_bReloading)
	{
		m_fReloadTimer -= dt;
		if (m_fReloadTimer < 0.f)
		{
			if (m_bCurrentWeapon)
				ReloadPaintGun();
			else
				ReloadActGun();
			m_bReloading = false;
		}
	}
}

void CPlayInfo3PV::ReloadCurrentWep(void)
{
	m_bReloading = true;
	m_fReloadTimer = ReloadCD;
}

void CPlayInfo3PV::ReloadPaintGun(void)
{
	m_iPaintGunAmmo = MaxPaintgunAmmo;
}

void CPlayInfo3PV::ReloadActGun(void)
{
	m_iActGunAmmo = MaxActgunAmmo;
}

void CPlayInfo3PV::ChangeWeapon(void)
{
	m_bCurrentWeapon = !m_bCurrentWeapon;
}

bool CPlayInfo3PV::GetCurrentWep(void)
{
	return m_bCurrentWeapon;
}

int CPlayInfo3PV::GetCurrentWepAmmo(void)
{
	if (m_bCurrentWeapon)
		return m_iPaintGunAmmo;
	else
		return m_iActGunAmmo;
}

void CPlayInfo3PV::Shoot(void)
{
	if (m_bCurrentWeapon)
		--m_iPaintGunAmmo;
	else
		--m_iActGunAmmo;
	m_bCanShoot = false;
	m_fShootTimer = ShootCD;
}