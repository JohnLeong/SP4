#ifndef ENTITY_H
#define ENTITY_H

#include "../Graphics/SpriteAnimation.h"
#include "../Tilemap.h"
#include "../define.h"

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
	int m_iCurrent_health;
	int m_iMax_health;
	bool m_bAlive;
	bool m_bActive;
	SpriteAnimation* m_cSprite;
	CTilemap* m_cTilemap;
};

#endif