#pragma once

class CPhysicsObject
{
public:
	CPhysicsObject();
	~CPhysicsObject();

	void Update(double dt);

	float m_fRotation;
	float m_fRotationSpeed;
	float m_fPosX;
	float m_fPosY;
	float m_fSpeedX;
	float m_fSize;
	bool m_bActive;
};

