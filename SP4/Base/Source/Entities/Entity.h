#ifndef ENTITY_H
#define ENTITY_H

#include "../Graphics/SpriteAnimation.h"
#include "../Tilemap.h"
#include "../define.h"

/*
\brief
Base class for all game entities
*/

class CEntity
{
public:
	CEntity();
	~CEntity();

	virtual void SetHealth(int);
	virtual void SetMaxHealth(int);
	virtual void SetAlive(bool);
	virtual void SetActive(bool);
	virtual void DeductHealth(int);
	virtual int GetHealth(void);
	virtual int GetMaxHealth(void);
	virtual bool IsAlive(void);
	virtual bool IsActive(void);
	
	virtual void Update(const float dt);		// Update

	void SetSprite(SpriteAnimation* sa);
	SpriteAnimation* GetSprite(void); 

protected:
	//Gameplay variables
	int m_iCurrent_health;			//Current health of entity
	int m_iMax_health;				//Max health of entity
	bool m_bAlive;					//Enemy alive state
	bool m_bActive;					//Enemy active state
	SpriteAnimation* m_cSprite;		//Sprite animation for this entity
	CTilemap* m_cTilemap;			//Pointer to current tilemap
};

#endif