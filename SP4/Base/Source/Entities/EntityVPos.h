#ifndef ENTITYVPOS_H
#define ENTITYVPOS_H

#include "Vector3.h"
#include "Entity.h"
/*
\brief
Base class for all game entities using world space based position
*/
class CEntityVPos	: public CEntity
{
public:
	CEntityVPos();
	~CEntityVPos();

	virtual float GetXPos(void);
	virtual float GetYPos(void);
	virtual Vector3 GetPos(void);

	virtual void SetXPos(float);
	virtual void SetYPos(float);
	virtual void SetPos(Vector3);

	virtual void Update(const float dt);			// Update

protected:
	Vector3 pos;					//Entity position
};

#endif