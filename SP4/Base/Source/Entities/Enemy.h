#include "../Tilemap.h"
#include "../Player/Player.h"

class CEnemy
{
public:
	CEnemy();
	~CEnemy(void);

	void SetXIndex(float iXIndex);							// Set position x of the player
	void SetYIndex(float iYIndex);							// Set position y of the player
	void SetPos(int iXIndex, int iYIndex);					// Set position x of the player

	int GetXIndex(void);									// Get position x of the player
	int GetYIndex(void);									// Get position y of the player

	virtual void Update(const float dt, CTilemap* cTilemap, CPlayer* cPlayer);		// Update

private:
	int m_iXIndex;
	int m_iYIndex;
};