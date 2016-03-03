#pragma once

#include <vector>
#include "PhysicsObject.h"
#include "MyMath.h"

class CPhysicsObjectManager
{
public:
	CPhysicsObjectManager();
	~CPhysicsObjectManager();

	void Update(double dt);
	void Cleanup(void);

	CPhysicsObject* FetchObject(void);

	std::vector<CPhysicsObject*> m_ObjectList;

private:
	float m_fNextTimer;
};

