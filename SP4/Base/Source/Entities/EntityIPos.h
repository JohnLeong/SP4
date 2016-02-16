#include "Entity.h"

//Entity class for entities using index based position

class CEntityIPos : public CEntity
{
public:
	CEntityIPos();
	~CEntityIPos();

	virtual void SetXIndex(float iXIndex);							// Set position x of the player
	virtual void SetYIndex(float iYIndex);							// Set position y of the player
	virtual void SetPos(int iXIndex, int iYIndex);					// Set position x of the player

	virtual int GetXIndex(void);									// Get position x of the player
	virtual int GetYIndex(void);									// Get position y of the player

	virtual void Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer);		// Update

protected:
	int m_iXIndex;			//X Index
	int m_iYIndex;			//Y Index
};

