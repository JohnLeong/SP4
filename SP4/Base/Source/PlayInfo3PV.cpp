#include "PlayInfo3PV.h"
#include "MeshBuilder.h"
#include "Application.h"

CPlayInfo3PV::CPlayInfo3PV(void)
	: theAvatarMesh(NULL)
	, jumpspeed(0)
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
	camRotation.SetToRotation(0, 0, 1, 0);

	up = Vector3(0, 1, 0);
	right = curDirection.Cross(up);

	// Initialise the Avatar's movement flags
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}
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
void CPlayInfo3PV::SetJumpspeed(int jumpspeed)
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
	Vector3 temp = Vector3(curDirection.x, 0, curDirection.z).Normalized();
	if (mode)
	{
		curPosition -= temp * (float) (100.0f * timeDiff);
	}
	else
	{
		curPosition += temp * (float) (100.0f * timeDiff);
	}
}

/********************************************************************************
 Hero Move Left Right
 ********************************************************************************/
void CPlayInfo3PV::MoveLeftRight(const bool mode, const float timeDiff)
{
	Vector3 temp = Vector3(curDirection.x, 0, curDirection.z).Normalized();
	Vector3 rightDirection = temp.Cross(Vector3(0, 1, 0));
	if (mode)
	{
		curPosition.x = curPosition.x - rightDirection.x * (int) (100.0f * timeDiff);
		curPosition.z = curPosition.z - rightDirection.z * (int)(100.0f * timeDiff);
	}
	else
	{
		curPosition.x = curPosition.x + rightDirection.x * (int) (100.0f * timeDiff);
		curPosition.z = curPosition.z + rightDirection.z * (int)(100.0f * timeDiff);
	}
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
int CPlayInfo3PV::GetJumpspeed(void)
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
		MoveFrontBack(false, dt);
		camera.m_fTPVCameraOffset = 30.00f;
	}
	else
	{
		//		MoveVel_W = 0.0f;
	}
	if (myKeys['s'] == true)
	{
		MoveFrontBack(true, dt);
	}
	else
	{
		//		MoveVel_S = 0.0f;
	}
	if (myKeys['a'] == true)
	{
		MoveLeftRight(true, dt);
	}
	else
	{
		//		MoveVel_A = 0.0f;
	}
	if (myKeys['d'] == true)
	{
		MoveLeftRight(false, dt);
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
	left-right rotate
	if ( Application::camera_yaw != 0 )
	Yaw( dt );
	if ( Application::camera_pitch != 0 )
	Pitch( dt );

	if(Application::IsKeyPressed('R'))
	{
	Reset();
	}
	*/

	// Camera turn Left and Right
	if (Application::camera_yaw != 0)
	{
		if (Application::camera_yaw > 0.0)
		{
			float yaw = (float)((Application::camera_yaw *- 100)*dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			curDirection = rotation * curDirection;
			right = curDirection.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(curDirection).Normalized();
		}
		else if (Application::camera_yaw < 0.0)
		{
			float yaw = (float)((Application::camera_yaw *- 100)*dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			curDirection = rotation * curDirection;
			right.y = 0;
			right.Normalize();
			up = right.Cross(curDirection).Normalized();
		}
	}

	// Camera turn Up and Down
	if (Application::camera_pitch != 0)
	{
		if (Application::camera_pitch > 0.0)
		{
			float pitch = (float)((Application::camera_pitch *100)*dt);
			Mtx44 rotation;
			rotation.SetToRotation(pitch, 1, 0, 0);
			curDirection = rotation * curDirection;
			right = curDirection.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(curDirection).Normalized();
		}

		else if (Application::camera_pitch < 0.0)
		{
			float pitch = (float)((Application::camera_pitch *100)*dt);
			Mtx44 rotation;
			rotation.SetToRotation(pitch, 1, 0, 0);
			curDirection = rotation * curDirection;
			right.y = 0;
			right.Normalize();
			up = right.Cross(curDirection).Normalized();
		}
	}
}