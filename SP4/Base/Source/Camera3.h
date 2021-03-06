#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"

class Camera3 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	enum CAM_TYPE { LAND_CAM, 
					AIR_CAM,
					NUM_CAM_TYPE };

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void UpdatePosition(Vector3 playerPos);
	// For Third Person Camera
	virtual void UpdatePosition(Vector3 position, Vector3 newDirection);
	// Update Camera status
	virtual void UpdateStatus(const unsigned char key, const bool status = true);
	virtual void Reset();

	// Basic methods
	virtual void MoveForward(const double dt);
	virtual void MoveBackward(const double dt);
	virtual void MoveLeft(const double dt);
	virtual void MoveRight(const double dt);
	virtual void TurnLeft(const double dt);
	virtual void TurnRight(const double dt);
	virtual void LookUp(const double dt);
	virtual void LookDown(const double dt);
	virtual void SpinClockWise(const double dt);
	virtual void SpinCounterClockWise(const double dt);

	virtual void SetCameraType(CAM_TYPE sCameraType);
	virtual CAM_TYPE GetCameraType(void);

	// Applied methods
	virtual void Pitch(const double dt);
	virtual void Yaw(const double dt);
	virtual void Roll(const double dt);
	virtual void Walk(const double dt);
	virtual void Strafe(const double dt);
	virtual void Jump(const double dt);
	virtual void UpdateJump(const double dt);
	float MoveVel_W;
	float MoveVel_S;
	float MoveVel_A;
	float MoveVel_D;
	float m_fTPVCameraOffset;
private:
	bool myKeys[255];

	CAM_TYPE sCameraType;

	// For Jump use
	bool m_bJumping;
	float GRAVITY;
	float JumpVel;
	float JUMPMAXSPEED, JUMPACCEL;

	// Maximum movement speed and acceleration
	float CAMERA_ACCEL;
};

#endif