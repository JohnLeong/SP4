#include "Vector3.h"
#include "EntityVPos.h"

#define Entity_Hazard_Moving_Speed 10.f

class CEntity_Hazard_Moving : public CEntityVPos
{
public:
	enum MoveDir
	{
		DIR_UP_DOWN = 0,
		DIR_LEFT_RIGHT,
		NUM_DIR
	};
	CEntity_Hazard_Moving();
	~CEntity_Hazard_Moving();

	virtual void Init(Vector3 pos, bool MoveDir, float m_fMoveDist);
	virtual void Update(const float dt, CPlayer* cPlayer);			// Update

protected:
	bool m_bDir;
	MoveDir m_MoveDir;
	Vector3 m_Origin;
	float m_fMoveDist;
};

