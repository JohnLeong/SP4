#ifndef SCENE_SPLASH_H
#define SCENE_SPLASH_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "Application.h"
#include "MatrixStack.h"
#include "Light.h"

class CSceneSplash : public CSceneManager
{
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_GRADIENT,
		GEO_BEAM,
		GEO_CHAR_1, 
		GEO_CHAR_2,
		GEO_CHAR_3,
		NUM_GEOMETRY,
	};

public:
	CSceneSplash(void);
	CSceneSplash(const int m_window_width, const int m_window_height);
	~CSceneSplash(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	float m_fTimer;
protected:
	Mesh* meshList[NUM_GEOMETRY];

private:
	enum ANIM_STATE
	{
		ANIM_0,
		ANIM_1,
		ANIM_2,
		ANIM_3,
		ANIM_4,
		ANIM_5,
		ANIM_6,
	};
	ANIM_STATE cAnimState;
	float m_fScreenCol;

	float m_fLogoTranslateY;
	float m_fLogo1PosY;
	float m_fLogo2PosY;
	float m_fLogo3PosY;
	float m_fBeamScaleX;

	float m_fShakeRadius;
	float m_fShakeAngle;
	float m_fShakeOffsetX;
	float m_fShakeOffsetY;
	float m_fBeamWait;

	bool m_bDoShake;
	bool m_bplaySplashSoundback;
};

#endif