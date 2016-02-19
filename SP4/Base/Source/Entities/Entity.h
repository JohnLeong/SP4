#ifndef ENTITY_H
#define ENTITY_H

#include "../Graphics/SpriteAnimation.h"
#include "../Tilemap.h"
#include "../Player/Player.h"

class CEntity
{
public:
	CEntity();
	~CEntity();

	virtual void SetHealth(int);
	virtual void SetMaxHealth(int);
	virtual void DeductHealth(int);
	virtual int GetHealth(void);
	virtual int GetMaxHealth(void);
	virtual bool IsAlive(void);

	virtual void Update(const float dt, CPlayer* cPlayer);		// Update

	void SetSprite(SpriteAnimation* sa);
	SpriteAnimation* GetSprite(void);

protected:
	//Gameplay variables
	int m_iCurrent_health;
	int m_iMax_health;
	bool m_bAlive;
	SpriteAnimation* m_cSprite;
	CTilemap* m_cTilemap;
};

#endif