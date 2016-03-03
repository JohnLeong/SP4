#include "PhysicsObjectManager.h"


CPhysicsObjectManager::CPhysicsObjectManager()
: m_fNextTimer(0.5f)
{
}


CPhysicsObjectManager::~CPhysicsObjectManager()
{

}

void CPhysicsObjectManager::Update(double dt)
{
	float fDelta = static_cast<float>(dt);
	for (std::vector<CPhysicsObject*>::iterator object = m_ObjectList.begin(); object != m_ObjectList.end(); object++)
	{
		if ((*object)->m_bActive)
			(*object)->Update(fDelta);
	}
	m_fNextTimer -= fDelta;
	if (m_fNextTimer < 0.f)
	{
		m_fNextTimer = 0.3f;
		FetchObject();
	}
}

void CPhysicsObjectManager::Cleanup(void)
{
	while (m_ObjectList.size() > 0)
	{
		CPhysicsObject* object = m_ObjectList.back();
		delete object;
		m_ObjectList.pop_back();
	}
}

CPhysicsObject* CPhysicsObjectManager::FetchObject(void)
{
	//Exercise 3a: Fetch a game object from m_goList and return it
	for (std::vector<CPhysicsObject *>::iterator it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
	{
		CPhysicsObject *go = (CPhysicsObject *)*it;
		if (go->m_bActive == false)
		{
			go->m_bActive = true;
			go->m_fPosX = -0.8f;
			go->m_fPosY = Math::RandFloatMinMax(-0.1f, 0.4f);
			go->m_fSpeedX = Math::RandFloatMinMax(0.05f, 0.2f);
			return go;
		}
	}
	for (unsigned x = 0; x < 10; ++x)
	{
		CPhysicsObject *go = new CPhysicsObject();
		go->m_bActive = false;
		m_ObjectList.push_back(go);
	}
	CPhysicsObject *go = m_ObjectList.back();
	go->m_bActive = true;
	go->m_fPosX = -0.8f;
	go->m_fPosY = Math::RandFloatMinMax(-0.1f, 0.4f);
	go->m_fSpeedX = Math::RandFloatMinMax(0.05f, 0.2f);
	return go;
}