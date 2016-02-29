#include "PhysicsObject.h"


CPhysicsObject::CPhysicsObject()
{
}


CPhysicsObject::~CPhysicsObject()
{
}

void CPhysicsObject::Update(double dt)
{
	//m_fRotation += dt * m_fRotationSpeed;
	m_fPosX += dt * m_fSpeedX;
	if (m_fPosX > 0.8f)
		m_bActive = false;
}