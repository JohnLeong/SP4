#include "Vector3.h"
#include "../Mesh.h"
#include "MyMath.h"

class CGameEntity
{
public:
	CGameEntity();
	~CGameEntity();

	virtual float GetXPos(void);
	virtual float GetYPos(void);

	virtual void SetXPos(float);
	virtual void SetYPos(float);

	virtual void SetHealth(int);
	virtual void SetMaxHealth(int);
	virtual void DeductHealth(int);
	virtual int GetHealth(void);
	virtual int GetMaxHealth(void);

	virtual void Update(const float dt);

protected:
	//Gameplay variables
	int current_health;
	int max_health;

public:
	Vector3 pos;					//Entity position
	Mesh* mesh;
};

